#include "ReadyUI.h"
#include <DxLib.h>
#include <cmath>
#include "../Easing/Tween.h"
#include "../System/InputManager.h"
#include "../Scene/SceneMain.h"
#include "../System/Time.h"
#include "../System/SoundManager.h"
#include "../Utility/Math.h"

namespace
{
	constexpr float kDelayStartTime = 1.0f;

	constexpr float kTextScalingSpeed = 0.025f;
	constexpr float kTextScalingRange = 0.025f;
}

ReadyUI::ReadyUI(ObjectManager* manager, SceneMain* scene) :
	GameObject(manager),
	mTextReadyAlpha(255),
	mTextStartAlpha(0),
	mScale(1),
	mGraphTextReady(-1),
	mGraphTextStart(-1),
	mIsStarted(false),
	mScene(scene),
	mTween(nullptr),
	mStartTimer(kDelayStartTime),
	mAnimationTimer(0.0f)
{
}

void ReadyUI::InitGameObject()
{
	mGraphTextReady = LoadGraph("Resources\\Image\\ready.png");
	mGraphTextStart = LoadGraph("Resources\\Image\\start.png");

	mTween = new Tween();
}

void ReadyUI::EndGameObject()
{
}

void ReadyUI::Update()
{
	if (!mIsStarted && InputManager::GetInstance().IsReleased(Input::Action::Confirm))
	{
		mIsStarted = true;

		std::vector<Animation::Keyframe> keyframes;
		keyframes.emplace_back(Animation::Keyframe{ 2.0f, 0, Animation::Ease::BounceOut });
		keyframes.emplace_back(Animation::Keyframe{ 1.0f, 12 });
		keyframes.emplace_back(Animation::Keyframe{ 1.0f, 40 });
		keyframes.emplace_back(Animation::Keyframe{ 0.7f, 46 });
		mTween->StartAnim(&mScale, keyframes);

		keyframes.clear();
		keyframes.emplace_back(Animation::Keyframe{ 255.0f, 0, Animation::Ease::Linear });
		keyframes.emplace_back(Animation::Keyframe{ 255.0f, 40, Animation::Ease::Linear });
		keyframes.emplace_back(Animation::Keyframe{ 0.0f, 46 });
		mTween->StartAnim(&mTextStartAlpha, keyframes);

		keyframes.clear();
		keyframes.emplace_back(Animation::Keyframe{ 255.0f, 0, Animation::Ease::Linear });
		keyframes.emplace_back(Animation::Keyframe{ 0.0f, 6 });
		mTween->StartAnim(&mTextReadyAlpha, keyframes);

		SoundManager::GetInstance().PlaySE(Sound::SE::GameStart);
	}

	if (mIsStarted)
	{
		mStartTimer -= Time::GetInstance().GetDeltaTime();

		if (mStartTimer < 0)
		{
			mScene->SetGameState(SceneMain::GameState::Play);
			SetState(State::EDead);
		}
	}

	mAnimationTimer += kTextScalingSpeed;

	mTween->Update();
}

void ReadyUI::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(mTextReadyAlpha));
	float scale = 1 + std::sin(mAnimationTimer) * 0.05f;
	DrawRotaGraph(240, 360, scale, 0, mGraphTextReady, 1);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(mTextStartAlpha));
	DrawRotaGraph(240, 360, mScale, 0, mGraphTextStart, 1);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void ReadyUI::PostDraw()
{
}

void ReadyUI::DrawImGui()
{
}
