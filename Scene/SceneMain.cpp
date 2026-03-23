#include "SceneMain.h"
#include <DxLib.h>
#include "SceneBase.h"
#include "../Scene/SceneGameClear.h"
#include "../Scene/Fader.h"
#include "../Utility/Color.h"
#include "../System/InputManager.h"
#include "../System/Time.h"
#include "../System/PauseManager.h"
#include "../System/SoundManager.h"
#include "../GameObject/WireManager.h"
#include "../GameObject/Electricity.h"
#include "../GameObject/HouseManager.h"
#include "../GameObject/GameUI.h"
#include "../GameObject/ResultUI.h"
#include "../GameObject/ReadyUI.h"
#include "../GameObject/BackGround.h"
#include "../GameObject/CountdownManager.h"
#include "../ImGui/imgui.h"

namespace
{
	// ƒQ[ƒ€‚Ì§ŒÀŽžŠÔ
	constexpr float kLimitTime = 30.0f;
}

SceneMain::SceneMain() :
	mObjWireManager(nullptr),
	mObjElectricity(nullptr),
	mObjHouseManager(nullptr),
	mGameState(GameState::Ready),
	mSuccessNum(0),
	mRemainTime(kLimitTime),
	mGameUI(nullptr),
	mPauseManager(nullptr),
	mResultUI(nullptr),
	mReadyUI(nullptr)
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

	mGameUI = new GameUI();
	mGameUI->Init(this);

	mObjElectricity = new Electricity(GetObjectManager(), mObjWireManager, this, mObjHouseManager);
	mObjElectricity->Init();

	mPauseManager = new PauseManager(GetObjectManager(), this);

	auto background = new BackGround(GetObjectManager());
	background->Init();

	auto countdown = new CountdownManager(GetObjectManager(), this);
	countdown->Init();

	SoundManager::GetInstance().PlayBGM(Sound::BGM::InGame);
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
	switch (mGameState)
	{
	case SceneMain::Ready:
		GameReady();
		break;
	case SceneMain::Play:
		GamePlay();
		break;
	case SceneMain::Result:
		GameResult();
		break;
	}

	mGameUI->Update();

	return this;
}

void SceneMain::DrawScene()
{
	if (!mPauseManager->IsPaused()) mGameUI->Draw();

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
		ImGui::SliderFloat(u8"Žc‚èŽžŠÔ = %f", &mRemainTime, 0, kLimitTime);
	}

	ImGui::End();
}

void SceneMain::SuccessToDelivery()
{
	mSuccessNum++;

	mGameUI->CountUpLightNum();

	mObjHouseManager->EnableRandomHouse();
}

void SceneMain::GameReady()
{
	if (mReadyUI == nullptr)
	{
		mReadyUI = new ReadyUI(GetObjectManager(), this);
		mReadyUI->Init();
	}
}

void SceneMain::GamePlay()
{
	if (mPauseManager->IsPaused()) return;

	mObjElectricity->StartMove();

	mRemainTime -= Time::GetInstance().GetDeltaTime();

	// Žc‚èŽžŠÔ‚ª–³‚­‚È‚Á‚½‚ç
	if (mRemainTime <= 0)
	{
		mGameState = GameState::Result;
	}
}

void SceneMain::GameResult()
{
	if (mResultUI == nullptr)
	{
		mResultUI = new ResultUI(GetObjectManager(), this);
		mResultUI->Init();

		SoundManager::GetInstance().PlayBGM(Sound::BGM::Result);
	}
}
