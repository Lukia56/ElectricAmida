#include "Rank.h"
#include <DxLib.h>
#include <vector>
#include "../Easing/Tween.h"
#include "../Utility/Color.h"
#include "../System/SoundManager.h"

namespace
{
	const char* const kRankGraphPath = "Resources\\Image\\Rank.png";
}

Rank::Rank(ObjectManager* manager) :
	GameObject(manager),
	mGraphs(),
	mCurrentGraph(0),
	mScale(1.0f),
	mAlpha(0.0f),
	mTween(nullptr),
	mPosY(360.0f),
	mFillAlpha(0.0f)
{
}

Rank::~Rank()
{
}

void Rank::InitGameObject()
{
	LoadDivGraph(kRankGraphPath, 6, 6, 1, 178, 186, mGraphs.data());

	mTween = new Tween();

	std::vector<Animation::Keyframe> keyframes;
	keyframes.emplace_back(Animation::Keyframe{ 0.0f, 0, Animation::Ease::Linear });
	keyframes.emplace_back(Animation::Keyframe{ 255.0f, 15 });
	mTween->StartAnim(&mAlpha, keyframes);
}

void Rank::EndGameObject()
{
	for (int i = mGraphs.size() - 1; i > 0; i--)
	{
		DeleteGraph(mGraphs[i]);
	}

	delete mTween;
}

void Rank::Update()
{
	mTween->Update();
}

void Rank::Draw()
{
}

void Rank::PostDraw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, mAlpha);

	DrawRotaGraph(240, mPosY, mScale, 0, mGraphs[mCurrentGraph], true);

	// 白で塗りつぶす
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, mFillAlpha);
	FillColorGraph(mGraphs[mCurrentGraph], Vector2(240.0f, mPosY), mScale);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Rank::DrawImGui()
{
}

void Rank::RankUp()
{
	// ランクの上限を超えるなら早期リターン
	if (mCurrentGraph >= mGraphs.size()) return;

	mCurrentGraph++;

	std::vector<Animation::Keyframe> keyframes;
	keyframes.emplace_back(Animation::Keyframe{ mScale, 0, Animation::Ease::QuadOut });
	keyframes.emplace_back(Animation::Keyframe{ mScale * 1.2f, 15, Animation::Ease::QuadIn });
	keyframes.emplace_back(Animation::Keyframe{ mScale * 1.1f, 30 });
	mTween->StartAnim(&mScale, keyframes);

	keyframes.clear();
	keyframes.emplace_back(Animation::Keyframe{ 255.0f, 0, Animation::Ease::Linear });
	keyframes.emplace_back(Animation::Keyframe{ 0.0f, 20 });
	mTween->StartAnim(&mFillAlpha, keyframes);

	SoundManager::GetInstance().PlaySE(Sound::SE::RankUp, 32100 + 3000 * mCurrentGraph);
}

void Rank::ShowFinalRank(int score)
{
	mCurrentGraph = CalculateRank(score);

	std::vector<Animation::Keyframe> keyframes;
	keyframes.emplace_back(Animation::Keyframe{ mScale, 0, Animation::Ease::QuadOut });
	keyframes.emplace_back(Animation::Keyframe{ mScale * 0.8f, 20, Animation::Ease::ElasticOut });
	keyframes.emplace_back(Animation::Keyframe{ mScale, 70 });
	mTween->StartAnim(&mScale, keyframes);

	keyframes.clear();
	keyframes.emplace_back(Animation::Keyframe{ 0.0f, 0, Animation::Ease::ExpoIn });
	keyframes.emplace_back(Animation::Keyframe{ 255.0f, 25, Animation::Ease::Linear });
	keyframes.emplace_back(Animation::Keyframe{ 0.0f, 50 });
	mTween->StartAnim(&mFillAlpha, keyframes);

	SoundManager::GetInstance().PlaySE(Sound::SE::ShowRank);
}

void Rank::Remove()
{
	std::vector<Animation::Keyframe> keyframes;
	keyframes.emplace_back(Animation::Keyframe{ mPosY, 0, Animation::Ease::BackIn });
	keyframes.emplace_back(Animation::Keyframe{ mPosY - 100, 30 });
	mTween->StartAnim(&mPosY, keyframes);

	keyframes.clear();
	keyframes.emplace_back(Animation::Keyframe{ 255.0f, 0, Animation::Ease::QuartIn });
	keyframes.emplace_back(Animation::Keyframe{ 0.0f, 30 });
	mTween->StartAnim(&mAlpha, keyframes);
}

void Rank::FillColorGraph(int graph, Vector2 pos, float scale)
{
	// 画像のサイズを取得する
	int width, height;
	GetGraphSize(graph, &width, &height);
	width *= 0.5f * scale;
	height *= 0.5f * scale;

	SetUseZBufferFlag(TRUE);

	// マスク用の図形
	DrawBoxToZBuffer(pos.x - width, pos.y - height, pos.x + width, pos.y + height, TRUE, DX_ZWRITE_MASK);
	// 塗りつぶす画像
	DrawRotaGraphToZBuffer(pos.x, pos.y, scale, 0, graph, DX_ZWRITE_CLEAR);
	// 塗りつぶし
	DrawBox(pos.x - width, pos.y - height, pos.x + width, pos.y + height, Color::kWhite, TRUE);

	SetUseZBufferFlag(FALSE);
}

int Rank::CalculateRank(int score)
{
	if (score >= 18) return 5;
	if (score >= 14) return 4;
	if (score >= 9) return 3;
	if (score >= 5) return 2;
	if (score >= 2) return 1;

	return 0;
}
