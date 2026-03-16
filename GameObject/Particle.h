#pragma once

#include "GameObject.h"

class Particle : public GameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="manager">オブジェクトマネージャーのポインタ</param>
	/// <param name="pos">初期位置</param>
	Particle(ObjectManager* manager, Vector2 pos);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Particle() = default;

	/// <summary>
	/// ゲームオブジェクト固有の初期化処理
	/// </summary>
	void InitGameObject() override;

	/// <summary>
	/// ゲームオブジェクト固有の後処理
	/// </summary>
	void EndGameObject() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;

private:

	int mAlpha;
};
