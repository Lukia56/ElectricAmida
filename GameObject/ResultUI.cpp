#include "ResultUI.h"
#include <DxLib.h>
#include <vector>
#include "../System/InputManager.h"
#include "../Utility/Color.h"
#include "../ImGui/imgui.h"
#include "../Scene/SceneMain.h"
#include "../Scene/SceneTitle.h"
#include "../Scene/Fader.h"
#include "../Easing/Tween.h"
#include "../Easing/Keyframe.h"
#include "../Utility/Vector.h"

namespace
{
	const Vector2 kCenterPos = { 240, 360 };

	const Vector2 kBoxSize = { 300, 400 };

	// メニュー画面の項目一覧
	enum Choice
	{
		Retry,
		Quit,
		Max
	};
}

ResultUI::ResultUI(ObjectManager* manager, SceneMain* scene) :
	GameObject(manager),
	mScene(scene),
	mMenuChoice(0),
	mAlpha(0),
	mMenuY(0.0f),
	mTween(nullptr)
{
	SetPosition(kCenterPos);
}

ResultUI::~ResultUI()
{
}

void ResultUI::InitGameObject()
{
	mTween = new Tween();
	
	std::vector<Animation::Keyframe> keyframes;
	keyframes.emplace_back(Animation::Keyframe{ 50.0f, 0, Animation::Ease::QuadOut });
	keyframes.emplace_back(Animation::Keyframe{ 0.0f, 60 });
	mTween->StartAnim(&mMenuY, keyframes);

	keyframes.clear();
	keyframes.emplace_back(Animation::Keyframe{ 0.0f, 0, Animation::Ease::Linear });
	keyframes.emplace_back(Animation::Keyframe{ 255.0f, 10 });
	mTween->StartAnim(&mAlpha, keyframes);
}

void ResultUI::EndGameObject()
{
	delete mTween;
	mTween = nullptr;
}

void ResultUI::Update()
{
	// 上下ボタンで選択場所を移動
	if (InputManager::GetInstance().IsPressed(Input::Action::MenuUp)) mMenuChoice--;
	if (InputManager::GetInstance().IsPressed(Input::Action::MenuDown)) mMenuChoice++;

	// 選択場所を項目の範囲内に収める
	mMenuChoice = (mMenuChoice + Choice::Max) % Choice::Max;

	// 決定ボタンが押されたら項目を選ぶ
	if (InputManager::GetInstance().IsPressed(Input::Action::Confirm))
	{
		switch (mMenuChoice)
		{
		case Choice::Retry:

			mScene->GetFader()->StartFadeOut<SceneMain>();

			break;

		case Choice::Quit:

			mScene->GetFader()->StartFadeOut<SceneTitle>();

			break;
		}
	}

	mTween->Update();
}

void ResultUI::Draw()
{

}

void ResultUI::PostDraw()
{
	Vector2 pos = GetPosition();
	pos.y += mMenuY;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, mAlpha);

	DrawBox(pos.x - kBoxSize.x * 0.5f, pos.y - kBoxSize.y * 0.5f, pos.x + kBoxSize.x * 0.5f, pos.y + kBoxSize.y * 0.5f, Color::kWhite, true);

	DrawString(pos.x - 40, pos.y - 140, "スコア", Color::kBlack);
	DrawString(pos.x - 90, pos.y - 40, "電気を届けた数：", Color::kBlack);
	DrawString(pos.x + 60, pos.y - 40, std::to_string(mScene->GetSuccessNum()).c_str(), Color::kBlack);

	DrawString(pos.x - 40, pos.y + 100, "リトライ", mMenuChoice == 0 ? 0x00ffff : Color::kBlack);
	DrawString(pos.x - 80, pos.y + 140, "タイトル画面へ戻る", mMenuChoice == 1 ? 0x00ffff : Color::kBlack);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void ResultUI::DrawImGui()
{
	if (ImGui::Begin("GameObject"))
	{
		ImGui::Text("[ResultUI]");

		ImGui::Text("MenuChoice = %d", mMenuChoice);

		ImGui::SliderFloat("Alpha", &mAlpha, 0, 255);
	}

	ImGui::End();
}
