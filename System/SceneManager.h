#pragma once

class Game;
class SceneBase;

/// <summary>
/// シーンを管理するクラス
/// </summary>
class SceneManager
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	SceneManager();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SceneManager();

	/// <summary>
	/// シーンの更新処理
	/// </summary>
	void Update();
	
	/// <summary>
	/// シーンの描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// ImGuiの描画処理
	/// </summary>
	void DrawImGui();

private:

	/// <summary>
	/// 現在のシーンのポインタ
	/// </summary>
	SceneBase* mPtrScene;
};