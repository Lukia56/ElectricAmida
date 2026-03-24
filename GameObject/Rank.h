#pragma once

#include "GameObject.h"
#include <array>

class Tween;

class Rank : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="manager">オブジェクトマネージャーのポインタ</param>
	Rank(ObjectManager* manager);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Rank();

	/// <summary>
	/// ゲームオブジェクト固有の初期化処理
	/// </summary>
	void InitGameObject() override;

	/// <summary>
	/// ゲームオブジェクト固有の後処理
	/// </summary>
	void EndGameObject() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;

	void PostDraw() override;

	/// <summary>
	/// ImGuiの描画
	/// </summary>
	void DrawImGui() override;

	/// <summary>
	/// ランクアップ演出
	/// </summary>
	void RankUp();

	/// <summary>
	/// 最終的なランクを発表する演出
	/// </summary>
	void ShowFinalRank(int score);

	/// <summary>
	/// 退場演出
	/// </summary>
	void Remove();

	/// <summary>
	/// 現在のグラフィックハンドルを取得
	/// </summary>
	/// <returns></returns>
	int GetCurrentGraph() const { return mGraphs[mCurrentGraph]; }

private:

	/// <summary>
	/// 画像の塗りつぶしを行う
	/// </summary>
	void FillColorGraph(int graph, Vector2 pos, float scale);

	/// <summary>
	/// スコアからランクを計算する
	/// </summary>
	int CalculateRank(int score);

	std::array<int, 6> mGraphs;

	int mCurrentGraph;

	float mScale;

	float mAlpha;

	Tween* mTween;

	float mPosY;

	float mFillAlpha;
};
