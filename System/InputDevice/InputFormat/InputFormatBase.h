#pragma once

#include <unordered_map>
#include <string>

/// <summary>
/// キーコードの管理と押下状態を検出するクラス
/// </summary>
class InputFormatBase
{
public:

	/// <summary>
	/// ボタンを追加する
	/// </summary>
	/// <param name="name">ボタン名</param>
	/// <param name="keyCode">キーコード</param>
	void AddButton(const std::string name, const int keyCode);

	/// <summary>
	/// ボタンを削除する
	/// </summary>
	/// <param name="name">ボタン名</param>
	void RemoveButton(const std::string name);

	/// <summary>
	/// ボタンの押下状態を取得する
	/// </summary>
	/// <returns>押されていたらtrue</returns>
	virtual bool CheckButtonState(const std::string name) = 0;

	/// <summary>
	/// 文字列をキーコードに変換するマップを取得する
	/// </summary>
	/// <returns>文字列をキーコードに変換するマップ</returns>
	std::unordered_map<std::string, int> GetButtonStringToKeyCode() const { return mButtonStringToKeyCode; };

private:

	/// <summary>
	/// 文字列をキーコードに変換するマップ
	/// </summary>
	std::unordered_map<std::string, int> mButtonStringToKeyCode;
};