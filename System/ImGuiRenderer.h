#pragma once

#include <functional>

/// <summary>
/// ImGuiを管理して描画するクラス
/// </summary>
class ImGuiRenderer
{
public:

	ImGuiRenderer() = default;
	~ImGuiRenderer() = default;

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 終了処理
	/// </summary>
	void End();

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="func">ImGuiに描画する関数ポインタ</param>
	void Draw(std::function<void(void)> func);
};
