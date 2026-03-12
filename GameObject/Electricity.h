#pragma once

#include "GameObject.h"

class WireManager;
class SceneMain;
class HouseManager;

class Electricity : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="manager">オブジェクトマネージャーのポインタ</param>
	/// <param name="wireMgr">電線マネージャーのポインタ</param>
	/// <param name="scene">シーンメインのポインタ
	/// <param name="houseMgr">住宅マネージャーのポインタ</param>
	Electricity(ObjectManager* manager, WireManager* wireMgr, SceneMain* scene, HouseManager* houseMgr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Electricity();

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

	void StartMove() { mIsStart = true; }

private:

	/// <summary>
	/// 他の電線に移動する
	/// </summary>
	void MoveToOtherWire(Vector2& newPos);

	/// <summary>
	/// 固定電線に移動する
	/// </summary>
	void MoveToFixedWire(Vector2& newPos);

	/// <summary>
	/// 住宅に移動し終わった処理
	/// </summary>
	void MovedToHouse(Vector2& newPos);

	/// <summary>
	/// 電線のマネージャーのポインタ
	/// </summary>
	WireManager* mPtrWireManager;

	/// <summary>
	/// シーンへのポインタ
	/// </summary>
	SceneMain* mPtrSceneMain;

	/// <summary>
	/// 住宅のマネージャーのポインタ
	/// </summary>
	HouseManager* mPtrHouseManager;

	/// <summary>
	/// 電線上の開始点
	/// </summary>
	Vector2 mStartPos;
	/// <summary>
	/// 電線上の終点
	/// </summary>
	Vector2 mEndPos;

	/// <summary>
	/// 移動速度
	/// </summary>
	float mSpeed;

	bool mIsStart;
};
