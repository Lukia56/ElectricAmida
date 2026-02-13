#include "Game.h"
#include <DxLib.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <cassert>
#include "../System/SceneManager.h"
#include "../System/InputManager.h"
#include "../Utility/Math.h"

namespace
{
	// システム設定データのファイルパス
	const char* const kSystemSettingDataPath = "Config\\SystemSetting.json";

	// デルタタイムの最大値
	constexpr float kMaxDeltaTime = 0.05f;
}

Game::Game() :
	mIsRunning(true),
	mTime(0),
	mElapsedTime(0),
	mPtrSceneManager(nullptr)
{
}

bool Game::Initialize()
{
	// DXライブラリを初期化
	if (DxLib_Init() == -1)
	{
		assert(false && "DXライブラリの初期化に失敗しました");
		return false;
	}

	if (!LoadSystemSetting()) return false;
	
	InitWindow();
	
	// 描画対象を裏画面に設定
	SetDrawScreen(DX_SCREEN_BACK);

	mTime = GetNowHiPerformanceCount();
	// 1Fの経過時間を計算
	mElapsedTime = static_cast<int>(1.0f / static_cast<float>(mSystemSettingData["fps"]) * 1000000.0f);

	// シーンを作るためにシーンマネージャーを作成
	mPtrSceneManager = new SceneManager();

	// 入力マネージャーを初期化する
	InputManager::GetInstance().Initialize();
	
	return true;
}

void Game::GameLoop()
{
	while (mIsRunning && ProcessMessage() == 0)
	{
		ProcessInput();
		ProcessUpdate();
		ProcessOutput();
	}
}

void Game::Finalize()
{
	if (mPtrSceneManager)
	{
		delete mPtrSceneManager;
	}

	DxLib_End();
}

void Game::ProcessInput()
{
	InputManager::GetInstance().Update();

	if (CheckHitKey(KEY_INPUT_ESCAPE))
	{
		mIsRunning = false;
	}
}

void Game::ProcessUpdate()
{
	// 1フレーム経過するまで待つ
	while (GetNowHiPerformanceCount() < mTime + mElapsedTime)
	{}

	// デルタタイムを計算
	float deltaTime = CalculateDeltaTime();
	mTime = GetNowHiPerformanceCount();
	
	mPtrSceneManager->Update(deltaTime);
}

void Game::ProcessOutput()
{
	// 画面の描画をすべて消す
	ClearDrawScreen();
	// デバッグ用文字列を消す
	clsDx();

	mPtrSceneManager->Draw();

	// 裏画面を表画面に反映する
	ScreenFlip();
}

bool Game::LoadSystemSetting()
{
	// システム設定のjsonファイルを取得
	std::ifstream fIn(kSystemSettingDataPath);

	// 成功したかチェック
	if (!fIn.is_open())
	{
		assert(false && "システム設定のデータの読み込みに失敗しました");
		return false;
	}

	// 変換
	fIn >> mSystemSettingData;

	return true;
}

void Game::InitWindow()
{
	// ウィンドウ名を設定
	std::string windowName = mSystemSettingData["defaultWindowText"];
	SetMainWindowText(windowName.c_str());

	// ウィンドウのサイズを指定
	SetGraphMode(mSystemSettingData["windowWidth"], mSystemSettingData["windowHeight"], mSystemSettingData["colorBit"]);

	// Debugビルドならウィンドウ、
	// Releaseビルドならフルスクリーンモードにする
#ifdef _DEBUG
	ChangeWindowMode(true);
#else
	ChangeWindowMode(false);
#endif
}

float Game::CalculateDeltaTime() const
{
	float dt = (GetNowHiPerformanceCount() - mTime) / 1000000.0f;
	
	// デルタタイムが大きすぎたら制限する
	if (dt > kMaxDeltaTime)
	{
		dt = kMaxDeltaTime;
	}

	return dt;
}
