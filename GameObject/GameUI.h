#pragma once

class SceneMain;

class GameUI
{
public:

	GameUI();

	~GameUI();

	void Init(SceneMain* scene);

	void End();

	void Draw();

private:

	SceneMain* mSceneMain;
	int mGraphMoneyIcon;
	int mGraphLightBulbIcon;
	int mGraphTimerIcon;
};
