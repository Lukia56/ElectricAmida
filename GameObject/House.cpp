#include "House.h"
#include <DxLib.h>
#include "../Utility/Color.h"
#include "WireManager.h"

House::House(ObjectManager* manager) :
	GameObject(manager),
	mIsEnabled(false)
{
}

House::~House()
{
}

void House::InitGameObject()
{
}

void House::EndGameObject()
{
}

void House::Update()
{
}

void House::Draw()
{
	int color = mIsEnabled ? Color::kYellow : Color::kRed;

	const auto& pos = GetPosition();
	DrawBox(pos.x - 40, pos.y - 40, pos.x + 40, pos.y + 40, color, true);
}
