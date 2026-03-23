#pragma once

#include "GameObject.h"
#include <array>

class SceneMain;

class CountdownManager : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="manager">オブジェクトマネージャーのポインタ</param>
	/// <param name="scene">メインシーンのポインタ</param>
	CountdownManager(ObjectManager* manager, SceneMain* scene);

	~CountdownManager() = default;

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
	/// ImGuiの描画
	/// </summary>
	void DrawImGui() override;

private:

	std::array<int, 3> mNumberGraphs;

	SceneMain* mScene;

	// 現在表示しているカウント
	int mCurrentCounting;
};
