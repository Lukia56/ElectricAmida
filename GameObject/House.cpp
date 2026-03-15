#include "House.h"
#include <DxLib.h>
#include "../Utility/Color.h"
#include "WireManager.h"
#include "../System/InputManager.h"

House::House(ObjectManager* manager, WireManager* wireMgr, int graph) :
	GameObject(manager),
	mPtrWireManager(wireMgr),
	mIsEnabled(false),
	mWireIndex(0),
	mGraph(graph)
{
}

House::~House()
{
}

void House::InitGameObject()
{
	const auto& fixedWires = mPtrWireManager->GetFixedWireList();

	Vector2 pos = GetPosition();

	const bool isLeft = pos.x <= fixedWires[FixedWire::kLeftIndex].line.start.x;

	Wire wire;
	if (isLeft)
	{
		wire.line.start = { fixedWires[FixedWire::kLeftIndex].line.start.x, pos.y };
		wire.line.end = pos;
	}
	else
	{
		wire.line.start = pos;
		wire.line.end = { fixedWires[FixedWire::kRightIndex].line.start.x, pos.y };
	}
	wire.enable = false;

	mPtrWireManager->AddWire(wire);

	mWireIndex = mPtrWireManager->GetWireList().size() - 1;
}

void House::EndGameObject()
{
}

void House::Update()
{
}

void House::Draw()
{
	int color = mIsEnabled ? Color::kYellow : Color::kGray;

	const auto& pos = GetPosition();
	//DrawBox(pos.x - 40, pos.y - 40, pos.x + 40, pos.y + 40, color, true);

	DrawRotaGraph(pos.x, pos.y, 1, 0, mGraph, 1);
	SetDrawBlendMode(DX_BLENDMODE_MUL, color);
	DrawBox(pos.x - 40, pos.y - 40, pos.x + 40, pos.y + 40, color, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void House::SetWireActive(bool state)
{
	mPtrWireManager->SetWireEnable(mWireIndex, state);
	mIsEnabled = state;
}

void House::SetActive()
{
	mIsEnabled = true;

	//mPtrWireManager->SetWireEnable(mWireIndex, false);
}
