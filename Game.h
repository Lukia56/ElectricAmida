#pragma once

#include <DxLib.h>
#include <nlohmann/json.hpp>

class SceneManager;
class ImGuiRenderer;

using json = nlohmann::json;

/// <summary>
/// ゲーム全体を管理するクラス
/// </summary>
class Game
{
public:

	/// <summary>
	/// ゲームを実行するかどうか
	/// </summary>
	static bool isRunning;

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Game();

	/// <summary>
	/// ゲームの初期化処理を行う
	/// </summary>
	/// <returns>初期化に成功したらtrue、失敗したらfalseを返す</returns>
	bool Initialize();

	/// <summary>
	/// ゲームループ
	/// </summary>
	void GameLoop();

	/// <summary>
	/// 終了処理を行う
	/// </summary>
	void Finalize();

	/// <summary>
	/// シーンマネージャーのゲッター
	/// </summary>
	/// <returns>シーンマネージャーのポインタ</returns>
	SceneManager* GetSceneManager() { return mPtrSceneManager; }

	/// <summary>
	/// システム設定のデータのゲッター
	/// </summary>
	/// <returns>システム設定のデータ</returns>
	json GetSystemSetting() { return mSystemSettingData; }

private:

	/// <summary>
	/// 入力処理
	/// </summary>
	void ProcessInput();

	/// <summary>
	/// 更新処理
	/// </summary>
	void ProcessUpdate();

	/// <summary>
	/// 出力処理
	/// </summary>
	void ProcessOutput();

	/// <summary>
	/// システム設定のjsonファイルを読み込む
	/// </summary>
	/// <returns>読み込みに成功したらtrue</returns>
	bool LoadSystemSetting();

	/// <summary>
	/// ウィンドウ関連の初期化
	/// </summary>
	void InitWindow();

	/// <summary>
	/// 1F経過にかかった秒数（デルタタイム）を計算する
	/// </summary>
	/// <returns>デルタタイムを返す</returns>
	float CalculateDeltaTime() const;

	/// <summary>
	/// フレームの開始時間
	/// </summary>
	LONGLONG mTime;

	/// <summary>
	/// 1フレーム経過するのにかかる時間
	/// </summary>
	int mElapsedTime;

	/// <summary>
	/// システム設定のデータ
	/// </summary>
	json mSystemSettingData;

	/// <summary>
	/// シーンマネージャーのポインタ
	/// </summary>
	SceneManager* mPtrSceneManager;

	/// <summary>
	/// ImGuiのレンダラー
	/// </summary>
	ImGuiRenderer* mImGuiRenderer;
};
