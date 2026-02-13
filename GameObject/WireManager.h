#pragma once

#include "GameObject.h"
#include <vector>
#include "../Collision/Collision2D.h"

/// <summary>
/// 電線のリスト
/// </summary>
using WireList = std::vector<LineSegment>;

namespace FixedWire
{
	// 左側の固定電線の添え字
	constexpr int kLeftIndex = 0;
	// 右側の固定電線の添え字
	constexpr int kRightIndex = 1;
}

class WireManager : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="manager">オブジェクトマネージャーのポインタ</param>
	WireManager(ObjectManager* manager);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~WireManager();

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
	/// 電線のリストを取得
	/// </summary>
	/// <returns>電線のリスト</returns>
	WireList GetWireList() const { return mWireList; }

	/// <summary>
	/// 固定電線のリストを取得
	/// </summary>
	/// <returns>固定電線のリスト</returns>
	WireList GetFixedWireList() const { return mFixedWireList; }

private:

	/// <summary>
	/// 追加電線の開始点の設定
	/// </summary>
	void SetDrawStartPos();

	/// <summary>
	/// 追加電線の終点の設定
	/// </summary>
	void SetDrawEndPos();

	/// <summary>
	/// 追加電線の生成
	/// </summary>
	void AddWire();

	/// <summary>
	/// 電線リストのデータ
	/// </summary>
	WireList mWireList;

	/// <summary>
	/// 固定電線のリストデータ
	/// </summary>
	WireList mFixedWireList;

	/// <summary>
	/// 追加しようとしている電線の線分
	/// </summary>
	LineSegment mDrawWire;
};
