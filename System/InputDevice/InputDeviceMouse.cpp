#include "InputDeviceMouse.h"
#include <memory>
#include "InputFormat/InputFormatMouseButton.h"
#include "InputFormat/InputFormatMouseWheel.h"

InputDeviceMouse::InputDeviceMouse() :
	mWheelRot(0),
	mIsFixMouse(false)
{
}

void InputDeviceMouse::InitializeDevice()
{
	// マウスボタンのフォーマットを追加
	auto formatButton = std::make_shared<InputFormatMouseButton>();
	AddFormat(formatButton);

	// マウスホイールのフォーマットを追加
	auto formatWheel = std::make_shared<InputFormatMouseWheel>();
	formatWheel->SetDevice(shared_from_this());
	AddFormat(formatWheel);

	SetMouseDispFlag(true);
}

void InputDeviceMouse::UpdateDevice()
{
	// 座標情報の更新
	UpdatePosLog();

	// マウスの固定処理
	FixMouse();

	// ホイール情報を取得
	UpdateWheetRot();
}

void InputDeviceMouse::UpdatePosLog()
{
	int x, y;
	GetMousePoint(&x, &y);

	for (int i = mPosLog.size() - 1; i > 0; i--)
	{
		// 1つ前に移動させる
		mPosLog[i] = mPosLog[i - 1];
	}
	mPosLog[0] = Vector2(x, y);
}

void InputDeviceMouse::FixMouse()
{
	// マウスを固定しないなら処理を終了
	if (!mIsFixMouse) return;
	
	// 画面中央に固定する
	SetMousePoint(0, 0);
	mPosLog[0] = Vector2::Zero;
}

void InputDeviceMouse::UpdateWheetRot()
{
	mWheelRot = GetMouseWheelRotVol();
}
