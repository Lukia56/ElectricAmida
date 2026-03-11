#include "SceneMain.h"
#include <DxLib.h>
#include "SceneBase.h"
#include "../Scene/SceneGameClear.h"
#include "../Scene/Fader.h"
#include "../Utility/Color.h"
#include "../System/InputManager.h"
#include "../System/Time.h"
#include "../System/PauseManager.h"
#include "../GameObject/WireManager.h"
#include "../GameObject/Electricity.h"
#include "../GameObject/HouseManager.h"
#include "../GameObject/GameUI.h"
#include "../GameObject/ResultUI.h"
#include "../ImGui/imgui.h"

namespace
{
	// ƒQ[ƒ€‚Ì§ŒÀŽžŠÔ
	constexpr float kLimitTime = 9930.0f;

	// “dü‚Ì‰Šú—\ŽZ
	constexpr int kBudget = 10;
}

SceneMain::SceneMain() :
	mObjWireManager(nullptr),
	mObjElectricity(nullptr),
	mObjHouseManager(nullptr),
	mGameState(GameState::Ready),
	mSuccessNum(0),
	mRemainTime(kLimitTime),
	mBudget(kBudget),
	mGameUI(nullptr),
	mPauseManager(nullptr),
	mResultUI(nullptr)
{
	mGameState = GameState::Result;
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

	mGameUI = new GameUI();
	mGameUI->Init(this);

	mObjElectricity = new Electricity(GetObjectManager(), mObjWireManager, this, mObjHouseManager);
	mObjElectricity->Init();

	mPauseManager = new PauseManager(GetObjectManager());
}

void SceneMain::EndScene()
{
	mObjElectricity = nullptr;
	mObjWireManager = nullptr;
	mObjHouseManager = nullptr;

	mGameUI->End();
	delete mGameUI;
	mGameUI = nullptr;

	delete mPauseManager;
	mPauseManager = nullptr;

	mResultUI = nullptr;
}

SceneBase* SceneMain::UpdateScene()
{
	if (mGameState == GameState::Play)
	{
		if (mObjElectricity && InputManager::GetInstance().IsPressed(Input::Action::Confirm))
		{
			mObjElectricity->StartMove();
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
	}
	if (mGameState == GameState::Result)
	{
		if (mResultUI == nullptr)
		{
			mResultUI = new ResultUI(GetObjectManager(), this);
		}
	}

	return this;
}

void SceneMain::DrawScene()
{
	//printfDx("¬Œ÷‰ñ” = %d\n", mSuccessNum);
	//printfDx("Žc‚èŽžŠÔ = %f\n", mRemainTime);
	//printfDx("—\ŽZ = %d\n", mBudget);

	mGameUI->Draw();

	if (mGameState == GameState::Play)
	{
		mPauseManager->Update();
		mPauseManager->Draw();
	}
}

void SceneMain::DrawSceneImGui()
{
	if (ImGui::Begin("Scene"))
	{
		ImGui::Text("SceneMain");

		ImGui::Text(u8"¬Œ÷‰ñ” = %d", mSuccessNum);
		ImGui::Text(u8"Žc‚èŽžŠÔ = %f", mRemainTime);
		ImGui::Text(u8"—\ŽZ = %d", mBudget);
	}

	ImGui::End();
}

void SceneMain::SuccessToDelivery()
{
	mSuccessNum++;

	mObjHouseManager->EnableRandomHouse();

	mObjElectricity = new Electricity(GetObjectManager(), mObjWireManager, this, mObjHouseManager);
	mObjElectricity->Init();
}
