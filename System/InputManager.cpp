#include "InputManager.h"
#include "../System/InputDevice/InputDeviceKeyboard.h"
#include "../System/InputDevice/InputDeviceMouse.h"

namespace
{
	const char* const kKeyDevice = "Device";
	const char* const kKeyButton = "Button";
}

namespace Input
{
	Action begin(Action) { return Action::Up; }
	Action end(Action) { return Action::Length; }
	Action operator*(Action action) { return action; }
	Action operator++(Action& action) { return action = Action(std::underlying_type<Action>::type(action) + 1); }
}

InputManager& InputManager::GetInstance()
{
	static InputManager instance;

	return instance;
}

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

void InputManager::Initialize()
{
	// デバイスにキーボードを追加
	auto keyboard = std::make_shared<InputDeviceKeyboard>();
	keyboard->Initialize();
	mDevices.emplace("Keyboard", keyboard);

	// デバイスにマウスを追加
	auto mouse = std::make_shared<InputDeviceMouse>();
	mouse->Initialize();
	mDevices.emplace("Mouse", mouse);

	// 各ボタンにボタンデータを格納できるようにするため空のリストを追加
	for (auto button : Input::Action())
	{
		// 空のボタンリストを追加
		BindList list;
		mActionMap.emplace(button, list);
	}

	BindButton(Input::Action::Up, "Keyboard", "UpArrow");
	BindButton(Input::Action::Up, "Keyboard", "W");
	BindButton(Input::Action::Up, "Mouse", "WheelUp");
	BindButton(Input::Action::Down, "Keyboard", "DownArrow");
	BindButton(Input::Action::Down, "Keyboard", "S");
	BindButton(Input::Action::Down, "Mouse", "WheelDown");
	BindButton(Input::Action::Left, "Keyboard", "LeftArrow");
	BindButton(Input::Action::Left, "Keyboard", "A");
	BindButton(Input::Action::Left, "Mouse", "LClick");
	BindButton(Input::Action::Right, "Keyboard", "RightArrow");
	BindButton(Input::Action::Right, "Keyboard", "D");
	BindButton(Input::Action::Right, "Mouse", "RClick");
	BindButton(Input::Action::Confirm, "Keyboard", "Space");
	BindButton(Input::Action::Draw, "Mouse", "LClick");
	BindButton(Input::Action::Pause, "Keyboard", "Escape");
}

void InputManager::Update()
{
	// それぞれのデバイスの更新処理を呼ぶ
	for (const auto& device : mDevices)
	{
		device.second->Update();
	}
}

void InputManager::BindButton(Input::Action action, std::string device, std::string button)
{
	// ボタン情報を生成
	BindData data;
	data.emplace(kKeyDevice, device);	// デバイスID
	data.emplace(kKeyButton, button);	// ボタン名

	// アクションマップに追加
	mActionMap.at(action).emplace_back(data);
}

void InputManager::UnbindButton(Input::Action action)
{
	// アクションのボタン情報をすべて削除する
	mActionMap.at(action).clear();
}

bool InputManager::IsHeld(Input::Action action)
{
	return GetState(action, InputState::EHeld);
}

bool InputManager::IsPressed(Input::Action action)
{
	return GetState(action, InputState::EPressed);
}

bool InputManager::IsReleased(Input::Action action)
{
	return GetState(action, InputState::EReleased);
}

bool InputManager::GetState(Input::Action action, InputState state)
{
	// ボタン情報の配列を取得する
	const BindList list = mActionMap.at(action);

	// 配列内のすべてのボタンの入力状態を調べる
	for (const auto& data : list)
	{
		const auto device = data.at(kKeyDevice);
		const auto button = data.at(kKeyButton);

		switch (state)
		{
		case InputState::EHeld:
			if (mDevices[device]->IsHeld(button)) return true;
			break;

		case InputState::EPressed:
			if (mDevices[device]->IsPressed(button)) return true;
			break;

		case InputState::EReleased:
			if (mDevices[device]->IsReleased(button)) return true;
			break;
		}
	}

	// ここまで来たら、どのボタンも押されていないためfalseを返す
	return false;
}