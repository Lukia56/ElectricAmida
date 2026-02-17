#include "Electricity.h"
#include <DxLib.h>
#include "../Utility/Vector.h"
#include "../Utility/Color.h"
#include "../GameObject/WireManager.h"
#include <cassert>

namespace
{
	constexpr float kInitSpeed = 10.0f;
}

Electricity::Electricity(ObjectManager* manager, WireManager* wireMgr) :
	GameObject(manager),
	mPtrWireManager(wireMgr),
	mSpeed(kInitSpeed)
{
}

Electricity::~Electricity()
{
}

void Electricity::InitGameObject()
{
	// 固定電線リストをキャッシュ
	const WireList& wires = mPtrWireManager->GetFixedWireList();

	// 固定電線を開始点にする
	mStartPos = wires[0].line.start;
	mEndPos = wires[0].line.end;
	SetPosition(mStartPos);
}

void Electricity::EndGameObject()
{
}

void Electricity::Update()
{
	Vector2 vect = mEndPos - mStartPos;
	vect = Vector2::Normalize(vect);

	const Vector2& speed = vect * mSpeed;

	Vector2 newPos = GetPosition() + speed;

	MoveToOtherWire(newPos);
	MoveToFixedWire(newPos);

	SetPosition(newPos);
}

void Electricity::Draw()
{
	Vector2 pos = GetPosition();
	DrawCircle(pos.x, pos.y, 25, Color::kYellow);
}

void Electricity::MoveToOtherWire(Vector2& newPos)
{
	// 電線リストたちをキャッシュ
	const auto& fixedWires = mPtrWireManager->GetFixedWireList();
	const auto& wires = mPtrWireManager->GetWireList();

	// 左右どちらの固定電線にいるかチェック
	const bool isLeft = newPos.x == fixedWires[FixedWire::kLeftIndex].line.start.x;
	const bool isRight = newPos.x == fixedWires[FixedWire::kRightIndex].line.start.x;

	// 固定電線にいないなら終了
	if (!isLeft && !isRight) return;

	// 移動可能な電線のリスト
	std::vector<Wire> canMoveWires;

	// すべての電線を調べて移動前と移動後の範囲内にある電線を取得する
	for (const auto& wire : wires)
	{
		// 移動開始点を取得
		// 左の固定電線にいるならstartを開始点にする
		// 右の固定電線にいるならendを開始点にする
		const auto& startPoint = (isLeft ? wire.line.start : wire.line.end);
		const auto& endPoint = (isLeft ? wire.line.end : wire.line.start);

		// 開始点のX座標が一致しなかったらスキップ
		if (startPoint.x != GetPosition().x) continue;
		// 開始点より外側ならスキップ
		if (startPoint.y <= GetPosition().y) continue;
		// 終点より外側ならスキップ
		if (startPoint.y > newPos.y) continue;
		// 電線が無効ならスキップ
		if (!wire.enable) continue;

		// 移動範囲内にあるためリストに追加
		canMoveWires.emplace_back(wire);
	}

	// 最小値判定用にfloatの最大値を入れておく
	float min = FLT_MAX;
	
	// 移動範囲内にある電線の内、移動前から一番近い電線に移動する
	for (const auto& wire : canMoveWires)
	{
		// 移動開始点を取得
		const auto& startPoint = (isLeft ? wire.line.start : wire.line.end);
		// 移動終点を取得
		const auto& endPoint = (isLeft ? wire.line.end : wire.line.start);

		// 現在の最小値以上だったらスキップ
		if (startPoint.y >= min) continue;

		// 最小値を更新
		min = startPoint.y;
		// 開始点、終点を設定
		mStartPos = startPoint;
		mEndPos = endPoint;
		// 電線に移動する
		newPos = mStartPos;
	}
}

void Electricity::MoveToFixedWire(Vector2& newPos)
{
	// 追加電線から固定電線に移動する
	if (Vector2::Length(mEndPos - mStartPos) <= Vector2::Length(newPos - mStartPos))
	{
		// 現在の電線の終点に移動
		newPos.y = mEndPos.y;

		// 固定電線のリストをキャッシュ
		const WireList& wires = mPtrWireManager->GetFixedWireList();

		// 左の固定電線かどうか
		const bool isLeft = (newPos.x <= wires[FixedWire::kLeftIndex].line.start.x);

		// 移動先の固定電線の添え字
		const int index = isLeft ? FixedWire::kLeftIndex : FixedWire::kRightIndex;

		// 開始点と終点を固定電線に設定
		mStartPos = wires[index].line.start;
		mEndPos = wires[index].line.end;

		// 座標更新
		newPos.x = mStartPos.x;
	}
}
