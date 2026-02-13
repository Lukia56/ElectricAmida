#pragma once

#include "InputDeviceBase.h"

/// <summary>
/// キーボードの処理をするクラス
/// </summary>
class InputDeviceKeyboard : public InputDeviceBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	InputDeviceKeyboard();

	/// <summary>
	/// デバイス固有の初期化処理
	/// フォーマットの追加を行う
	/// </summary>
	void InitializeDevice() override;

	/// <summary>
	/// デバイス固有の更新処理
	/// </summary>
	void UpdateDevice() override;
};
