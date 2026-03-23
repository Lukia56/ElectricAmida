#include "CountNumber.h"
#include <DxLib.h>
#include "../Easing/Tween.h"
#include "../Utility/Vector.h"
#include "../Utility/Math.h"

namespace
{
	const Vector2 kCenterPos = { 240, 360 };
}

CountNumber::CountNumber(ObjectManager* manager, int graph) :
	GameObject(manager),
	mGraph(graph),
	mAngle(0.0f),
	mScale(1.0f),
	mAlpha(0.0f),
	mTween(nullptr)
{
}

void CountNumber::InitGameObject()
{
	mTween = new Tween();

	std::vector<Animation::Keyframe> keyframes;
	keyframes.emplace_back(Animation::Keyframe{ 4, 0, Animation::Ease::QuintOut });
	keyframes.emplace_back(Animation::Keyframe{ 2, 20, Animation::Ease::QuintIn });
	keyframes.emplace_back(Animation::Keyframe{ 0, 40 });
	mTween->StartAnim(&mScale, keyframes);

	keyframes.clear();
	keyframes.emplace_back(Animation::Keyframe{ 45, 0, Animation::Ease::QuintOut });
	keyframes.emplace_back(Animation::Keyframe{ 0, 20, Animation::Ease::QuintIn });
	keyframes.emplace_back(Animation::Keyframe{ -45, 40 });
	mTween->StartAnim(&mAngle, keyframes);

	keyframes.clear();
	keyframes.emplace_back(Animation::Keyframe{ 0, 0, Animation::Ease::QuadOut });
	keyframes.emplace_back(Animation::Keyframe{ 255, 8, Animation::Ease::Linear });
	keyframes.emplace_back(Animation::Keyframe{ 255, 32, Animation::Ease::QuadIn });
	keyframes.emplace_back(Animation::Keyframe{ 0, 40 });
	mTween->StartAnim(&mAlpha, keyframes);
}

void CountNumber::EndGameObject()
{
}

void CountNumber::Update()
{
	mTween->Update();

	if (mAlpha == 0.0f) SetState(State::EDead);
}

void CountNumber::PreDraw()
{
	// 手前に表示されるとゲーム画面が見えないため、後ろに暗めに表示させる

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, mAlpha * 0.5f);

	DrawRotaGraph(kCenterPos.x, kCenterPos.y, mScale, Math::ToRadian(mAngle), mGraph, 1);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void CountNumber::DrawImGui()
{
}
