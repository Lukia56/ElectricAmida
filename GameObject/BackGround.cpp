#include "BackGround.h"
#include <DxLib.h>
#include "../GameObject/Tree.h"

namespace
{
	const char* const kGraphTreePath = "Resources\\Image\\tree.png";

	constexpr int kTreeNum = 10;
}

BackGround::BackGround(ObjectManager* manager) :
	GameObject(manager),
	mGraphTree(-1)
{
}

void BackGround::InitGameObject()
{
	mGraphTree = LoadGraph(kGraphTreePath);

	Tree* tree;
	Vector2 pos = Vector2(20, 640);

	for (int i = 0; i < kTreeNum; i++)
	{
		tree = new Tree(GetObjectManager(), mGraphTree, pos);
		tree->Init();

		pos.y -= 40 + GetRand(60);
	}

	pos = Vector2(460, 640);
	for (int i = 0; i < kTreeNum; i++)
	{
		tree = new Tree(GetObjectManager(), mGraphTree, pos);
		tree->Init();

		pos.y -= 40 + GetRand(60);
	}
}

void BackGround::EndGameObject()
{
	DeleteGraph(mGraphTree);
}

void BackGround::Update()
{
}

void BackGround::Draw()
{
}

void BackGround::DrawImGui()
{
}
