#pragma once

#include "SceneBase.h"

class SceneGameClear : public SceneBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// メンバの初期設定を行う
	/// 削除されてしまうため、ゲームオブジェクトの作成は行わない
	/// </summary>
	SceneGameClear();

	/// <summary>
	/// デストラクタ
	/// メンバの後処理を行う
	/// </summary>
	virtual ~SceneGameClear();

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


};
