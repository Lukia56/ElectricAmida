#include "SceneTitle.h"
#include <DxLib.h>
#include <memory>
#include "../System/InputManager.h"
#include "../Utility/Color.h"
#include "../Scene/SceneMain.h"
#include "../Scene/Fader.h"
#include "../Easing/Tween.h"
#include "../ImGui/imgui.h"
#include "../Game.h"
#include "../System/InputDevice/InputDeviceMouse.h"

namespace
{
	// メニュー画面の項目一覧
	enum Choice
	{
		Start,
		Settings,
		Quit,
		Max
	};

	const char* const kButtonText[] = {"はじめる", "設定", "やめる"};

	// タイトルロゴの座標
	const Vector2 kLogoPos = { 240, 280 };
	// タイトルロゴのスケール
	const float kLogoScale = 0.5f;
	// タイトルロゴのパス
	const char* const kLogoGraphPath = "Resources\\Image\\Logo.png";

	// メニューボタンの基準座標
	const Vector2 kButtonBasePos = { 120, 420 };
	// メニューボタンの間隔
	const Vector2 kButtonOffsetPos = { 0, 70 };
	// メニューボタンの選択した時の幅
	const float kButtonChoiceOffsetPos = 50;
	// メニューボタンのパス
	const char* const kMenuButtonPath = "Resources\\Image\\MenuButton.png";
}

SceneTitle::SceneTitle() :
	mGraphLogo(-1),
	mGraphButton(),
	mMenuChoice(0),
	mTween(nullptr)
{
	mGraphButton.fill(-1);
	for (int i = 0; i < mGraphButton.size(); i++)
	{
		mButtonPos[i] = Vector2(kButtonBasePos + kButtonOffsetPos * i);
		mButtonPos[i].x -= kButtonChoiceOffsetPos;
	}
	mButtonAlpha.fill(255);
}

void SceneTitle::InitializeScene()
{
	mGraphLogo = LoadGraph(kLogoGraphPath);

	LoadDivGraph(kMenuButtonPath, 3, 1, 3, 187, 31, mGraphButton.data());

	mTween = std::make_unique<Tween>();

	AnimationButtonMove();
}

void SceneTitle::EndScene()
{
	DeleteGraph(mGraphLogo);
	for (auto& graph : mGraphButton)
	{
		DeleteGraph(graph);
	}
}

SceneBase* SceneTitle::UpdateScene()
{
	int preChoice = mMenuChoice;

	// 上下ボタンで選択場所を移動
	if (InputManager::GetInstance().IsPressed(Input::Action::MenuUp)) mMenuChoice--;
	if (InputManager::GetInstance().IsPressed(Input::Action::MenuDown)) mMenuChoice++;

	// 選択場所を項目の範囲内に収める
	mMenuChoice = (mMenuChoice + Choice::Max) % Choice::Max;

	// 項目を移動していたらボタン座標を更新
	if (preChoice != mMenuChoice)
	{
		AnimationButtonMove();
	}

	// 決定ボタンが押されたら項目を選ぶ
	if (InputManager::GetInstance().IsReleased(Input::Action::Confirm))
	{
		AnimationButtonChoose();

		switch (mMenuChoice)
		{
		case Choice::Start:

			GetFader()->StartFadeOut<SceneMain>();

			break;

		case Choice::Settings:



			break;

		case Choice::Quit:

			Game::isRunning = false;

			break;
		}
	}

	mTween->Update();

	return this;
}

void SceneTitle::DrawScene()
{
	for (int i = 0; i < Choice::Max; i++)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, mButtonAlpha[i]);

		//DrawGraph(mButtonPos[i].x, mButtonPos[i].y, mGraphButton[i], true);
		DrawRotaGraph(mButtonPos[i].x, mButtonPos[i].y, 2, 0, mGraphButton[i], true);

		DrawString(mButtonPos[i].x, mButtonPos[i].y, kButtonText[i], Color::kWhite);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	DrawRotaGraph(kLogoPos.x, kLogoPos.y, kLogoScale, 0, mGraphLogo, true);
}

void SceneTitle::DrawSceneImGui()
{
	if (ImGui::Begin("Scene"))
	{
		ImGui::Text("SceneTitle");

		ImGui::Text("mMenuChoice = %d", mMenuChoice);
	}

	ImGui::End();
}

void SceneTitle::AnimationButtonMove()
{
	for (int i = 0; i < Choice::Max; i++)
	{
		// 選択されているなら
		if (mMenuChoice == i)
		{
			// 飛び出させる
			std::vector<Animation::Keyframe> keyframes;
			// 開始位置を設定
			keyframes.emplace_back(Animation::Keyframe{ mButtonPos[i].x, 0, Animation::Ease::BackOut });
			// 終了位置を設定
			keyframes.emplace_back(Animation::Keyframe{ kButtonBasePos.x + kButtonOffsetPos.x, 15 });

			// アニメーションを開始
			mTween->StartAnim(&mButtonPos[i].x, keyframes);
		}
		// 選択されていないなら
		else
		{
			// 元の位置に戻す
			std::vector<Animation::Keyframe> keyframes;
			// 開始位置を設定
			keyframes.emplace_back(Animation::Keyframe{ mButtonPos[i].x, 0, Animation::Ease::QuadInOut });
			// 終了位置を設定
			keyframes.emplace_back(Animation::Keyframe{ kButtonBasePos.x + kButtonOffsetPos.x - kButtonChoiceOffsetPos, 8 });

			// アニメーションを開始
			mTween->StartAnim(&mButtonPos[i].x, keyframes);
		}
	}
}

void SceneTitle::AnimationButtonChoose()
{
	for (int i = 0; i < Choice::Max; i++)
	{
		// 選択されているなら
		if (mMenuChoice == i)
		{
			// X座標のアニメーション
			std::vector<Animation::Keyframe> keyframes;
			keyframes.emplace_back(Animation::Keyframe{ mButtonPos[i].x, 0, Animation::Ease::QuadIn });
			keyframes.emplace_back(Animation::Keyframe{ mButtonPos[i].x - 25, 3, Animation::Ease::ElasticOut });
			keyframes.emplace_back(Animation::Keyframe{ mButtonPos[i].x, 60 });

			mTween->StartAnim(&mButtonPos[i].x, keyframes);
		}
		// 選択されていないなら
		else
		{
			// X座標のアニメーション
			std::vector<Animation::Keyframe> keyframes;
			keyframes.emplace_back(Animation::Keyframe{ mButtonPos[i].x, 0, Animation::Ease::QuadIn });
			keyframes.emplace_back(Animation::Keyframe{ mButtonPos[i].x - 100, 6 });

			mTween->StartAnim(&mButtonPos[i].x, keyframes);

			// アルファのアニメーション
			keyframes.clear();
			keyframes.emplace_back(Animation::Keyframe{ 255, 0, Animation::Ease::QuadIn });
			keyframes.emplace_back(Animation::Keyframe{ 0, 6 });

			mTween->StartAnim(&mButtonAlpha[i], keyframes);
		}
	}
}
