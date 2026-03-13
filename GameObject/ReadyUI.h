#pragma once

#include "GameObject.h"

class SceneMain;
class Tween;

class ReadyUI : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="manager">オブジェクトマネージャーのポインタ</param>
	/// <param name="scene">シーンのポインタ</param>
	ReadyUI(ObjectManager* manager, SceneMain* scene);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ReadyUI() = default;

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

	/// <summary>
	/// 不透明度
	/// </summary>
	float mTextReadyAlpha;
	float mTextStartAlpha;

	float mScale;

	int mGraphTextReady;

	int mGraphTextStart;

	bool mIsStarted;

	SceneMain* mScene;

	Tween* mTween;

	float mStartTimer;
};
