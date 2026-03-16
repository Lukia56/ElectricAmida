#include "GameUI.h"
#include <DxLib.h>
#include <string>
#include "../Utility/Color.h"
#include "../Utility/Vector.h"
#include "../Scene/SceneMain.h"
#include "../Easing/Tween.h"
#include "../GameObject/ScorePopUp.h"

namespace
{
	const char* const kLightBulbIconPath = "Resources\\Image\\IconLightBulb.png";
	const char* const kTimerIconPath = "Resources\\Image\\IconTimer.png";

	const Vector2 kLightIconPos = { 150, 20 };
	const Vector2 kTimerIconPos = { 280, 20 };

	const Vector2 kLightTextPos = { 210, 30 };
	const Vector2 kTimerTextPos = { 340, 30 };
}

GameUI::GameUI() :
	mSceneMain(nullptr),
	mGraphLightBulbIcon(-1),
	mGraphTimerIcon(-1),
	mLightIconPos(kLightIconPos),
	mTimerIconPos(kTimerIconPos),
	mLightTextPos(kLightTextPos),
	mTimerTextPos(kTimerTextPos),
	mTween(nullptr)
{
}

GameUI::~GameUI()
{
}

void GameUI::Init(SceneMain* scene)
{
	mSceneMain = scene;

	mGraphLightBulbIcon = LoadGraph(kLightBulbIconPath);
	mGraphTimerIcon = LoadGraph(kTimerIconPath);

	mTween = new Tween();
}

void GameUI::End()
{
	DeleteGraph(mGraphLightBulbIcon);
	DeleteGraph(mGraphTimerIcon);

	delete mTween;
}

void GameUI::Update()
{
	mTween->Update();
}

void GameUI::Draw()
{
	DrawGraph(mLightIconPos.x, mLightIconPos.y, mGraphLightBulbIcon, 1);
	DrawGraph(mTimerIconPos.x, mTimerIconPos.y, mGraphTimerIcon, 1);

	DrawString(mLightTextPos.x, mLightTextPos.y, std::to_string(mSceneMain->GetSuccessNum()).c_str(), Color::kWhite);
	DrawString(mTimerTextPos.x, mTimerTextPos.y, std::to_string(mSceneMain->GetRemainTime()).c_str(), Color::kWhite);
}

void GameUI::CountUpLightNum()
{
	std::vector<Animation::Keyframe> keyframes;
	keyframes.emplace_back(Animation::Keyframe{ mLightTextPos.y + 10, 0, Animation::Ease::QuadOut });
	keyframes.emplace_back(Animation::Keyframe{ mLightTextPos.y - 5, 10, Animation::Ease::QuadInOut });
	keyframes.emplace_back(Animation::Keyframe{ mLightTextPos.y + 3, 20, Animation::Ease::QuadInOut });
	keyframes.emplace_back(Animation::Keyframe{ mLightTextPos.y, 40});
	mTween->StartAnim(&mLightTextPos.y, keyframes);
	
	ScorePopUp* popup = new ScorePopUp(mSceneMain->GetObjectManager());
	popup->Init();
	popup->SetPosition(Vector2(mLightTextPos.x + 15, mLightTextPos.y));
}

void GameUI::CountDownTimer()
{
}
