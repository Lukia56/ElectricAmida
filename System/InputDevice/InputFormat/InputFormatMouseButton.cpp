#include "InputFormatMouseButton.h"
#include <DxLib.h>

InputFormatMouseButton::InputFormatMouseButton()
{
	AddButton("LClick", MOUSE_INPUT_LEFT);
	AddButton("RClick", MOUSE_INPUT_RIGHT);
	AddButton("MiddleButton", MOUSE_INPUT_MIDDLE);
	AddButton("SideButton4", MOUSE_INPUT_4);
	AddButton("SideButton5", MOUSE_INPUT_5);
}

bool InputFormatMouseButton::CheckButtonState(const std::string name)
{
	int keyCode = GetButtonStringToKeyCode().at(name);

	return GetMouseInput() & keyCode;
}
