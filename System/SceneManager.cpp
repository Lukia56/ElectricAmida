#include "SceneManager.h"
#include <DxLib.h>
#include <cassert>
#include "../Game.h"
#include "../Scene/SceneBase.h"
#include "../Scene/SceneMain.h"
#include "../Scene/SceneTitle.h"
#include "../Scene/Fader.h"

SceneManager::SceneManager() :
	mPtrScene(nullptr)
{
	mPtrScene = new SceneMain();
	mPtrScene->Initialize(this);
}

SceneManager::~SceneManager()
{
	assert(mPtrScene && "m_pSceneがnullptrです");
	if (!mPtrScene) return;

	mPtrScene->End();
	delete mPtrScene;
}

void SceneManager::Update()
{
	// 確認処理
	assert(mPtrScene && "m_pSceneがnullptrです");
	if (!mPtrScene) return;

	// シーンの切り替えもしくは更新
	SceneBase* pScene = mPtrScene->Update();

	// シーンが切り替えられていたら
	if (pScene != mPtrScene)
	{
		// フェーダーの色を共有する
		int faderColor = mPtrScene->GetFader()->GetFadeColor();	// 前のシーンのフェーダーの色を取得
		pScene->GetFader()->SetFadeColor(faderColor);			// 次のシーンのフェーダーの色を変更

		// 前のシーンを削除
		mPtrScene->End();
		delete mPtrScene;

		// 次のシーンを初期化
		mPtrScene = pScene;
		mPtrScene->Initialize(this);
	}
}

void SceneManager::Draw()
{
	// 確認処理
	assert(mPtrScene && "m_pSceneがnullptrです");
	if (!mPtrScene) return;

	mPtrScene->Draw();
}

void SceneManager::DrawImGui()
{
	// 確認処理
	assert(mPtrScene && "m_pSceneがnullptrです");
	if (!mPtrScene) return;

	mPtrScene->DrawImGui();
}
