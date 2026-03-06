#pragma once

#include <functional>
#include "../Utility/Vector.h"

class ObjectManager;

/// <summary>
/// ゲームオブジェクトの基底クラス
/// </summary>
class GameObject
{
public:

	enum class State
	{
		EActive,
		EDeactive,
		EDead
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="manager">オブジェクトマネージャーのポインタ</param>
	GameObject(ObjectManager* manager);

	/// <summary>
	/// デストラクタ
	/// 派生クラスを破棄した時に備えて仮想デストラクタ化
	/// </summary>
	virtual ~GameObject();

	/// <summary>
	/// 処理を実行する
	/// </summary>
	/// <param name="ptrFunc">関数ポインタ</param>
	void RunProcess(std::function<void()> ptrFunc);

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init();

	/// <summary>
	/// 後処理
	/// </summary>
	void End();

	/// <summary>
	/// ゲームオブジェクト固有の初期化処理
	/// </summary>
	virtual void InitGameObject() {};

	/// <summary>
	/// ゲームオブジェクト固有の後処理
	/// </summary>
	virtual void EndGameObject() {};

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update() {};

	/// <summary>
	/// 更新処理の前に実行する処理
	/// </summary>
	virtual void PreUpdate() {};

	/// <summary>
	/// 更新処理の後に実行する処理
	/// </summary>
	virtual void PostUpdate() {};

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw() {};

	/// <summary>
	/// 描画処理の前に実行する処理
	/// </summary>
	virtual void PreDraw() {};

	/// <summary>
	/// 描画処理の後に実行する処理
	/// </summary>
	virtual void PostDraw() {};

	/// <summary>
	/// ImGuiの描画処理
	/// </summary>
	virtual void DrawImGui() {};

	/// <summary>
	/// オブジェクトマネージャーのゲッター
	/// </summary>
	/// <returns>オブジェクトマネージャーのポインタ</returns>
	ObjectManager* GetObjectManager() const { return mPtrObjManager; }

	/// <summary>
	/// 状態を取得する
	/// </summary>
	/// <returns>状態</returns>
	State GetState() const { return mState; }
	/// <summary>
	/// 状態を設定する
	/// </summary>
	/// <param name="state">状態</param>
	void SetState(const State state) { mState = state; }

	Vector2 GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; }

	Vector2 GetScale() const { return mScale; }
	void SetScale(const Vector2& scale) { mScale = scale; }

	float GetRotation() const { return mRotation; }
	void SetRotation(const float rot) { mRotation = rot; }

private:

	/// <summary>
	/// オブジェクトマネージャーのポインタ
	/// </summary>
	ObjectManager* mPtrObjManager;

	/// <summary>
	/// 自身の状態
	/// </summary>
	State mState;

	/// <summary>
	/// 座標
	/// </summary>
	Vector2 mPosition;

	/// <summary>
	/// スケール
	/// </summary>
	Vector2 mScale;

	/// <summary>
	/// 角度
	/// </summary>
	float mRotation;
};
