#pragma once

#include "IInputDevice.h"
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>

class InputFormatBase;

class InputDeviceBase : public IInputDevice
{
public:

	/// <summary>
	/// 初期化処理
	/// 押下状態を初期化する
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// デバイス固有の初期化処理
	/// フォーマットの追加を行う
	/// </summary>
	virtual void InitializeDevice() = 0;

	/// <summary>
	/// 入力情報の更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// デバイス固有の更新処理
	/// </summary>
	virtual void UpdateDevice() = 0;

	/// <summary>
	/// 指定したボタンが押されているか調べる
	/// </summary>
	/// <param name="button">ボタンのID</param>
	/// <returns>入力結果 押されていたらtrueを返す</returns>
	bool IsHeld(std::string button) const override;

	/// <summary>
	/// 指定したボタンが押された瞬間か調べる
	/// </summary>
	/// <param name="button">ボタンのID</param>
	/// <returns>入力結果 押されていたらtrueを返す</returns>
	bool IsPressed(std::string button) const override;

	/// <summary>
	/// 指定したボタンが離された瞬間か調べる
	/// </summary>
	/// <param name="button">ボタンのID</param>
	/// <returns>入力結果 離されていたらtrueを返す</returns>
	bool IsReleased(std::string button) const override;

protected:

	void AddFormat(std::shared_ptr<InputFormatBase> format);

private:

	/// <summary>
	/// 入力情報のログ
	/// 0：押されていない
	/// 1：押された１回め
	/// 2以上：押され続けている回数
	/// -1：押されて離された１回め
	/// -2以下：押されて離されてからの回数
	/// </summary>
	std::unordered_map<std::string, int> mInputLog;

	/// <summary>
	/// ボタンのフォーマットへのポインタ
	/// </summary>
	std::vector<std::shared_ptr<InputFormatBase>> mFormats;
};
