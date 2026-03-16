#include "Particle.h"
#include <DxLib.h>
#include <cmath>
#include "../Utility/Color.h"
#include "../Utility/Math.h"
#include "../System/Time.h"

namespace
{
	constexpr float kMoveSpeed = 100;
	constexpr int kFadeOutSpeed = 16;
}

Particle::Particle(ObjectManager* manager, Vector2 pos) :
	GameObject(manager),
	mAlpha(255)
{
	SetPosition(pos);
}

void Particle::InitGameObject()
{
	SetRotation(Math::ToRadian(GetRand(360)));
}

void Particle::EndGameObject()
{

}

void Particle::Update()
{
	mAlpha -= kFadeOutSpeed;

	if (mAlpha <= 0) SetState(State::EDead);

	Vector2 pos = GetPosition();

	Vector2 move = Vector2(
		std::sin(GetRotation()) * kMoveSpeed * Time::GetInstance().GetDeltaTime(),
		std::cos(GetRotation()) * kMoveSpeed * Time::GetInstance().GetDeltaTime());

	SetPosition(pos + move);
}

void Particle::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, mAlpha);

	Vector2 pos = GetPosition();
	
	DrawCircle(pos.x, pos.y, 3, Color::kYellow);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
