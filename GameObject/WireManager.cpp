#include "WireManager.h"
#include "../System/InputManager.h"
#include "../Utility/Color.h"
#include "../Collision/Collision2D.h"
#include "../System/InputDevice/InputDeviceMouse.h"
#include "../Scene/SceneMain.h"

namespace
{
	// 右側の固定電線の線分
	const Vector2 kLeftFixWireStart = { 400, 10 };
	const Vector2 kLeftFixWireEnd = { 400, 530 };

	// 左側の固定電線の線分
	const Vector2 kRightFixWireStart = { 560, 10 };
	const Vector2 kRightFixWireEnd = { 560, 530 };
}

WireManager::WireManager(ObjectManager* manager, SceneMain* scene) :
	GameObject(manager),
	mPtrScene(scene)
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
		DrawLine(mDrawWire.start.x, mDrawWire.start.y, mDrawWire.end.x, mDrawWire.end.y, mPtrScene->GetBudget() > 0 ? Color::kWhite : Color::kRed);
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
}

void WireManager::AddWire(Wire& line)
{
	mWireList.emplace_back(line);
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
	
	// 予算が無いなら早期リターン
	if (mPtrScene->GetBudget() <= 0) return;

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

		mPtrScene->SetBudget(mPtrScene->GetBudget() - 1);
	}
}
