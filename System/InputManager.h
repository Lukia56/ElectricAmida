#pragma once

#include <unordered_map>
#include <array>
#include <vector>
#include <string>
#include <memory>

class InputDeviceBase;

namespace Input
{
	enum class Action
	{
		Up,
		Down,
		Left,
		Right,
		MenuUp,
		MenuDown,
		MenuLeft,
		MenuRight,
		Confirm,
		Draw,
		Pause,
		StartMove,
		Length
	};

	enum class Device
	{
		Keyboard,
		Mouse,
		Length
	};
}

/// <summary>
/// 入力処理を管理するクラス
/// </summary>
class InputManager
{
public:

	/// <summary>
	/// 入力マネージャーのインスタンスの生成、取得を行う
	/// 初めて呼び出すときは生成、
	/// 2回目以降は取得を行う
	/// </summary>
	/// <returns>インスタンス</returns>
	static InputManager& GetInstance();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~InputManager();

	/// <summary>
	/// 初期化処理
	/// ボタンの割り当て等を行う
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// 各デバイスの入力情報を更新する
	/// </summary>
	void Update();

	/// <summary>
	/// ボタンを割り当てる
	/// </summary>
	/// <param name="action">割り当てたいアクションID</param>
	/// <param name="device">割り当てるボタンのデバイス名</param>
	/// <param name="button">割り当てるボタン名</param>
	void BindButton(Input::Action action, std::string device, std::string button);

	/// <summary>
	/// 指定したボタンアクションに割り当てられたボタンをすべて削除する
	/// </summary>
	/// <param name="buttonAction">解除したいボタンアクションID</param>
	void UnbindButton(Input::Action action);

	/// <summary>
	/// 指定したボタンアクションが押されているか調べる
	/// </summary>
	/// <returns>入力結果 押されていたらtrueを返す</returns>
	bool IsHeld(Input::Action action);

	/// <summary>
	/// 指定したボタンアクションが押された瞬間か調べる
	/// </summary>
	/// <returns>入力結果 押されていたらtrueを返す</returns>
	bool IsPressed(Input::Action action);

	/// <summary>
	/// 指定したボタンアクションが離された瞬間か調べる
	/// </summary>
	/// <returns>入力結果 離されていたらtrueを返す</returns>
	bool IsReleased(Input::Action action);

	/// <summary>
	/// デバイスを取得する
	/// </summary>
	/// <typeparam name="T">取得したいデバイスの型</typeparam>
	/// <returns>取得に成功したらデバイスのポインタを返す。失敗したらnullptrを返す</returns>
	template <class T>
	T* GetDevice() const;

private:

	/// <summary>
	/// 入力状態の状態
	/// </summary>
	enum class InputState
	{
		EHeld,		// 押し続けている
		EPressed,	// 押された瞬間
		EReleased	// 離された瞬間
	};

	// デバイス名とボタン名を格納するためのマップ
	using BindData = std::unordered_map<std::string, std::string>;
	// ボタンの情報を格納するための配列
	using BindList = std::vector<BindData>;
	// アクションごとのボタン情報のリストを格納するためのマップ
	using ActionMap = std::unordered_map<Input::Action, BindList>;

	/// <summary>
	/// コンストラクタ
	/// インスタンスの生成を禁止する
	/// </summary>
	InputManager();

	// コピーコンストラクタ禁止
	InputManager(const InputManager&) = delete;
	// コピー代入禁止
	InputManager& operator=(const InputManager&) = delete;
	// ムーブ禁止
	InputManager(InputManager&&) = delete;
	// ムーブ代入禁止
	InputManager& operator=(InputManager&&) = delete;

	/// <summary>
	/// 指定したボタンアクションの状態を取得する
	/// ボタンアクションに割り当てられたすべてのボタンの入力状態を調べる
	/// </summary>
	/// <param name="button">ボタンアクションID</param>
	/// <param name="state">入力状態</param>
	/// <returns>ボタンアクションに割り当てられたボタンが１つでも押されていたらtrue、
	/// 1つも押されていなかったらfalseを返す</returns>
	bool GetState(Input::Action button, InputState state);

	/// <summary>
	/// ボタンアクションのマップ
	/// </summary>
	ActionMap mActionMap;

	/// <summary>
	/// 入力デバイスのマップ
	/// </summary>
	std::unordered_map<std::string, std::shared_ptr<InputDeviceBase>> mDevices;
};

template<class T>
inline T* InputManager::GetDevice() const
{
	// 型が一致する要素を探す
	for (const auto& device : mDevices)
	{
		// 指定したデバイスにキャスト
		T* result = dynamic_cast<T*>(device.second.get());

		// キャストに成功したらポインタを返す
		if (result != nullptr) return result;
	}

	// 型が見つからなかったためnullptrを返す
	return nullptr;
}
