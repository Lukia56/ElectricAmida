#include "PauseManager.h"
#include <DxLib.h>
#include "../System/InputManager.h"
#include "../System/ObjectManager.h"
#include "../System/SoundManager.h"
#include "../Scene/SceneBase.h"
#include "../Scene/SceneMain.h"
#include "../Scene/SceneTitle.h"
#include "../Scene/Fader.h"
#include "../Utility/Color.h"

namespace
{
	// メニュー画面の項目一覧
	enum Choice
	{
		EndPause,
		Retry,
		Quit,
		Max
	};
}

PauseManager::PauseManager(ObjectManager* objManager, SceneBase* scene) :
	mScreenGraph(-1),
	mIsPaused(false),
	mMenuChoice(0),
	mObjectManager(objManager),
	mScene(scene)
{
}

PauseManager::~PauseManager()
{
	// 画面のグラフィックを解放する
	if (mScreenGraph != -1)
	{
		DeleteGraph(mScreenGraph);
	}
}

void PauseManager::Update()
{
	// ポーズボタンが押されたらポーズ状態を切り替える
	if (InputManager::GetInstance().IsPressed(Input::Action::Pause))
	{
		TogglePause();
	}

	// ポーズ中の処理
	OnPause();
}

void PauseManager::Draw()
{
	// オブジェクトの描画を停止しても画面に写し続けるために、
	// ポーズ前の画面を取得する
	if (mIsPaused && mScreenGraph == -1)
	{
		// 描画先のサイズを取得
		int sx, sy;
		GetDrawScreenSize(&sx, &sy);

		// 描画先と同じサイズの空の画面を作成
		mScreenGraph = MakeScreen(sx, sy);

		// 現在のゲーム画面を格納する
		GetDrawScreenGraph(0, 0, sx, sy, mScreenGraph);
	}

	// ポーズ前の画面を描画
	if (mScreenGraph != -1)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 127);
		DrawGraph(0, 0, mScreenGraph, 0);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		DrawExtendString(180, 40, 2, 2, "ポーズ中", Color::kWhite);

		DrawString(60, 240, "戻る", mMenuChoice == 0 ? Color::kYellow : Color::kGray);
		DrawString(60, 280, "リトライ", mMenuChoice == 1 ? Color::kYellow : Color::kGray);
		DrawString(60, 320, "タイトル画面へ戻る", mMenuChoice == 2 ? Color::kYellow : Color::kGray);
	}
}

void PauseManager::OnPause()
{
	// ポーズ中ではないなら早期リターン
	if (!mIsPaused) return;

	if (mScene->GetFader()->IsFadingOut()) return;

	// 上下ボタンで選択場所を移動
	if (InputManager::GetInstance().IsPressed(Input::Action::MenuUp))
	{
		mMenuChoice--;
		SoundManager::GetInstance().PlaySE(Sound::SE::MenuMove);
	}
	if (InputManager::GetInstance().IsPressed(Input::Action::MenuDown))
	{
		mMenuChoice++;
		SoundManager::GetInstance().PlaySE(Sound::SE::MenuMove);
	}

	// 選択場所を項目の範囲内に収める
	mMenuChoice = (mMenuChoice + Choice::Max) % Choice::Max;

	// 決定ボタンが押されたら項目を選ぶ
	if (InputManager::GetInstance().IsPressed(Input::Action::Confirm))
	{
		SoundManager::GetInstance().PlaySE(Sound::SE::Confirm);

		switch (mMenuChoice)
		{
		case Choice::EndPause:

			TogglePause();

			break;

		case Choice::Retry:

			mScene->GetFader()->StartFadeOut<SceneMain>();

			break;

		case Choice::Quit:

			mScene->GetFader()->StartFadeOut<SceneTitle>();

			break;
		}
	}
}

void PauseManager::TogglePause()
{
	// ポーズ状態を切り替える
	mIsPaused = !mIsPaused;

	SoundManager::GetInstance().PlaySE(Sound::SE::Pause);

	// ポーズされたならゲームオブジェクトを停止する
	if (mIsPaused)
	{
		mObjectManager->DeactiveAllGameObject();
	}
	// ポーズ解除されたなら画面のグラフィックを解放する
	if (!mIsPaused)
	{
		DeleteGraph(mScreenGraph);
		mScreenGraph = -1;

		mObjectManager->ActiveAllGameObject();
	}
}
