#include "InputFormatMouseWheel.h"
#include <DxLib.h>
#include "../System/InputDevice/InputDeviceMouse.h"

namespace
{
	enum Wheel
	{
		Up = 0,
		Down = 1
	};
}

InputFormatMouseWheel::InputFormatMouseWheel()
{
	AddButton("WheelUp", Wheel::Up);
	AddButton("WheelDown", Wheel::Down);
}

bool InputFormatMouseWheel::CheckButtonState(const std::string name)
{
	// シェアポインタを取得
	auto ptr = mPtrDevice.lock();

	// 取得に失敗したらfalse
	if (!ptr) return false;
	
	int keyCode = GetButtonStringToKeyCode().at(name);

	switch (keyCode)
	{
	case Wheel::Up:
			
		return ptr->GetWheelRot() > 0;

	case Wheel::Down:

		return ptr->GetWheelRot() < 0;
	}

	return false;
}
