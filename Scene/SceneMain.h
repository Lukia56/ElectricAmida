#pragma once

#include "SceneBase.h"
#include <vector>
#include <unordered_map>
#include <string>
#include "../Utility/Vector.h"

class WireManager;
class Electricity;
class HouseManager;

class SceneMain : public SceneBase
{
public:

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

private:

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
};
