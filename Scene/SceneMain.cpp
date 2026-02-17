#include "SceneMain.h"
#include <DxLib.h>
#include "SceneBase.h"
#include "../Scene/Fader.h"
#include "../Utility/Color.h"
#include "../System/InputManager.h"
#include "../GameObject/WireManager.h"
#include "../GameObject/Electricity.h"
#include "../GameObject/HouseManager.h"

namespace
{
}

SceneMain::SceneMain() :
	mObjWireManager(nullptr),
	mObjElectricity(nullptr),
	mObjHouseManager(nullptr)
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::InitializeScene()
{
	mObjWireManager = new WireManager(GetObjectManager());
	mObjWireManager->Init();

	mObjHouseManager = new HouseManager(GetObjectManager(), mObjWireManager);
	mObjHouseManager->Init();
}

void SceneMain::EndScene()
{
	mObjElectricity = nullptr;
	mObjWireManager = nullptr;
	mObjHouseManager = nullptr;
}

SceneBase* SceneMain::UpdateScene()
{
	if (InputManager::GetInstance().IsPressed(Input::Action::Down) && !mObjElectricity)
	{
		mObjElectricity = new Electricity(GetObjectManager(), mObjWireManager);
		mObjElectricity->Init();
	}

	return this;
}

void SceneMain::DrawScene()
{
	
}
