#include "WireManager.h"
#include "../System/InputManager.h"
#include "../Utility/Color.h"
#include "../Collision/Collision2D.h"
#include "../System/InputDevice/InputDeviceMouse.h"
#include "../System/SoundManager.h"
#include "../System/Time.h"
#include "../Scene/SceneMain.h"

namespace
{
	const Vector2 kCenterPos = { 240, 360 };

	// 右側の固定電線の線分
	const Vector2 kLeftFixWireStart = { kCenterPos.x - 80.0f, 100 };
	const Vector2 kLeftFixWireEnd = { kCenterPos.x - 80.0f, 680 };

	// 左側の固定電線の線分
	const Vector2 kRightFixWireStart = { kCenterPos.x + 80.0f, 100 };
	const Vector2 kRightFixWireEnd = { kCenterPos.x + 80.0f, 680 };

	constexpr float kSeTimerDuration = 0.1f;

	// 点線の点の長さ
	constexpr float kDottedLineDotLen = 5;
	// 点線の隙間の長さ
	constexpr float kDottedLineSpaceLen = 5;
}

WireManager::WireManager(ObjectManager* manager, SceneMain* scene) :
	GameObject(manager),
	mPtrScene(scene),
	mSeTimer(kSeTimerDuration)
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
	
	if (mPtrScene->GetGameState() != SceneMain::GameState::Play) return;

	SetDrawEndPos();

	// 電線を引く
	CreateAddWire();
}

void WireManager::Draw()
{
	// 固定電線を描画
	for (const auto& wire : mFixedWireList)
	{
		DrawLine(wire.line.start.x, wire.line.start.y, wire.line.end.x, wire.line.end.y, Color::kWhite);
	}

	// 電線を描画
	for (const auto& wire : mWireList)
	{
		DrawLine(wire.line.start.x, wire.line.start.y, wire.line.end.x, wire.line.end.y, wire.enable ? Color::kWhite : Color::kDkGray);
	}
}

void WireManager::PostDraw()
{
	if (InputManager::GetInstance().IsHeld(Input::Action::Draw) && mPtrScene->GetGameState() == SceneMain::GameState::Play)
	{
		// マウスが離された座標を開始点にする
		//DrawLine(mDrawWire.start.x, mDrawWire.start.y, mDrawWire.end.x, mDrawWire.end.y, CanCreateWire() ? Color::kWhite : Color::kRed);

		DrawDottedLine(mDrawWire.start, mDrawWire.end, CanCreateWire() ? Color::kWhite : Color::kRed, kDottedLineDotLen, kDottedLineSpaceLen);
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

	if (mSeTimer < 0)
	{
		mSeTimer = kSeTimerDuration;

		SoundManager::GetInstance().PlaySE(Sound::SE::ReadyDraw);
	}
	mSeTimer -= Time::GetInstance().GetDeltaTime();
}

void WireManager::CreateAddWire()
{
	if (!InputManager::GetInstance().IsReleased(Input::Action::Draw)) return;
	
	// 固定電線に触れているかチェック
	if (CanCreateWire())
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

		SoundManager::GetInstance().PlaySE(Sound::SE::CreateWire);
	}
}

bool WireManager::CanCreateWire()
{
	bool result = Collision::IsIntersect(mDrawWire, mFixedWireList[FixedWire::kLeftIndex].line)
		&& Collision::IsIntersect(mDrawWire, mFixedWireList[FixedWire::kRightIndex].line);

	return result;
}

void WireManager::DrawDottedLine(const Vector2& start, const Vector2& end, unsigned int color, float dotLen, float spaceLen)
{
	Vector2 vect = end - start;
	float len = Vector2::Length(vect);

	// 長さが0なら描画しない
	if (len <= 0) return;

	Vector2 pos;
	Vector2 nextPos;
	Vector2 unit = Vector2::Normalize(vect);

	// 開始点から終点まで描画する
	for (int i = 0; i <= len; i += dotLen + spaceLen)
	{
		pos = start + unit * i;
		nextPos = pos + unit * dotLen;

		// 終点を超えていたら収める
		if (Vector2::LengthSquare(nextPos - start) > Vector2::LengthSquare(vect))
		{
			nextPos = end;
		}

		DrawLine(pos.x, pos.y, nextPos.x, nextPos.y, color);
	}
}
