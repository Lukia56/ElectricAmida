#pragma once

#include "GameObject.h"

class SceneMain;
class Tween;

class ResultUI : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="manager">オブジェクトマネージャーのポインタ</param>
	/// <param name="scene">シーンメインのポインタ
	ResultUI(ObjectManager* manager, SceneMain* scene);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ResultUI();

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

private:

	SceneMain* mScene;

	/// <summary>
	/// メニューで選択している場所
	/// </summary>
	int mMenuChoice;

	/// <summary>
	/// メニューの不透明度
	/// </summary>
	int mAlpha;

	/// <summary>
	/// メニューのY座標
	/// </summary>
	float mMenuY;

	Tween* mTween;
};
