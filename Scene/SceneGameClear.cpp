#include "SceneGameClear.h"
#include "../System/InputManager.h"
#include "../Scene/SceneMain.h"
#include "../Scene/Fader.h"

SceneGameClear::SceneGameClear()
{
}

SceneGameClear::~SceneGameClear()
{
}

void SceneGameClear::InitializeScene()
{
}

void SceneGameClear::EndScene()
{
}

SceneBase* SceneGameClear::UpdateScene()
{
	// 決定（スペース）キーが押されたら
	if (InputManager::GetInstance().IsPressed(Input::Action::Confirm))
	{
		// SceneMainに遷移する
		GetFader()->StartFadeOut<SceneMain>();
	}

	return this;
}

void SceneGameClear::DrawScene()
{
	printfDx("ゲームクリア（仮）\n");
	printfDx("スペースキーでリプレイ\n");
}
