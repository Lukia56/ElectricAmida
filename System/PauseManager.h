#pragma once

class ObjectManager;
class SceneBase;

class PauseManager
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	PauseManager(ObjectManager* objManager, SceneBase* scene);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PauseManager();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// ポーズ中かどうかを取得
	/// </summary>
	/// <returns>ポーズ中かつ描画画面を取得済みならtrue</returns>
	bool IsPaused() const { return mIsPaused && mScreenGraph != -1; }

private:

	/// <summary>
	/// ポーズ中の処理
	/// </summary>
	void OnPause();

	/// <summary>
	/// ポーズ状態を切り替える
	/// </summary>
	void TogglePause();

	/// <summary>
	/// ポーズ前の画面のグラフィックハンドル
	/// </summary>
	int mScreenGraph;

	/// <summary>
	/// ポーズしているかどうか
	/// </summary>
	bool mIsPaused;

	/// <summary>
	/// メニューで選択している場所
	/// </summary>
	int mMenuChoice;

	ObjectManager* mObjectManager;

	SceneBase* mScene;
};
