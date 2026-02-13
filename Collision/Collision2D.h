#pragma once

#include "../Utility/Vector.h"

struct LineSegment
{
	Vector2 start;
	Vector2 end;
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
	/// ü•ª‚Æü•ª‚ÌŒğ“_‚Ìæ“¾
	/// </summary>
	/// <param name="lineA">ü•ª</param>
	/// <param name="lineB"></param>
	/// <returns>ü•ª‚ÌŒğ“_</returns>
	Vector2 GetIntersectPoint(const LineSegment& lineA, const LineSegment& lineB);
}
