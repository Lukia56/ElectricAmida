#pragma once

#include "../Utility/Vector.h"

struct LineSegment
{
	Vector2 start;
	Vector2 end;
};

struct Rect
{
	float left, top, right, bottom;
};

struct Circle
{
	Vector2 center;
	float radius;
};

namespace Collision
{
	/// <summary>
	/// ü•ª‚Æü•ª‚ÌŒğ·”»’è
	/// </summary>
	/// <param name="lineA">ü•ª</param>
	/// <param name="lineB">ü•ª</param>
	/// <returns>Œğ·‚µ‚Ä‚¢‚½‚çtrue</returns>
	bool IsIntersect(const LineSegment& lineA, const LineSegment& lineB);

	/// <summary>
	/// ‹éŒ`‚Æ‹éŒ`‚ÌŒğ·”»’è
	/// </summary>
	/// <param name="rectA">‹éŒ`</param>
	/// <param name="rectB">‹éŒ`</param>
	/// <returns>Œğ·‚µ‚Ä‚¢‚½‚çtrue</returns>
	bool IsIntersect(const Rect& rectA, const Rect& rectB);

	/// <summary>
	/// ‰~‚Æ‰~‚ÌŒğ·”»’è
	/// </summary>
	/// <param name="circleA">‰~</param>
	/// <param name="circleB">‰~</param>
	/// <returns>Œğ·‚µ‚Ä‚¢‚½‚çtrue</returns>
	bool IsIntersect(const Circle& circleA, const Circle& circleB);

	/// <summary>
	/// ‹éŒ`‚Æ‰~‚ÌŒğ·”»’è
	/// </summary>
	/// <param name="rect">‹éŒ`</param>
	/// <param name="circle">‰~</param>
	/// <returns>Œğ·‚µ‚Ä‚¢‚½‚çtrue</returns>
	bool IsIntersect(const Rect& rect, const Circle& circle);

	/// <summary>
	/// ü•ª‚Æü•ª‚ÌŒğ“_‚Ìæ“¾
	/// </summary>
	/// <param name="lineA">ü•ª</param>
	/// <param name="lineB"></param>
	/// <returns>ü•ª‚ÌŒğ“_</returns>
	Vector2 GetIntersectPoint(const LineSegment& lineA, const LineSegment& lineB);
}
