#include "SceneTitle.h"
#include <DxLib.h>
#include "../System/InputManager.h"
#include "../Utility/Color.h"
#include "../Scene/SceneMain.h"
#include "../Scene/Fader.h"

namespace
{
	// メニュー画面の項目一覧
	enum Choice
	{
		Start,
		Quit,
		Max
	};

	// 矢印の基準位置
	const Vector2 kArrowBasePos = { 340, 405 };

	// 矢印の移動幅
	const float kArrowMoveOffset = 40.0f;

	// タイトルロゴの座標
	const Vector2 kLogoPos = { 200, 60 };

	// タイトルロゴのパス
	const char* const kLogoGraphPath = "Resources\\Image\\Logo.png";
}

SceneTitle::SceneTitle() :
	mGraphLogo(-1),
	mMenuChoice(0),
	mArrowPos()
{
}

void SceneTitle::InitializeScene()
{
	mGraphLogo = LoadGraph(kLogoGraphPath);
}

void SceneTitle::EndScene()
{
}

SceneBase* SceneTitle::UpdateScene()
{
	// 上下ボタンで選択場所を移動
	if (InputManager::GetInstance().IsPressed(Input::Action::Up)) mMenuChoice--;
	if (InputManager::GetInstance().IsPressed(Input::Action::Down)) mMenuChoice++;

	// 選択場所を項目の範囲内に収める
	mMenuChoice = (mMenuChoice + Choice::Max) % Choice::Max;

	// 決定ボタンが押されたら項目を選ぶ
	if (InputManager::GetInstance().IsPressed(Input::Action::Confirm))
	{
		switch (mMenuChoice)
		{
		case Choice::Start:

			GetFader()->StartFadeOut<SceneMain>();

			break;

		case Choice::Quit:



			break;
		}
	}

	return this;
}

void SceneTitle::DrawScene()
{
	DrawString(360, 400, "はじめる", mMenuChoice == 0 ? Color::kYellow : Color::kGray);
	DrawString(360, 440, "やめる", mMenuChoice == 1 ? Color::kYellow : Color::kGray);

	Vector2 pos = kArrowBasePos;
	pos.y += kArrowMoveOffset * mMenuChoice;
	DrawBox(pos.x-10, pos.y - 10, pos.x+10, pos.y+10, Color::kWhite, 1);

	DrawGraph(kLogoPos.x, kLogoPos.y, mGraphLogo, true);
}
