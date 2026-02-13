#include "GameObject.h"
#include "../System/ObjectManager.h"
#include "../Utility/Vector.h"

GameObject::GameObject(ObjectManager* manager) :
	mPtrObjManager(manager),
	mState(State::EActive),
	mPosition(Vector2::Zero),
	mScale(Vector2::One),
	mRotation(0.0f)
{
	mPtrObjManager->AddGameObject(this);
}

GameObject::~GameObject()
{
	mPtrObjManager->RemoveGameObject(this);
}

void GameObject::RunProcess(std::function<void()> ptrFunc)
{
	if (mState != State::EActive) return;

	ptrFunc();
}

void GameObject::Init()
{
	InitGameObject();
}

void GameObject::End()
{
	EndGameObject();
}
