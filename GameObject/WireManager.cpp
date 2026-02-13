#include "WireManager.h"
#include "../System/InputManager.h"
#include "../Utility/Color.h"
#include "../Collision/Collision2D.h"
#include "../System/InputDevice/InputDeviceMouse.h"

namespace
{
	// 右側の固定電線の線分
	const Vector2 kLeftFixWireStart = { 320, 10 };
	const Vector2 kLeftFixWireEnd = { 320, 530 };

	// 左側の固定電線の線分
	const Vector2 kRightFixWireStart = { 640, 10 };
	const Vector2 kRightFixWireEnd = { 640, 530 };
}

WireManager::WireManager(ObjectManager* manager) :
	GameObject(manager)
{
}

WireManager::~WireManager()
{
}

void WireManager::InitGameObject()
{
	LineSegment wire;

	// 左側の固定電線を生成
	wire.start = kLeftFixWireStart;
	wire.end = kLeftFixWireEnd;
	mFixedWireList.emplace_back(wire);
	// 右側の固定電線を生成
	wire.start = kRightFixWireStart;
	wire.end = kRightFixWireEnd;
	mFixedWireList.emplace_back(wire);

	// 追加電線の初期化
	mDrawWire.start = Vector2();
	mDrawWire.end = Vector2();
}

void WireManager::EndGameObject()
{
}

void WireManager::Update()
{
	SetDrawStartPos();
	
	SetDrawEndPos();

	// 電線を引く
	AddWire();
}

void WireManager::Draw()
{
	if (InputManager::GetInstance().IsHeld(Input::Action::Draw))
	{
		// マウスが離された座標を開始点にする
		DrawLine(mDrawWire.start.x, mDrawWire.start.y, mDrawWire.end.x, mDrawWire.end.y, Color::kWhite);
	}

	// 固定電線を描画
	for (const auto& wire : mFixedWireList)
	{
		DrawLine(wire.start.x, wire.start.y, wire.end.x, wire.end.y, Color::kCyan);
	}

	// 固定電線を描画
	for (const auto& wire : mWireList)
	{
		DrawLine(wire.start.x, wire.start.y, wire.end.x, wire.end.y, Color::kCyan);
	}
}

void WireManager::SetDrawStartPos()
{
	if (!InputManager::GetInstance().IsPressed(Input::Action::Draw)) return;
	
	int x, y;

	// マウスがクリックされた座標を開始点にする
	GetMousePoint(&x, &y);
	mDrawWire.start = Vector2(x, y);
}

void WireManager::SetDrawEndPos()
{
	// 電線を引く準備
	if (!InputManager::GetInstance().IsHeld(Input::Action::Draw)) return;

	int x, y;
	GetMousePoint(&x, &y);

	mDrawWire.end = Vector2(x, y);
}

void WireManager::AddWire()
{
	if (!InputManager::GetInstance().IsReleased(Input::Action::Draw)) return;
	
	// 固定電線に触れているかチェック
	if (Collision::IsIntersect(mDrawWire, mFixedWireList[0])
		&& Collision::IsIntersect(mDrawWire, mFixedWireList[1]))
	{
		// 開始点を左の固定電線に合わせるために、
		// 開始点を左に置く
		if (mDrawWire.start.x > mDrawWire.end.x)
		{
			std::swap(mDrawWire.start, mDrawWire.end);
		}

		// 開始点を左の固定電線に合わせる
		mDrawWire.start = Collision::GetIntersectPoint(mFixedWireList[0], mDrawWire);
		// 終着点を右の固定電線に合わせる
		mDrawWire.end = Collision::GetIntersectPoint(mFixedWireList[1], mDrawWire);

		// 電線を追加
		mWireList.emplace_back(mDrawWire);
	}
}
