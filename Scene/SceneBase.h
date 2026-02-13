#pragma once

#include <vector>

class ObjectManager;
class SceneManager;
class Fader;

/// <summary>
/// 各画面の基本クラス
/// 基本的にはこのクラスを継承して各画面のクラスを作成する
/// 作成したクラスをSceneManagerクラスから呼び出すことで保守しやすくする
/// </summary>
class SceneBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// メンバ変数の初期設定
	/// 削除されてしまうため、ゲームオブジェクトの作成は行わない
	/// </summary>
	SceneBase();

	/// <summary>
	/// デストラクタ
	/// 派生クラスを破棄した時に備えて仮想デストラクタ化
	/// </summary>
	virtual ~SceneBase();
	
	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="manager">シーンマネージャーのポインタ</param>
	void Initialize(SceneManager* manager);

	/// <summary>
	/// シーンの初期設定を行う
	/// シーン開始時からのゲームオブジェクトはここで作成する
	/// </summary>
	virtual void InitializeScene() = 0;

	/// <summary>
	/// 終了処理
	/// </summary>
	void End();

	/// <summary>
	/// シーンの終了処理を行う
	/// </summary>
	virtual void EndScene() = 0;

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <returns>自身のポインタを返す</returns>
	SceneBase* Update();

	/// <summary>
	/// シーンの更新処理
	/// </summary>
	/// <returns>自身のポインタを返す</returns>
	virtual SceneBase* UpdateScene() = 0;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// シーンの描画処理
	/// </summary>
	virtual void DrawScene() = 0;

	/// <summary>
	/// フェーダーのゲッター
	/// </summary>
	/// <returns>フェーダーのポインタ</returns>
	Fader* GetFader() const { return mPtrFader; }

	/// <summary>
	/// シーンマネージャーのポインタを取得
	/// </summary>
	/// <returns>シーンマネージャーのポインタ</returns>
	SceneManager* GetSceneManager() const { return mPtrSceneManager; }

	/// <summary>
	/// オブジェクトマネージャーのポインタを取得
	/// </summary>
	/// <returns>オブジェクトマネージャーのポインタ</returns>
	ObjectManager* GetObjectManager() const { return mPtrObjectManager; }

	/// <summary>
	/// 次のシーンのセッター
	/// </summary>
	/// <param name="next">次のシーンのポインタ</param>
	void SetNextScene(SceneBase* next) { mPtrNextScene = next; }

private:

	/// <summary>
	/// シーンマネージャーのポインタ
	/// </summary>
	SceneManager* mPtrSceneManager;

	/// <summary>
	/// オブジェクトマネージャーのポインタ
	/// </summary>
	ObjectManager* mPtrObjectManager;

	/// <summary>
	/// 次のシーンのポインタ
	/// </summary>
	SceneBase* mPtrNextScene;

	/// <summary>
	/// フェーダーのポインタ
	/// </summary>
	Fader* mPtrFader;
};
