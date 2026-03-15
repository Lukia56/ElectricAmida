#include "HouseManager.h"
#include <cmath>
#include "House.h"
#include "../Utility/Vector.h"
#include "../GameObject/WireManager.h"

namespace
{
	const Vector2 kCenterPos = { 240, 360 };

	constexpr int kHouseNum = 8;

	const Vector2 kLeftTopPos = { kCenterPos.x - 150.0f, 300 };
	const Vector2 kRightTopPos = { kCenterPos.x + 150.0f, 300 };

	// ‰Æ‚ÌŠÔ‚Ì‹——£
	constexpr float kHouseDistance = 100.0f;

	const char* const kGraphPath = "Resources\\Image\\house.png";
}

HouseManager::HouseManager(ObjectManager* manager, WireManager* wireMgr) :
	GameObject(manager),
	mPtrWireManager(wireMgr),
	mEnabledHouse(false),
	mGraph(-1)
{
}

HouseManager::~HouseManager()
{
}

void HouseManager::InitGameObject()
{
	mGraph = LoadGraph(kGraphPath);

	House* house;
	Vector2 pos;
	for (int i = 0; i < std::ceil(kHouseNum / 2.0f); i++)
	{
		pos = kLeftTopPos + Vector2(0, kHouseDistance * i);

		house = new House(GetObjectManager(), mPtrWireManager, mGraph);
		house->SetPosition(pos);
		house->Init();
		mObjHouseList.emplace_back(house);
	}
	for (int i = 0; i < std::floor(kHouseNum / 2.0f); i++)
	{
		pos = kRightTopPos + Vector2(0, kHouseDistance * i);

		house = new House(GetObjectManager(), mPtrWireManager, mGraph);
		house->SetPosition(pos);
		house->Init();
		mObjHouseList.emplace_back(house);
	}
}

void HouseManager::EndGameObject()
{
	DeleteGraph(mGraph);
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
	houseList[random]->SetWireActive(true);
	auto iter = std::find(mObjHouseList.begin(), mObjHouseList.end(), houseList[random]);
	mEnabledHouse = std::distance(mObjHouseList.begin(), iter);
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
