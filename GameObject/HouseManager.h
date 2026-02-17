#pragma once

#include "GameObject.h"
#include <vector>

class WireManager;
class House;

struct HouseData
{
	House* house;
	int wireIndex;
};

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

private:

	/// <summary>
	/// 電線マネージャーのポインタ
	/// </summary>
	WireManager* mPtrWireManager;

	std::vector<HouseData> mObjHouseList;
};
