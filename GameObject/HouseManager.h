#pragma once

#include "GameObject.h"
#include <vector>

class WireManager;
class House;

class HouseManager :  public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="manager">オブジェクトマネージャーのポインタ</param>
	/// <param name="wireMgr">電線マネージャーのポインタ</param>
	HouseManager(ObjectManager* manager, WireManager* wireMgr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~HouseManager();

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
	/// ランダムな住宅を有効にする
	/// </summary>
	void EnableRandomHouse();

	/// <summary>
	/// 家の数を取得
	/// </summary>
	/// <returns></returns>
	int GetHouseNum();

	/// <summary>
	/// 一番近い住宅を取得する
	/// </summary>
	/// <param name="pos">調べたい座標</param>
	/// <returns>一番近い住宅のゲームオブジェクト</returns>
	House* GetNearestHouse(Vector2 pos);

	/// <summary>
	/// 電線のマネージャーの取得
	/// </summary>
	/// <returns>電線のマネージャーのポインタ</returns>
	WireManager* GetWireManager() const { return mPtrWireManager; }

private:

	/// <summary>
	/// 電線マネージャーのポインタ
	/// </summary>
	WireManager* mPtrWireManager;

	std::vector<House*> mObjHouseList;
};
