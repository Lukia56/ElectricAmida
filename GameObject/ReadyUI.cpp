#include "ReadyUI.h"
#include <DxLib.h>
#include "../Easing/Tween.h"
#include "../System/InputManager.h"

ReadyUI::ReadyUI(ObjectManager* manager) :
	GameObject(manager),
	mAlpha(0),
	mScale(1),
	mGraphText(-1),
	mIsStarted(false),
	mTween(nullptr)
{
}

void ReadyUI::InitGameObject()
{
	mGraphText = LoadGraph("Resources\\Image\\ready.png");

	mTween = new Tween();
}

void ReadyUI::EndGameObject()
{
}

void ReadyUI::Update()
{
	if (InputManager::GetInstance().IsPressed(Input::Action::Confirm))
	{
		mIsStarted = true;

		std::vector<Animation::Keyframe> keyframes;
		keyframes.emplace_back(Animation::Keyframe{ 1.0f, 0, Animation::Ease::Linear });
		keyframes.emplace_back(Animation::Keyframe{ 1.5f, 60 });
		mTween->StartAnim(&mScale, keyframes);

		keyframes.clear();
		keyframes.emplace_back(Animation::Keyframe{ 1.0f, 0, Animation::Ease::Linear });
		keyframes.emplace_back(Animation::Keyframe{ 1.0f, 60, Animation::Ease::Linear });
		keyframes.emplace_back(Animation::Keyframe{ 0.0f, 70 });
		mTween->StartAnim(&mScale, keyframes);
	}

	mTween->Update();
}

void ReadyUI::Draw()
{
	DrawRotaGraph(240, 360, mScale, 0, mGraphText, 1);
}

void ReadyUI::PostDraw()
{
}

void ReadyUI::DrawImGui()
{
}
