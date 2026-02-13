#include "SceneMain.h"
#include <DxLib.h>
#include "SceneBase.h"
#include "../Scene/Fader.h"
#include "../Utility/Color.h"
#include "../System/InputManager.h"
#include "../GameObject/WireManager.h"
#include "../GameObject/Electricity.h"

namespace
{
}

SceneMain::SceneMain() :
	mObjWireManager(nullptr),
	mObjElectricity(nullptr)
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::InitializeScene()
{
	mObjWireManager = new WireManager(GetObjectManager());
	mObjWireManager->Init();
}

void SceneMain::EndScene()
{
	mObjElectricity->End();
	delete mObjElectricity;

	if (mObjElectricity)
	{
		mObjElectricity->End();
		delete mObjElectricity;
	}
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
