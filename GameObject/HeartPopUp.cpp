#include "HeartPopUp.h"
#include "../Easing/Tween.h"

namespace
{
	const char* const kGraphHeartPath = "Resources\\Image\\Heart.png";
}

HeartPopUp::HeartPopUp(ObjectManager* manager) :
	GameObject(manager),
	mGraph(-1),
	mOffsetPos(),
	mAlpha(0.0f),
	mTween(nullptr)
{
}

void HeartPopUp::InitGameObject()
{
	mGraph = LoadGraph(kGraphHeartPath);

	mTween = new Tween();

	std::vector<Animation::Keyframe> keyframes;
	keyframes.emplace_back(Animation::Keyframe{ mOffsetPos.y + 20, 0, Animation::Ease::Linear });
	keyframes.emplace_back(Animation::Keyframe{ mOffsetPos.y - 60, 60 });
	mTween->StartAnim(&mOffsetPos.y, keyframes);

	keyframes.clear();
	keyframes.emplace_back(Animation::Keyframe{ mOffsetPos.x, 0, Animation::Ease::QuadOut });
	keyframes.emplace_back(Animation::Keyframe{ mOffsetPos.x + 10, 15, Animation::Ease::QuadInOut });
	keyframes.emplace_back(Animation::Keyframe{ mOffsetPos.x - 10, 45, Animation::Ease::QuadIn });
	keyframes.emplace_back(Animation::Keyframe{ mOffsetPos.x, 60 });
	mTween->StartAnim(&mOffsetPos.x, keyframes);

	keyframes.clear();
	keyframes.emplace_back(Animation::Keyframe{ 0, 0, Animation::Ease::QuadOut });
	keyframes.emplace_back(Animation::Keyframe{ 255, 8, Animation::Ease::Linear });
	keyframes.emplace_back(Animation::Keyframe{ 255, 52, Animation::Ease::QuadIn });
	keyframes.emplace_back(Animation::Keyframe{ 0, 60 });
	mTween->StartAnim(&mAlpha, keyframes);
}

void HeartPopUp::EndGameObject()
{
	delete mTween;

	DeleteGraph(mGraph);
}

void HeartPopUp::Update()
{
	mTween->Update();

	if (mAlpha == 0.0f) SetState(State::EDead);
}

void HeartPopUp::Draw()
{
	Vector2 pos = GetPosition() + mOffsetPos;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, mAlpha);

	DrawRotaGraph(pos.x, pos.y, 2, 0, mGraph, 1);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void HeartPopUp::DrawImGui()
{
}
