#include "Collision2D.h"
#include "../Utility/Vector.h"

bool Collision::IsIntersect(const LineSegment& lineA, const LineSegment& lineB)
{
	Vector2 ab = lineA.end - lineA.start;
	Vector2 cd = lineB.end - lineB.start;
	Vector2 ac = lineB.start - lineA.start;
	Vector2 ad = lineB.end - lineA.start;
	Vector2 ca = lineA.start - lineB.start;
	Vector2 cb = lineA.end - lineB.start;

	// •„†‚ª•‰‚Å‚Í‚È‚¢‚È‚çŒğ·‚µ‚Ä‚¢‚È‚¢
	if (Vector2::Cross(ac, ab) * Vector2::Cross(ad, ab) > 0)
	{
		return false;
	}
	// •„†‚ª•‰‚Å‚Í‚È‚¢‚È‚çŒğ·‚µ‚Ä‚¢‚È‚¢
	if (Vector2::Cross(ca, cd) * Vector2::Cross(cb, cd) > 0)
	{
		return false;
	}

	// —¼•û•‰‚Ì‚½‚ßAŒğ·‚µ‚Ä‚¢‚é
	return true;
}

Vector2 Collision::GetIntersectPoint(const LineSegment& lineA, const LineSegment& lineB)
{
	Vector2 a = lineA.start;
	Vector2 b = lineA.end;
	Vector2 c = lineB.start;
	Vector2 d = lineB.end;

	float deno = Vector2::Cross(b - a, d - c);

	if (deno == 0.0f)
	{
		return Vector2(INFINITE, INFINITE);
	}

	float s = Vector2::Cross(c - a, d - c) / deno;
	float t = Vector2::Cross(b - a, a - c) / deno;

	if (s < 0.0 || 1.0 < s || t < 0.0 || 1.0 < t)
	{
		return Vector2(INFINITE, INFINITE);
	}

	return Vector2(a.x + s * (b - a).x, a.y + s * (b - a).y);
}
