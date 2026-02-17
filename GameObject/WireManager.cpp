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
	Wire wire;

	// 左側の固定電線を生成
	wire.line.start = kLeftFixWireStart;
	wire.line.end = kLeftFixWireEnd;
	wire.enable = true;
	mFixedWireList.emplace_back(wire);
	// 右側の固定電線を生成
	wire.line.start = kRightFixWireStart;
	wire.line.end = kRightFixWireEnd;
	wire.enable = true;
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
	CreateAddWire();
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
		DrawLine(wire.line.start.x, wire.line.start.y, wire.line.end.x, wire.line.end.y, Color::kCyan);
	}

	// 電線を描画
	for (const auto& wire : mWireList)
	{
		DrawLine(wire.line.start.x, wire.line.start.y, wire.line.end.x, wire.line.end.y, wire.enable ? Color::kCyan : Color::kBrown);
	}



	
	Rect shapeA;
	Circle shapeB;
	shapeA.left = 100;
	shapeA.top = 100;
	shapeA.right= 300;
	shapeA.bottom = 300;

	/*shapeB.left = 120;
	shapeB.top = 120;
	shapeB.right = 280;
	shapeB.bottom = 280;*/

	//shapeA.center = Vector2(150, 150);
	//shapeA.radius = 75;
	shapeB.center = Vector2(300, 200);
	shapeB.radius = 75;

	DrawBox(shapeA.left, shapeA.top, shapeA.right, shapeA.bottom, Color::kRed, 0);
	//DrawBox(shapeB.left, shapeB.top, shapeB.right, shapeB.bottom, Color::kGreen, 0);
	//DrawCircle(shapeA.center.x, shapeA.center.y, shapeA.radius, Color::kRed, 0);
	DrawCircle(shapeB.center.x, shapeB.center.y, shapeB.radius, Color::kGreen, 0);

	if (Collision::IsIntersect(shapeA, shapeB))
	{
		DrawBox(200, 200, 210, 210, Color::kWhite, 1);
	}
}

void WireManager::AddWire(const Wire wire)
{
	mWireList.emplace_back(wire);
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

void WireManager::CreateAddWire()
{
	if (!InputManager::GetInstance().IsReleased(Input::Action::Draw)) return;
	
	// 固定電線に触れているかチェック
	if (Collision::IsIntersect(mDrawWire, mFixedWireList[FixedWire::kLeftIndex].line)
		&& Collision::IsIntersect(mDrawWire, mFixedWireList[FixedWire::kRightIndex].line))
	{
		// 開始点を左の固定電線に合わせるために、
		// 開始点を左に置く
		if (mDrawWire.start.x > mDrawWire.end.x)
		{
			std::swap(mDrawWire.start, mDrawWire.end);
		}

		// 開始点を左の固定電線に合わせる
		mDrawWire.start = Collision::GetIntersectPoint(mFixedWireList[FixedWire::kLeftIndex].line, mDrawWire);
		// 終着点を右の固定電線に合わせる
		mDrawWire.end = Collision::GetIntersectPoint(mFixedWireList[FixedWire::kRightIndex].line, mDrawWire);

		// 電線を追加
		Wire wire;
		wire.line = mDrawWire;
		wire.enable = true;
		mWireList.emplace_back(wire);
	}
}
