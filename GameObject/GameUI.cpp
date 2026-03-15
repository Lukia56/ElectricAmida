#include "GameUI.h"
#include <DxLib.h>
#include <string>
#include "../Utility/Color.h"
#include "../Scene/SceneMain.h"

namespace
{
	const char* const kMoneyIconPath = "Resources\\Image\\IconMoney.png";
	const char* const kLightBulbIconPath = "Resources\\Image\\IconLightBulb.png";
	const char* const kTimerIconPath = "Resources\\Image\\IconTimer.png";
}

GameUI::GameUI() :
	mSceneMain(nullptr),
	mGraphMoneyIcon(-1),
	mGraphLightBulbIcon(-1),
	mGraphTimerIcon(-1)
{
}

GameUI::~GameUI()
{
}

void GameUI::Init(SceneMain* scene)
{
	mSceneMain = scene;

	mGraphMoneyIcon = LoadGraph(kMoneyIconPath);
	mGraphLightBulbIcon = LoadGraph(kLightBulbIconPath);
	mGraphTimerIcon = LoadGraph(kTimerIconPath);
}

void GameUI::End()
{
	DeleteGraph(mGraphMoneyIcon);
	DeleteGraph(mGraphLightBulbIcon);
	DeleteGraph(mGraphTimerIcon);
}

void GameUI::Draw()
{
	//DrawGraph(350, 32, mGraphMoneyIcon, 1);
	DrawGraph(220, 20, mGraphLightBulbIcon, 1);
	DrawGraph(590, 32, mGraphTimerIcon, 1);

	//DrawString(400, 32, std::to_string(mSceneMain->GetBudget()).c_str(), Color::kWhite);
	DrawString(270, 30, std::to_string(mSceneMain->GetSuccessNum()).c_str(), Color::kWhite);
	DrawString(640, 32, std::to_string(mSceneMain->GetRemainTime()).c_str(), Color::kWhite);
}
