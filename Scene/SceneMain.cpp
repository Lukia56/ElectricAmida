#include "SceneMain.h"
#include <DxLib.h>
#include <fstream>
#include <nlohmann/json.hpp>
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
	// ゲームの制限時間
	constexpr float kLimitTime = 30.0f;

	// セーブデータのファイルパス
	const char* const kSaveDataPath = "Config\\SaveData.json";
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

	std::ifstream fIn(kSaveDataPath);

	// 成功したかチェック
	if (fIn.is_open())
	{
		// 変換
		fIn >> mSaveData;
	}
	// ファイルが無かったら新しく作る
	else
	{
		mSaveData["highscore"] = 0;
	}
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

		ImGui::Text(u8"成功回数 = %d", mSuccessNum);
		ImGui::SameLine();
		if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { mSuccessNum--; }
		ImGui::SameLine();
		if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { mSuccessNum++; }

		ImGui::SliderFloat(u8"残り時間 = %f", &mRemainTime, 0, kLimitTime);
	}

	ImGui::End();
}

void SceneMain::SuccessToDelivery()
{
	mSuccessNum++;

	mGameUI->CountUpLightNum();

	mObjHouseManager->EnableRandomHouse();
}

bool SceneMain::IsHighscore() const
{
	return mSuccessNum > mSaveData["highscore"];
}

void SceneMain::SaveHighscore()
{
	if (IsHighscore())
	{
		mSaveData["highscore"] = mSuccessNum;

		std::ofstream fOut(kSaveDataPath);
		fOut << std::setw(4) << mSaveData << std::endl;
	}
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

	// 残り時間が無くなったら
	if (mRemainTime <= 0)
	{
		mGameState = GameState::Result;

		SoundManager::GetInstance().PlaySE(Sound::SE::Finish);
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
