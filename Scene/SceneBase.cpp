#include "SceneBase.h"
#include <DxLib.h>
#include <cassert>
#include <algorithm>
#include "../System/SceneManager.h"
#include "../System/ObjectManager.h"
#include "../Utility/Color.h"
#include "../Scene/Fader.h"

// コンストラクタ
SceneBase::SceneBase() :
	mPtrSceneManager(nullptr),
	mPtrObjectManager(nullptr),
	mPtrNextScene(nullptr),
	mPtrFader(nullptr)
{
	mPtrObjectManager = new ObjectManager();
	mPtrObjectManager->Init();

	mPtrFader = new Fader(this);
}

SceneBase::~SceneBase()
{
}

void SceneBase::Initialize(SceneManager* manager)
{
	mPtrSceneManager = manager;

	InitializeScene();
}

void SceneBase::End()
{
	mPtrObjectManager->End();
	delete mPtrObjectManager;

	delete mPtrFader;

	EndScene();
}

SceneBase* SceneBase::Update()
{
	if (mPtrFader->Update()) return mPtrNextScene;

	mPtrObjectManager->Update();

	return UpdateScene();
}

void SceneBase::Draw()
{
	// シーンの描画処理
	DrawScene();

	mPtrObjectManager->Draw();

	// フェードインアウトのフィルター処理
	mPtrFader->Draw();
}
