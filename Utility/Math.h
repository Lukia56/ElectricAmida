#pragma once

#include <limits>
#include <algorithm>

/// <summary>
/// 数学系計算を行う名前空間
/// </summary>
namespace Math
{
	/// <summary>
	/// 円周率
	/// </summary>
	constexpr float kPi = 3.14159265359f;
	/// <summary>
	/// 円周率の2倍
	/// </summary>
	constexpr float kTwoPi = kPi * 2.0f;

	/// <summary>
	/// ラジアン角に変換
	/// </summary>
	/// <param name="degree">変換したいデグリー角</param>
	/// <returns>ラジアン角</returns>
	inline float ToRadian(float degree)
	{
		return degree * kPi / 180.0f;
	}

	/// <summary>
	/// デグリー角に変換
	/// </summary>
	/// <param name="radian">変換したいラジアン角</param>
	/// <returns>デグリー角</returns>
	inline float ToDegree(float radian)
	{
		return radian * 180.0f / kPi;
	}

	/// <summary>
	/// 2つの値を比べて大きい方を取得する
	/// </summary>
	/// <param name="a">値1</param>
	/// <param name="b">値2</param>
	/// <returns>大きい方の値</returns>
	template<typename T>
	inline T Max(const T& a, const T& b)
	{
		return (a > b ? a : b);
	}

	/// <summary>
	/// 2つの値を比べて小さい方を取得する
	/// </summary>
	/// <param name="a">値1</param>
	/// <param name="b">値2</param>
	/// <returns>小さい方の値</returns>
	template<typename T>
	inline T Min(const T& a, const T& b)
	{
		return (a < b ? a : b);
	}

	/// <summary>
	/// 値を範囲内に収める
	/// </summary>
	/// <param name="value">収めたい値</param>
	/// <param name="min">最小値</param>
	/// <param name="max">最大値</param>
	/// <returns>範囲内に収めた値</returns>
	template<typename T>
	inline T Clamp(const T& value, const T& min, const T& max)
	{
		return Min(max, Max(min, value));
	}

	/// <summary>
	/// 値を線形補間させる
	/// </summary>
	/// <param name="src">開始値</param>
	/// <param name="dst">最終値</param>
	/// <param name="time">補完量</param>
	/// <returns>補完した値を返す</returns>
	inline float Lerp(float src, float dst, float time)
	{
		return src + (dst - src) * time;
	}

	/// <summary>
	/// 値を等速補間させる
	/// </summary>
	/// <param name="src">開始値</param>
	/// <param name="dst">最終値</param>
	/// <param name="amount">変化量</param>
	/// <returns>補完した値を返す</returns>
	template<typename T>
	inline float Approach(const T& src, const T& dst, const T& amount)
	{
		if (src > dst)
		{
			return Max(dst, src - amount);
		}
		else
		{
			return Min(dst, src + amount);
		}
	}
}
