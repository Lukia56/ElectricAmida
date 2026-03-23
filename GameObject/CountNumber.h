#pragma once

#include "GameObject.h"

class Tween;

class CountNumber :  public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="manager">オブジェクトマネージャーのポインタ</param>
	/// <param name="graph">表示する画像のグラフィックハンドル</param>
	CountNumber(ObjectManager* manager, int graph);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~CountNumber() = default;

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
	/// 描画処理の前に実行する処理
	/// </summary>
	virtual void PreDraw() override;

	/// <summary>
	/// ImGuiの描画
	/// </summary>
	void DrawImGui() override;

private:

	int mGraph;

	float mAngle;

	float mScale;

	float mAlpha;

	Tween* mTween;
};
