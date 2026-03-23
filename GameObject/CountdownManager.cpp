#include "CountdownManager.h"
#include <DxLib.h>
#include <cmath>
#include "../Scene/SceneMain.h"
#include "../GameObject/CountNumber.h"
#include "../ImGui/imgui.h"

namespace
{
	enum Number
	{
		Three,
		Two,
		One
	};

	const char* const kGraphPaths[3] = {
		"Resources\\Image\\1.png",
		"Resources\\Image\\2.png",
		"Resources\\Image\\3.png"
	};

	const char* const kGraphPathThree = "Resources\\Image\\3.png";
	const char* const kGraphPathTwo = "Resources\\Image\\2.png";
	const char* const kGraphPathOne = "Resources\\Image\\1.png";
}

CountdownManager::CountdownManager(ObjectManager* manager, SceneMain* scene) :
	GameObject(manager),
	mScene(scene),
	mCurrentCounting(30)
{
	mNumberGraphs.fill(-1);
}

void CountdownManager::InitGameObject()
{
	// グラフィックハンドルを読み込み
	for (int i = 0; i < mNumberGraphs.size(); i++)
	{
		mNumberGraphs[i] = LoadGraph(kGraphPaths[i]);
	}
}

void CountdownManager::EndGameObject()
{
	for (int i = mNumberGraphs.size() - 1; i > 0; i--)
	{
		DeleteGraph(mNumberGraphs[i]);
	}
}

void CountdownManager::Update()
{
	if (std::ceil(mScene->GetRemainTime()) < mCurrentCounting)
	{
		mCurrentCounting--;

		if (mCurrentCounting > 3 || mCurrentCounting <= 0) return;
		
		// カウントを表示
		auto count = new CountNumber(GetObjectManager(), mNumberGraphs[mCurrentCounting - 1]);
		count->Init();
	}
}

void CountdownManager::DrawImGui()
{
	if (ImGui::Begin("GameObject"))
	{
		ImGui::Text("[CountdownManager]");

		ImGui::Text("CurrentCounting:%d", mCurrentCounting);
	}

	ImGui::End();
}
