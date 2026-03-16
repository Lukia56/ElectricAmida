#include "Tree.h"
#include <DxLib.h>

Tree::Tree(ObjectManager* manager, int graph, Vector2& pos) :
	GameObject(manager),
	mGraph(graph)
{
	SetPosition(pos);
}

void Tree::InitGameObject()
{
}

void Tree::EndGameObject()
{
}

void Tree::Update()
{
}

void Tree::Draw()
{
	Vector2 pos = GetPosition();

	DrawGraph(pos.x, pos.y, mGraph, 1);
}

void Tree::DrawImGui()
{
}
