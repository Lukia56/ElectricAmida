#pragma once

#include "InputDeviceBase.h"
#include "../Utility/Vector.h"
#include <array>
#include <memory>

namespace Mouse
{
	/// <summary>
	/// 座標ログを残す数
	/// </summary>
	constexpr int kPosLogNum = 2;
}

/// <summary>
/// マウスの処理をするクラス
/// </summary>
class InputDeviceMouse : public InputDeviceBase, public std::enable_shared_from_this<InputDeviceMouse>
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	InputDeviceMouse();

	/// <summary>
	/// デバイス固有の初期化処理
	/// フォーマットの追加を行う
	/// </summary>
	void InitializeDevice() override;

	/// <summary>
	/// デバイス固有の更新処理
	/// </summary>
	void UpdateDevice() override;

	/// <summary>
	/// マウスの座標を取得する
	/// </summary>
	/// <returns>現在のマウスの座標</returns>
	Vector2 GetPos() const { return mPosLog[0]; }

	/// <summary>
	/// マウスの移動量を取得する
	/// </summary>
	/// <returns>マウスの移動量</returns>
	Vector2 GetRelativePos() const { return mPosLog[0] - mPosLog[1]; }

	/// <summary>
	/// マウスホイールの回転量を取得する
	/// </summary>
	/// <returns>マウスホイールの回転量</returns>
	int GetWheelRot() const { return mWheelRot; };

	/// <summary>
	/// マウスを固定するかどうかを設定する
	/// </summary>
	/// <param name="fix">固定するならtrue</param>
	void SetFixMouse(const bool fix) { mIsFixMouse = fix; }

private:

	/// <summary>
	/// 座標ログの更新
	/// </summary>
	void UpdatePosLog();

	/// <summary>
	/// マウスの固定処理
	/// </summary>
	void FixMouse();

	/// <summary>
	/// マウスホイールの回転量を更新
	/// </summary>
	void UpdateWheetRot();

	/// <summary>
	/// マウスの座標のログ
	/// 移動量検知に使用する
	/// </summary>
	std::array<Vector2, Mouse::kPosLogNum> mPosLog;

	/// <summary>
	/// マウスホイールの回転量
	/// DXライブラリの関数だと1フレームに複数回呼び出すと、
	/// 最初の1回しか回転量を受け取れないため、変数に格納
	/// </summary>
	int mWheelRot;

	/// <summary>
	/// マウスを固定するかどうか
	/// 視点移動など無限にマウスを移動させたいときにtrueにする
	/// </summary>
	bool mIsFixMouse;
};
