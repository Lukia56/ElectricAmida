#include "SceneTest.h"
#include <DxLib.h>
#include "SceneBase.h"
#include "../Scene/Fader.h"
#include "../Utility/Color.h"
#include "../System/InputManager.h"
#include "../System/ObjectManager.h"

SceneTest::SceneTest()
{
}

SceneTest::~SceneTest()
{
}

void SceneTest::InitializeScene()
{
}

void SceneTest::EndScene()
{
}

SceneBase* SceneTest::UpdateScene()
{
	
	return this;
}

void SceneTest::DrawScene()
{
	DrawBox(440, 170, 540, 270, Color::kWhite, false);

	printfDx("INPUT::UP : %d\n", InputManager::GetInstance().IsHeld(Input::Action::Up));
	printfDx("INPUT::DOWN : %d\n", InputManager::GetInstance().IsHeld(Input::Action::Down));
	printfDx("INPUT::LEFT : %d\n", InputManager::GetInstance().IsHeld(Input::Action::Left));
	printfDx("INPUT::RIGHT : %d\n", InputManager::GetInstance().IsHeld(Input::Action::Right));
}
