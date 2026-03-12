#include "ImGuiRenderer.h"
#include <DxLib.h>
#include "../ImGui/imgui_impl_win32.h"
#include "../ImGui/imgui_impl_dx11.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
// ImGuiにプロシージャの情報を流す
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wp, lp))
	{
		return true;
	}
	return 0;
}

void ImGuiRenderer::Initialize()
{
	// DxLibが持つDirectXの情報を取得する
	auto g_pd3dDevice = (ID3D11Device*)(GetUseDirect3D11Device());
	auto g_pd3dDeviceContext = (ID3D11DeviceContext*)GetUseDirect3D11DeviceContext();

	// ImGuiを初期化
	ImGui::CreateContext();
	ImGui_ImplWin32_Init(GetMainWindowHandle());
	ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

	// フォントの初期化
	// アルファベットはデフォルトのままに、日本語のみを変更
	ImGuiIO& io = ImGui::GetIO();
	ImFontConfig config;
	config.MergeMode = true;
	io.Fonts->AddFontDefault();
	io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\meiryo.ttc", 20.0f, &config, ImGui::GetIO().Fonts->GetGlyphRangesJapanese());

	// ウインドウプロージャを登録する
	SetHookWinProc(WndProc);
}

void ImGuiRenderer::End()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiRenderer::Draw(std::function<void(void)> func)
{
	// 描画準備
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	auto& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_::ImGuiCol_WindowBg].w = 0.5f;

	// 描画処理
	func();

	// 描画データを表示する
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
