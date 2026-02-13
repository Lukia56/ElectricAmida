#include "InputFormatBase.h"

void InputFormatBase::AddButton(const std::string name, const int keyCode)
{
	mButtonStringToKeyCode[name] = keyCode;
}

void InputFormatBase::RemoveButton(const std::string name)
{
	mButtonStringToKeyCode.erase(name);
}
