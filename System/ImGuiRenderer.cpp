#include "ImGuiRenderer.h"
#include <DxLib.h>
#include "../ImGui/imgui_impl_win32.h"
#include "../ImGui/imgui_impl_dx11.h"

ImGuiRenderer::ImGuiRenderer()
{
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
	io.Fonts->AddFontFromFileTTF("c:/Users/student1/AppData/Local/Microsoft/Windows/Fonts/JF-Dot-K12.ttf", 12.0f, &config, ImGui::GetIO().Fonts->GetGlyphRangesJapanese());
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

	// 描画処理
	func();

	// 描画データを表示する
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
