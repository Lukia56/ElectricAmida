#pragma once
#include "SceneBase.h"
#include <DxLib.h>

/// <summary>
/// 確認用のクラス
/// なにか機能の確認を行うときにこのクラスで検証をする
/// </summary>
class SceneTest : public SceneBase
{
public:

	/// <summary>
	/// SceneTest画面のコンストラクタ
	/// メンバの初期設定を行う
	/// 削除されてしまうため、ゲームオブジェクトの作成は行わない
	/// </summary>
	SceneTest();

	/// <summary>
	/// SceneTest画面のデストラクタ
	/// メンバの後処理を行う
	/// </summary>
	virtual ~SceneTest();

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
