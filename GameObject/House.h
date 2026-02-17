#pragma once

#include "GameObject.h"

struct Wire;

class House : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="manager">オブジェクトマネージャーのポインタ</param>
	House(ObjectManager* manager);

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

	void SetEnable(const bool enable) { mIsEnabled = enable; }

private:

	/// <summary>
	/// 有効化どうか
	/// </summary>
	bool mIsEnabled;

	/// <summary>
	/// 電線
	/// </summary>
	Wire* mWire;
};
