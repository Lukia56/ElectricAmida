#pragma once

#include "GameObject.h"

class WireManager;
struct Wire;

class House : public GameObject
{
public:

	/// <summary>
	/// デフォルトコンストラクタ
	/// </summary>
	House() = default;

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="manager">オブジェクトマネージャーのポインタ</param>
	/// <param name="wireMgr">電線のマネージャーのポインタ</param>
	House(ObjectManager* manager, WireManager* wireMgr, int graph);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~House();

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

	void SetWireActive(bool state);

	void SetActive();

	bool IsEnable() const { return mIsEnabled; }

private:

	/// <summary>
	/// 電線のマネージャーのポインタ
	/// </summary>
	WireManager* mPtrWireManager;

	/// <summary>
	/// 有効化どうか
	/// </summary>
	bool mIsEnabled;

	/// <summary>
	/// 自身の引込線のインデックス
	/// </summary>
	int mWireIndex;

	int mGraph;
};
