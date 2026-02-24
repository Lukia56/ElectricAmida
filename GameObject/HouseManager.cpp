#include "HouseManager.h"
#include <cmath>
#include "House.h"
#include "../Utility/Vector.h"
#include "../GameObject/WireManager.h"

namespace
{
	int kHouseNum = 10;

	Vector2 kLeftTopPos = { 250, 80 };
	Vector2 kRightTopPos = { 710, 80 };

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

		house = new House(GetObjectManager(), mPtrWireManager);
		house->SetPosition(pos);
		house->Init();
		mObjHouseList.emplace_back(house);
	}
	for (int i = 0; i < std::floor(kHouseNum / 2.0f); i++)
	{
		pos = kRightTopPos + Vector2(0, kHouseDistance * i);

		house = new House(GetObjectManager(), mPtrWireManager);
		house->SetPosition(pos);
		house->Init();
		mObjHouseList.emplace_back(house);
	}
}

void HouseManager::EndGameObject()
{
}

void HouseManager::Update()
{
}

void HouseManager::Draw()
{
}

void HouseManager::EnableRandomHouse()
{
	std::vector<House*> houseList;

	for (const auto& house : mObjHouseList)
	{
		if (house->IsEnable()) continue;

		houseList.emplace_back(house);
	}

	if (houseList.size() == 0) return;

	int random = GetRand(houseList.size() - 1);
	houseList[random]->SetWireActive();
}

int HouseManager::GetHouseNum()
{
	return kHouseNum;
}

House* HouseManager::GetNearestHouse(Vector2 pos)
{
	float dist = 999999;
	House* nearestHouse = nullptr;

	for (auto& house : mObjHouseList)
	{
		if (Vector2::Length(house->GetPosition() - pos) < dist)
		{
			dist = Vector2::Length(house->GetPosition() - pos);
			nearestHouse = house;
		}
	}

	return nearestHouse;
}
