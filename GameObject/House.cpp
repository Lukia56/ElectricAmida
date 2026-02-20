#include "House.h"
#include <DxLib.h>
#include "../Utility/Color.h"
#include "WireManager.h"
#include "../System/InputManager.h"

House::House(ObjectManager* manager, WireManager* wireMgr) :
	GameObject(manager),
	mPtrWireManager(wireMgr),
	mIsEnabled(false),
	mWireIndex(0)
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
	if (InputManager::GetInstance().IsPressed(Input::Action::Up))
	{
		mPtrWireManager->SetWireEnable(mWireIndex, true);
	}
}

void House::Draw()
{
	int color = mIsEnabled ? Color::kYellow : Color::kRed;

	const auto& pos = GetPosition();
	DrawBox(pos.x - 40, pos.y - 40, pos.x + 40, pos.y + 40, color, true);
}

void House::SetWireActive()
{
	mPtrWireManager->SetWireEnable(mWireIndex, true);
}

void House::SetActive()
{
	mIsEnabled = true;

	mPtrWireManager->SetWireEnable(mWireIndex, false);
}
