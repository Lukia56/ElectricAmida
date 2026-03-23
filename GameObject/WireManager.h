#pragma once

#include "GameObject.h"
#include <vector>
#include "../Collision/Collision2D.h"

class SceneMain;

struct Wire
{
	LineSegment line;
	bool enable;
};

/// <summary>
/// 電線のリスト
/// </summary>
using WireList = std::vector<Wire>;

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
	/// <param name="scene">メインシーンのポインタ</param>
	WireManager(ObjectManager* manager, SceneMain* scene);

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

	void PostDraw() override;

	/// <summary>
	/// 電線リストに電線を追加する
	/// </summary>
	void AddWire(Wire& line);

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

	/// <summary>
	/// インデックスを指定して電線の有効状態を変更する
	/// </summary>
	/// <param name="index">インデックス</param>
	/// <param name="enable">状態</param>
	void SetWireEnable(const int index, const bool enable) { mWireList[index].enable = enable; }

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
	void CreateAddWire();

	bool CanCreateWire();

	/// <summary>
	/// 点線を描画する
	/// </summary>
	/// <param name="start">開始点</param>
	/// <param name="end">終点</param>
	/// <param name="color">線の色</param>
	/// <param name="dotLen">点の長さ</param>
	/// <param name="spaceLen">隙間の長さ</param>
	void DrawDottedLine(const Vector2& start, const Vector2& end, unsigned int color, float dotLen, float spaceLen);

	/// <summary>
	/// シーンのポインタ
	/// </summary>
	SceneMain* mPtrScene;

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

	/// <summary>
	/// 追加電線の準備中にならす音のタイマー
	/// </summary>
	float mSeTimer;
};
