#include "SceneMain.h"
#include <DxLib.h>
#include "SceneBase.h"
#include "../Scene/SceneGameClear.h"
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
	if (mRemainTime <= kLimitTime - 1 && !mObjElectricity)
	{
		mObjElectricity = new Electricity(GetObjectManager(), mObjWireManager, this, mObjHouseManager);
		mObjElectricity->Init();
	}

	mRemainTime -= Time::GetInstance().GetDeltaTime();

	// Žc‚èŽžŠÔ‚ª–³‚­‚È‚Á‚½‚ç
	if (mRemainTime <= 0)
	{
		GetFader()->StartFadeOut<SceneGameClear>();
	}
	// ‚·‚×‚Ä‚ÌZ‘î‚É“d‹C‚ð“Í‚¯I‚í‚Á‚½‚ç
	if (mSuccessNum == mObjHouseManager->GetHouseNum())
	{
		GetFader()->StartFadeOut<SceneGameClear>();
	}

	return this;
}

void SceneMain::DrawScene()
{
	printfDx("¬Œ÷‰ñ” = %d\n", mSuccessNum);
	printfDx("Žc‚èŽžŠÔ = %f\n", mRemainTime);
	printfDx("—\ŽZ = %d\n", mBudget);
}

void SceneMain::SuccessToDelivery()
{
	mSuccessNum++;

	mObjHouseManager->EnableRandomHouse();

	mObjElectricity = nullptr;
}
