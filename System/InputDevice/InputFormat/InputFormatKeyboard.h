#pragma once

#include "InputFormatBase.h"

/// <summary>
/// キーボードのキーコードの管理と押下状態を検出するクラス
/// </summary>
class InputFormatKeyboard : public InputFormatBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// ボタンを登録する
	/// </summary>
	InputFormatKeyboard();

	/// <summary>
	/// ボタンの押下状態を取得する
	/// </summary>
	/// <returns>押されていたらtrue</returns>
	bool CheckButtonState(const std::string name) override;
};
