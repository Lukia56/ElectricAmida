#pragma once

#include "InputFormatBase.h"
#include <string>

/// <summary>
/// マウスのボタンのキーコードの管理と押下状態を検出するクラス
/// </summary>
class InputFormatMouseButton : public InputFormatBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// ボタンを登録する
	/// </summary>
	InputFormatMouseButton();

	/// <summary>
	/// ボタンの押下状態を取得する
	/// </summary>
	/// <returns>押されていたらtrue</returns>
	bool CheckButtonState(const std::string name) override;
};

