#include "HouseManager.h"
#include <cmath>
#include "House.h"
#include "../Utility/Vector.h"
#include "../GameObject/WireManager.h"

namespace
{
	int kHouseNum = 10;

	Vector2 kLeftTopPos = { 150, 50 };
	Vector2 kRightTopPos = { 810, 50 };

	// ‰Æ‚ÌŠÔ‚Ì‹——£
	float kHouseDistance = 100.0f;
}

HouseManager::HouseManager(ObjectManager* manager, WireManager* wireMgr) :
	GameObject(manager),
	mPtrWireManager(wireMgr)
{
}

HouseManager::~HouseManager()
{
}

void HouseManager::InitGameObject()
{
	House* house;
	Vector2 pos;
	for (int i = 0; i < std::ceil(kHouseNum / 2.0f); i++)
	{
		pos = kLeftTopPos + Vector2(0, kHouseDistance * i);

		Wire wire;
		wire.line.start = {mPtrWireManager->GetFixedWireList()[FixedWire::kLeftIndex].line.start.x, pos.y};
		wire.line.end = pos;
		wire.enable = false;
		mPtrWireManager->AddWire(wire);

		house = new House(GetObjectManager());
		house->SetPosition(pos);

		HouseData data;
		data.house = house;
		data.wireIndex = mPtrWireManager->GetWireList().size() - 1;
		mObjHouseList.emplace_back(data);
	}
	for (int i = 0; i < std::floor(kHouseNum / 2.0f); i++)
	{
		/*Wire wire;
		wire.line = LineSegment{};
		mPtrWireManager->AddWire(wire);
		house = new House(GetObjectManager(), wire.enable);
		house->SetPosition(kRightTopPos + Vector2(0, kHouseDistance * i));*/
	}
}

void HouseManager::EndGameObject()
{
}

void HouseManager::Update()
{
	for (auto& data : mObjHouseList)
	{
		bool enable = mPtrWireManager->GetWireList()[data.wireIndex].enable;
		data.house->SetEnable(enable);
	}
}

void HouseManager::Draw()
{
}
