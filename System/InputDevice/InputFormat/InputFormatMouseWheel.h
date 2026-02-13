#pragma once

#include "InputFormatBase.h"
#include <memory>

class InputDeviceMouse;

/// <summary>
/// マウスホイールのキーコードの管理と押下状態を検出するクラス
/// </summary>
class InputFormatMouseWheel : public InputFormatBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// ボタンを登録する
	/// </summary>
	InputFormatMouseWheel();

	/// <summary>
	/// ボタンの押下状態を取得する
	/// </summary>
	/// <returns>押されていたらtrue</returns>
	bool CheckButtonState(const std::string name) override;

	/// <summary>
	/// デバイスを設定する
	/// </summary>
	/// <param name="device">デバイスのポインタ</param>
	void SetDevice(std::shared_ptr<InputDeviceMouse> device) { mPtrDevice = device; }

private:

	/// <summary>
	/// マウスのデバイスのポインタ
	/// </summary>
	std::weak_ptr<InputDeviceMouse> mPtrDevice;
};
