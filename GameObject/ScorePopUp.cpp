#include "ScorePopUp.h"
#include "../Easing/Tween.h"
#include "../Utility/Color.h"

ScorePopUp::ScorePopUp(ObjectManager* manager) :
	GameObject(manager),
	mOffsetPos(),
	mAlpha(0.0f),
	mTween(nullptr)
{
}

void ScorePopUp::InitGameObject()
{
	mTween = new Tween();

	std::vector<Animation::Keyframe> keyframes;
	keyframes.emplace_back(Animation::Keyframe{ mOffsetPos.y + 20, 0, Animation::Ease::QuadOut });
	keyframes.emplace_back(Animation::Keyframe{ mOffsetPos.y + 0, 20, Animation::Ease::QuadIn });
	keyframes.emplace_back(Animation::Keyframe{ mOffsetPos.y - 20, 40 });
	mTween->StartAnim(&mOffsetPos.y, keyframes);

	keyframes.clear();
	keyframes.emplace_back(Animation::Keyframe{ 0, 0, Animation::Ease::QuadOut });
	keyframes.emplace_back(Animation::Keyframe{ 255, 20, Animation::Ease::QuadIn });
	keyframes.emplace_back(Animation::Keyframe{ 0, 40 });
	mTween->StartAnim(&mAlpha, keyframes);
}

void ScorePopUp::EndGameObject()
{
	delete mTween;
}

void ScorePopUp::Update()
{
	mTween->Update();

	if (mAlpha == 0.0f) SetState(State::EDead);
}

void ScorePopUp::Draw()
{
	Vector2 pos = GetPosition() + mOffsetPos;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, mAlpha);

	DrawString(pos.x, pos.y, "+1", Color::kWhite);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void ScorePopUp::DrawImGui()
{
}
