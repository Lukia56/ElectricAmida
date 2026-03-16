#pragma once

#include "GameObject.h"

class Tree : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="manager">オブジェクトマネージャーのポインタ</param>
	/// <param name="graph">木のグラフィックハンドル</param>
	/// <param name="pos">座標</param>
	Tree(ObjectManager* manager, int graph, Vector2& pos);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Tree() = default;

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

	/// <summary>
	/// ImGuiの描画
	/// </summary>
	void DrawImGui() override;

private:

	int mGraph;
};
