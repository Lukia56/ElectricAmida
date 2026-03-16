#pragma once

#include "GameObject.h"

class Tween;

class ScorePopUp : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="manager">オブジェクトマネージャーのポインタ</param>
	ScorePopUp(ObjectManager* manager);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ScorePopUp() = default;

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

	Vector2 mOffsetPos;

	float mAlpha;

	Tween* mTween;
};
