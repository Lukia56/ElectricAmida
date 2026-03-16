#pragma once

#include "../Utility/Vector.h"

class SceneMain;
class Tween;

class GameUI
{
public:

	GameUI();

	~GameUI();

	void Init(SceneMain* scene);

	void End();

	void Update();

	void Draw();

	void CountUpLightNum();

	void CountDownTimer();

private:

	SceneMain* mSceneMain;
	int mGraphLightBulbIcon;
	int mGraphTimerIcon;

	Vector2 mLightIconPos;
	Vector2 mTimerIconPos;
	Vector2 mLightTextPos;
	Vector2 mTimerTextPos;

	Tween* mTween;
};
