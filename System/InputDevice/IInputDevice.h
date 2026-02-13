#pragma once

#include <string>

/// <summary>
/// 入力デバイスのインターフェース
/// </summary>
class IInputDevice
{
public:

	/// <summary>
	/// 初期化処理
	/// 押下状態を初期化する
	/// </summary>
	virtual void Initialize() = 0;

	/// <summary>
	/// 入力情報の更新処理
	/// </summary>
	virtual void Update() = 0;

	/// <summary>
	/// 指定したボタンが押されているか調べる
	/// </summary>
	/// <param name="button">ボタンのID</param>
	/// <returns>入力結果 押されていたらtrueを返す</returns>
	virtual bool IsHeld(std::string button) const = 0;

	/// <summary>
	/// 指定したボタンが押された瞬間か調べる
	/// </summary>
	/// <param name="button">ボタンのID</param>
	/// <returns>入力結果 押されていたらtrueを返す</returns>
	virtual bool IsPressed(std::string button) const = 0;

	/// <summary>
	/// 指定したボタンが離された瞬間か調べる
	/// </summary>
	/// <param name="button">ボタンのID</param>
	/// <returns>入力結果 離されていたらtrueを返す</returns>
	virtual bool IsReleased(std::string button) const = 0;
};
