#include "SceneMain.h"
#include <DxLib.h>
#include "SceneBase.h"
#include "../Scene/Fader.h"
#include "../Utility/Color.h"
#include "../System/InputManager.h"
#include "../System/Time.h"
#include "../GameObject/WireManager.h"
#include "../GameObject/Electricity.h"
#include "../GameObject/HouseManager.h"

namespace
{
	// ƒQ[ƒ€‚Ì§ŒÀŽžŠÔ
	constexpr float kLimitTime = 30.0f;

	// “dü‚Ì‰Šú—\ŽZ
	constexpr int kBudget = 10;
}

SceneMain::SceneMain() :
	mObjWireManager(nullptr),
	mObjElectricity(nullptr),
	mObjHouseManager(nullptr),
	mSuccessNum(0),
	mRemainTime(kLimitTime),
	mBudget(kBudget)
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::InitializeScene()
{
	mObjWireManager = new WireManager(GetObjectManager(), this);
	mObjWireManager->Init();

	mObjHouseManager = new HouseManager(GetObjectManager(), mObjWireManager);
	mObjHouseManager->Init();

	mObjHouseManager->EnableRandomHouse();
}

void SceneMain::EndScene()
{
	mObjElectricity = nullptr;
	mObjWireManager = nullptr;
	mObjHouseManager = nullptr;
}

SceneBase* SceneMain::UpdateScene()
{
	if (InputManager::GetInstance().IsPressed(Input::Action::Down))
	{
		mObjElectricity = new Electricity(GetObjectManager(), mObjWireManager, this, mObjHouseManager);
		mObjElectricity->Init();
	}
	if (InputManager::GetInstance().IsPressed(Input::Action::Right))
	{
		mObjHouseManager->EnableRandomHouse();
	}

	mRemainTime -= Time::GetInstance().GetDeltaTime();

	return this;
}

void SceneMain::DrawScene()
{
	printfDx("¬Œ÷‰ñ” = %d", mSuccessNum);
	printfDx("Žc‚èŽžŠÔ = %f", mRemainTime);
	printfDx("—\ŽZ = %d", mBudget);
}

void SceneMain::SuccessToDelivery()
{
	mSuccessNum++;

	mObjHouseManager->EnableRandomHouse();
}
