#include "InputDeviceKeyboard.h"
#include <memory>
#include "InputFormat/InputFormatKeyboard.h"

InputDeviceKeyboard::InputDeviceKeyboard()
{
}

void InputDeviceKeyboard::InitializeDevice()
{
	// キーボードのフォーマットを追加
	auto formatKeyboard = std::make_shared<InputFormatKeyboard>();
	AddFormat(formatKeyboard);
}

void InputDeviceKeyboard::UpdateDevice()
{
}
