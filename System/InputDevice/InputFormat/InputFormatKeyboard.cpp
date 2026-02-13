#include "InputFormatKeyboard.h"
#include <DxLib.h>

InputFormatKeyboard::InputFormatKeyboard()
{
	AddButton("A", KEY_INPUT_A);
	AddButton("B", KEY_INPUT_B);
	AddButton("C", KEY_INPUT_C);
	AddButton("D", KEY_INPUT_D);
	AddButton("E", KEY_INPUT_E);
	AddButton("F", KEY_INPUT_F);
	AddButton("G", KEY_INPUT_G);
	AddButton("H", KEY_INPUT_H);
	AddButton("I", KEY_INPUT_I);
	AddButton("J", KEY_INPUT_J);
	AddButton("K", KEY_INPUT_K);
	AddButton("L", KEY_INPUT_L);
	AddButton("M", KEY_INPUT_M);
	AddButton("N", KEY_INPUT_N);
	AddButton("O", KEY_INPUT_O);
	AddButton("P", KEY_INPUT_P);
	AddButton("Q", KEY_INPUT_Q);
	AddButton("R", KEY_INPUT_R);
	AddButton("S", KEY_INPUT_S);
	AddButton("T", KEY_INPUT_T);
	AddButton("U", KEY_INPUT_U);
	AddButton("V", KEY_INPUT_V);
	AddButton("W", KEY_INPUT_W);
	AddButton("X", KEY_INPUT_X);
	AddButton("Y", KEY_INPUT_Y);
	AddButton("Z", KEY_INPUT_Z);

	AddButton("0", KEY_INPUT_0);
	AddButton("1", KEY_INPUT_1);
	AddButton("2", KEY_INPUT_2);
	AddButton("3", KEY_INPUT_3);
	AddButton("4", KEY_INPUT_4);
	AddButton("5", KEY_INPUT_5);
	AddButton("6", KEY_INPUT_6);
	AddButton("7", KEY_INPUT_7);
	AddButton("8", KEY_INPUT_8);
	AddButton("9", KEY_INPUT_9);

	AddButton("F1", KEY_INPUT_F1);
	AddButton("F2", KEY_INPUT_F2);
	AddButton("F3", KEY_INPUT_F3);
	AddButton("F4", KEY_INPUT_F4);
	AddButton("F5", KEY_INPUT_F5);
	AddButton("F6", KEY_INPUT_F6);
	AddButton("F7", KEY_INPUT_F7);
	AddButton("F8", KEY_INPUT_F8);
	AddButton("F9", KEY_INPUT_F9);
	AddButton("F10", KEY_INPUT_F10);
	AddButton("F11", KEY_INPUT_F11);
	AddButton("F12", KEY_INPUT_F12);

	AddButton("Numpad0", KEY_INPUT_NUMPAD0);
	AddButton("Numpad1", KEY_INPUT_NUMPAD1);
	AddButton("Numpad2", KEY_INPUT_NUMPAD2);
	AddButton("Numpad3", KEY_INPUT_NUMPAD3);
	AddButton("Numpad4", KEY_INPUT_NUMPAD4);
	AddButton("Numpad5", KEY_INPUT_NUMPAD5);
	AddButton("Numpad6", KEY_INPUT_NUMPAD6);
	AddButton("Numpad7", KEY_INPUT_NUMPAD7);
	AddButton("Numpad8", KEY_INPUT_NUMPAD8);
	AddButton("Numpad9", KEY_INPUT_NUMPAD9);
	AddButton("Numpad9", KEY_INPUT_NUMPAD9);
	AddButton("NumpadEnter", KEY_INPUT_NUMPADENTER);
	AddButton("Add", KEY_INPUT_ADD);
	AddButton("Subtract", KEY_INPUT_SUBTRACT);
	AddButton("Multiply", KEY_INPUT_MULTIPLY);
	AddButton("Divide", KEY_INPUT_DIVIDE);
	AddButton("Decimal", KEY_INPUT_DECIMAL);

	AddButton("Minus", KEY_INPUT_MINUS);
	AddButton("Yen", KEY_INPUT_YEN);
	AddButton("PrevTrack", KEY_INPUT_PREVTRACK);
	AddButton("Period", KEY_INPUT_PERIOD);
	AddButton("Slash", KEY_INPUT_SLASH);
	AddButton("LAlt", KEY_INPUT_LALT);
	AddButton("RAlt", KEY_INPUT_RALT);
	AddButton("ScrollLock", KEY_INPUT_SCROLL);
	AddButton("Semicolon", KEY_INPUT_SEMICOLON);
	AddButton("Colon", KEY_INPUT_COLON);
	AddButton("LBracket", KEY_INPUT_RBRACKET);
	AddButton("RBracket", KEY_INPUT_LBRACKET);
	AddButton("At", KEY_INPUT_AT);
	AddButton("BackSlash", KEY_INPUT_BACKSLASH);
	AddButton("Comma", KEY_INPUT_COMMA);
	AddButton("CapsLock", KEY_INPUT_CAPSLOCK);
	AddButton("PauseBreak", KEY_INPUT_PAUSE);

	AddButton("LShift", KEY_INPUT_LSHIFT);
	AddButton("RShift", KEY_INPUT_RSHIFT);
	AddButton("LControl", KEY_INPUT_LCONTROL);
	AddButton("RControl", KEY_INPUT_RCONTROL);
	AddButton("Escape", KEY_INPUT_ESCAPE);
	AddButton("Space", KEY_INPUT_SPACE);
	AddButton("PageUp", KEY_INPUT_PGUP);
	AddButton("PageDown", KEY_INPUT_PGDN);
	AddButton("End", KEY_INPUT_END);
	AddButton("Home", KEY_INPUT_HOME);
	AddButton("LeftArrow", KEY_INPUT_LEFT);
	AddButton("UpArrow", KEY_INPUT_UP);
	AddButton("RightArrow", KEY_INPUT_RIGHT);
	AddButton("DownArrow", KEY_INPUT_DOWN);
	AddButton("Insert", KEY_INPUT_INSERT);
	AddButton("Delete", KEY_INPUT_DELETE);

	AddButton("BackSpace", KEY_INPUT_BACK);
	AddButton("Tab", KEY_INPUT_TAB);
	AddButton("Return", KEY_INPUT_RETURN);
}

bool InputFormatKeyboard::CheckButtonState(const std::string name)
{
	int keyCode = GetButtonStringToKeyCode().at(name);

	return CheckHitKey(keyCode);
}
