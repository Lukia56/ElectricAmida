#include "SceneGameOver.h"
#include "../System/InputManager.h"
#include "../Scene/SceneMain.h"
#include "../Scene/Fader.h"

SceneGameOver::SceneGameOver()
{
}

SceneGameOver::~SceneGameOver()
{
}

void SceneGameOver::InitializeScene()
{
}

void SceneGameOver::EndScene()
{
}

SceneBase* SceneGameOver::UpdateScene()
{
	// 決定（スペース）キーが押されたら
	if (InputManager::GetInstance().IsPressed(Input::Action::Confirm))
	{
		// SceneMainに遷移する
		GetFader()->StartFadeOut<SceneMain>();
	}

	return this;
}

void SceneGameOver::DrawScene()
{
	printfDx("ゲームオーバー（仮）\n");
	printfDx("スペースキーでリプレイ\n");
}
