#pragma once

#include "SceneBase.h"
#include <vector>
#include <unordered_map>
#include <string>
#include "../Utility/Vector.h"

class WireManager;
class Electricity;
class HouseManager;
class GameUI;
class PauseManager;
class ResultUI;
class ReadyUI;

class SceneMain : public SceneBase
{
public:

	enum GameState
	{
		Ready,
		Play,
		Result
	};

	/// <summary>
	/// コンストラクタ
	/// メンバの初期設定を行う
	/// 削除されてしまうため、ゲームオブジェクトの作成は行わない
	/// </summary>
	SceneMain();

	/// <summary>
	/// デストラクタ
	/// メンバの後処理を行う
	/// </summary>
	virtual ~SceneMain();

	/// <summary>
	/// シーンの初期設定を行う
	/// シーン開始時からのゲームオブジェクトはここで作成する
	/// </summary>
	void InitializeScene() override;

	/// <summary>
	/// シーンの終了処理を行う
	/// </summary>
	void EndScene() override;

	/// <summary>
	/// SceneTest画面の処理を行う
	/// </summary>
	/// <returns>SceneBase型のポインタ 次に処理する画面</returns>
	SceneBase* UpdateScene() override;

	/// <summary>
	/// SceneTest画面の描画を行う
	/// </summary>
	void DrawScene() override;

	/// <summary>
	/// ImGuiの描画
	/// </summary>
	void DrawSceneImGui() override;

	/// <summary>
	/// 電気を届けるのに成功した数を加算する
	/// </summary>
	void SuccessToDelivery();

	GameState GetGameState() const { return mGameState; }
	
	/// <summary>
	/// 成功数を取得する
	/// </summary>
	/// <returns></returns>
	int GetSuccessNum() const { return mSuccessNum; }

	/// <summary>
	/// 残り時間を取得する
	/// </summary>
	/// <returns></returns>
	int GetRemainTime() const { return mRemainTime; }

	/// <summary>
	/// 予算を取得する
	/// </summary>
	/// <returns>現在の予算</returns>
	int GetBudget() const { return mBudget; }
	/// <summary>
	/// 予算を設定
	/// </summary>
	/// <param name="budget">予算</param>
	void SetBudget(const int budget) { mBudget = budget; }

private:

	void GameReady();

	void GamePlay();

	void GameResult();

	/// <summary>
	/// 電線のマネージャーのゲームオブジェクト
	/// </summary>
	WireManager* mObjWireManager;

	/// <summary>
	/// 電気のゲームオブジェクト
	/// </summary>
	Electricity* mObjElectricity;

	/// <summary>
	/// 住宅のマネージャーのゲームオブジェクト
	/// </summary>
	HouseManager* mObjHouseManager;

	/// <summary>
	/// ゲームの進行状態
	/// </summary>
	GameState mGameState;

	/// <summary>
	/// 電気を届けるのに成功した数
	/// </summary>
	int mSuccessNum;

	/// <summary>
	/// ゲームの残り時間
	/// </summary>
	float mRemainTime;

	/// <summary>
	/// 電線を引く予算
	/// </summary>
	int mBudget;

	GameUI* mGameUI;

	PauseManager* mPauseManager;

	ResultUI* mResultUI;

	ReadyUI* mReadyUI;
};
