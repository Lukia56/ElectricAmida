#include "Easing.h"
#include "Time.h"

Tween& Tween::GetInstance()
{
	static Tween instance;

	return instance;
}

void Tween::Update()
{
	for (auto iter = mData.begin(); iter < mData.end();)
	{
		auto& data = *iter;

		if (data.delay <= 0)
		{
			if (data.duration > data.time)
			{
				data.time += Time::GetInstance().GetDeltaTime();

				*data.value = data.start + (data.end - data.start) * Easing(data.ease, data.time / data.duration);
			}
			else
			{
				*data.value = data.end;
			}
		}
		else
		{
			data.delay -= Time::GetInstance().GetDeltaTime();

			iter = mData.erase(iter);

			continue;
		}

		iter++;
	}
}

float Tween::Easing(Animation::Ease ease, float time)
{
	float begin = 0;
	float change = 1;
	float duration = 1;

	switch (ease)
	{
	case Animation::Ease::Linear:

		return begin + change * time / duration;
	}

	return 0;
}
