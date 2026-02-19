#include "SceneTest.h"
#include <DxLib.h>
#include "SceneBase.h"
#include "../Scene/Fader.h"
#include "../Utility/Color.h"
#include "../System/InputManager.h"
#include "../System/ObjectManager.h"
#include "../Collision/Collision2D.h"

SceneTest::SceneTest()
{
	mRect.left = 100;
	mRect.top = 100;
	mRect.right = 300;
	mRect.bottom = 300;

	mCircle.center = Vector2(480, 270);
	mCircle.radius = 50;
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
	auto& input = InputManager::GetInstance();

	Vector2 move(input.IsHeld(Input::Action::Right) - input.IsHeld(Input::Action::Left), input.IsHeld(Input::Action::Down) - input.IsHeld(Input::Action::Up));

	mCircle.center += move * 10;
	
	return this;
}

void SceneTest::DrawScene()
{
	int color = Color::kWhite;
	if (Collision::IsIntersect(mRect, mCircle))
	{
		color = Color::kRed;
	}

	DrawBox(mRect.left, mRect.top, mRect.right, mRect.bottom, color, 0);

	DrawCircle(mCircle.center.x, mCircle.center.y, mCircle.radius, color, 0);
}
