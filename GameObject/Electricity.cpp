#include "Electricity.h"
#include <DxLib.h>
#include <cmath>
#include "../Utility/Vector.h"
#include "../Utility/Color.h"
#include "../Utility/Math.h"
#include "../GameObject/WireManager.h"
#include "../GameObject/HouseManager.h"
#include "../GameObject/House.h"
#include "../GameObject/Particle.h"
#include "../Scene/SceneMain.h"
#include "../Scene/SceneGameOver.h"
#include "../Scene/Fader.h"
#include "../System/Time.h"
#include "../System/InputManager.h"
#include "../ImGui/imgui.h"
#include <cassert>

namespace
{
	constexpr float kInitSpeed = 50.0f;

	constexpr int kScreenCenterX = 240;

	// 加速時の係数
	constexpr float kCoefSpeed = 10.0f;

	constexpr int kParticleDuration = 2;
}

Electricity::Electricity(ObjectManager* manager, WireManager* wireMgr, SceneMain* scene, HouseManager* houseMgr) :
	GameObject(manager),
	mPtrWireManager(wireMgr),
	mPtrSceneMain(scene),
	mPtrHouseManager(houseMgr),
	mSpeed(kInitSpeed),
	mIsStart(false),
	mTimer(0),
	mParticleTimer(0)
{
}

Electricity::~Electricity()
{
}

void Electricity::InitGameObject()
{
	const auto& houses = mPtrHouseManager->GetHouseObjectList();
	const int isLeft = 0;//houses[mPtrHouseManager->GetEnableHouseIndex()]->GetPosition().x < kScreenCenterX;

	// 固定電線リストをキャッシュ
	const WireList& wires = mPtrWireManager->GetFixedWireList();

	// 固定電線を開始点にする
	mStartPos = wires[isLeft].line.start;
	mEndPos = wires[isLeft].line.end;
	SetPosition(mStartPos);
}

void Electricity::EndGameObject()
{
}

void Electricity::Update()
{
	mTimer += 50;

	GenerateParticle();

	if (mPtrSceneMain->GetGameState() == SceneMain::GameState::Result)
	{
		SetState(State::EDead);
		return;
	}

	if (!mIsStart) return;

	Vector2 vect = mEndPos - mStartPos;
	vect = Vector2::Normalize(vect);

	Vector2 speed = vect * mSpeed * Time::GetInstance().GetDeltaTime();

	if (InputManager::GetInstance().IsHeld(Input::Action::Accel))
	{
		speed *= kCoefSpeed;
	}

	Vector2 newPos = GetPosition() + speed;

	MoveToOtherWire(newPos);
	MoveToFixedWire(newPos);

	SetPosition(newPos);
}

void Electricity::Draw()
{
	Vector2 pos = GetPosition();
	DrawCircle(pos.x, pos.y, 10 + std::sin(Math::ToRadian(mTimer)) * 1, Color::kYellow);
}

void Electricity::DrawImGui()
{
	if (ImGui::Begin("GameObject"))
	{
		ImGui::Text("[Electricity]");

		ImGui::Text("Position");
		ImGui::Text("X:%f Y:%f", GetPosition().x, GetPosition().y);
		ImGui::Text("StartPos");
		ImGui::Text("X:%f Y:%f", mStartPos.x, mStartPos.y);
		ImGui::Text("EndPos");
		ImGui::Text("X:%f Y:%f", mEndPos.x, mEndPos.y);

		ImGui::SliderFloat("mSpeed", &mSpeed, 0.0f, 1000.0f);

		ImGui::Checkbox("IsStart", &mIsStart);
	}

	ImGui::End();
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
		// 電線が無効ならスキップ
		if (!wire.enable) continue;

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
	// 電線の移動が終わったなら
	if (Vector2::Length(mEndPos - mStartPos) > Vector2::Length(newPos - mStartPos)) return;
	
	// 現在の電線の終点に移動
	newPos.y = mEndPos.y;

	// 固定電線のリストをキャッシュ
	const WireList& wires = mPtrWireManager->GetFixedWireList();

	// 左の固定電線かどうか
	const bool isLeft = (newPos.x <= wires[FixedWire::kLeftIndex].line.start.x);

	// 終点が固定電線に繋がっていないなら
	if ((isLeft && mEndPos.x != wires[FixedWire::kLeftIndex].line.start.x)
	|| (!isLeft && mEndPos.x != wires[FixedWire::kRightIndex].line.start.x))
	{
		MovedToHouse(newPos);

		return;
	}

	// 移動先の固定電線の添え字
	const int index = isLeft ? FixedWire::kLeftIndex : FixedWire::kRightIndex;

	// 開始点と終点を固定電線に設定
	mStartPos = wires[index].line.start;
	mEndPos = wires[index].line.end;

	// 座標更新
	newPos.x = mStartPos.x;

	// 固定電線の終点まで移動したら
	if (newPos.y == wires[index].line.end.y)
	{
		mIsStart = false;
		Init();
		newPos = GetPosition();
	}
}

void Electricity::MovedToHouse(Vector2& newPos)
{
	if (auto* house = mPtrHouseManager->GetNearestHouse(GetPosition()))
	{
		house->Success();
	}

	mPtrSceneMain->SuccessToDelivery();

	Init();
	newPos = GetPosition();
}

void Electricity::GenerateParticle()
{
	mParticleTimer--;

	if (mParticleTimer < 0)
	{
		mParticleTimer = kParticleDuration;

		Particle* pt = new Particle(GetObjectManager(), GetPosition());
		pt->Init();
	}
}
