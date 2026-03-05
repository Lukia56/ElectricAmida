#pragma once

#include "SceneBase.h"
#include "../Utility/Vector.h"

/// <summary>
/// タイトル画面のシーン
/// </summary>
class SceneTitle : public SceneBase
{
public:

	/// <summary>
	/// メンバの初期設定を行う
	/// 削除されてしまうため、ゲームオブジェクトの作成は行わない
	/// </summary>
	SceneTitle();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SceneTitle() = default;

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
	/// 更新
	/// </summary>
	/// <returns>SceneBase型のポインタ 次に処理する画面</returns>
	SceneBase* UpdateScene() override;

	/// <summary>
	/// 描画
	/// </summary>
	void DrawScene() override;

private:

	int mGraphLogo;

	int mMenuChoice;

	Vector2 mArrowPos;
};
