//#pragma once
//
//#include <vector>
//
//namespace Animation
//{
//	struct Data
//	{
//		float* value;
//		float start;
//		float end;
//		Ease ease;
//		float duration;
//		float delay;
//		float time;
//	};
//
//	enum class Ease
//	{
//		Linear,
//		QuadIn,
//		QuadOut,
//		QuadInOut,
//		CubicIn,
//		CubicOut,
//		CubicInOut,
//		QuartIn,
//		QuartOut,
//		QuartInOut,
//		QuintIn,
//		QuintOut,
//		QuintInOut,
//		ExpoIn,
//		ExpoOut,
//		ExpoInOut,
//		SineIn,
//		SineOut,
//		SineInOut,
//		CircIn,
//		CircOut,
//		CircInOut,
//		BackIn,
//		BackOut,
//		BackInOut,
//		ElasticIn,
//		ElasticOut,
//		ElasticInOut,
//		BounceIn,
//		BounceOut,
//		BounceInOut
//	};
//}
//
//class Tween
//{
//public:
//
//	/// <summary>
//	/// シングルトンのインスタンスを取得
//	/// </summary>
//	/// <returns>インスタンス</returns>
//	static Tween& GetInstance();
//
//	void Update();
//
//private:
//
//	/// <summary>
//	/// コンストラクタ
//	/// </summary>
//	Tween();
//
//	// コピー禁止
//	Tween(const Tween&) = delete;
//	// コピー代入禁止
//	Tween& operator=(const Tween&) = delete;
//	// ムーブ禁止		
//	Tween(Tween&&) = delete;
//	// ムーブ代入禁止
//	Tween& operator=(Tween&&) = delete;
//
//	float Easing(Animation::Ease ease, float time);
//
//	std::vector<Animation::Data> mData;
//};