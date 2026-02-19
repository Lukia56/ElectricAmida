#include "Collision2D.h"
#include <cmath>
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

bool Collision::IsIntersect(const Rect& rectA, const Rect& rectB)
{
	// A‚Ì¶‚Ì•Ó‚ªB‚Ì‰E‚Ì•Ó‚æ‚è‰E‚É‚ ‚Á‚½‚çŒğ·‚µ‚Ä‚¢‚È‚¢
	if (rectA.left > rectB.right) return false;
	// A‚Ìã‚Ì•Ó‚ªB‚Ì‰º‚Ì•Ó‚æ‚è‰º‚É‚ ‚Á‚½‚çŒğ·‚µ‚Ä‚¢‚È‚¢
	if (rectA.top > rectB.bottom) return false;
	// A‚Ì‰E‚Ì•Ó‚ªB‚Ì¶‚Ì•Ó‚æ‚è¶‚É‚ ‚Á‚½‚çŒğ·‚µ‚Ä‚¢‚È‚¢
	if (rectA.right < rectB.left) return false;
	// A‚Ì‰º‚Ì•Ó‚ªB‚Ìã‚Ì•Ó‚æ‚èã‚É‚ ‚Á‚½‚çŒğ·‚µ‚Ä‚¢‚È‚¢
	if (rectA.bottom < rectB.top) return false;

	// ‚±‚±‚Ü‚ÅğŒ‚ğ–‚½‚³‚È‚©‚Á‚½‚çŒğ·‚µ‚Ä‚¢‚é
	return true;
}

bool Collision::IsIntersect(const Circle& circleA, const Circle& circleB)
{
	// ‰~‚ÌŠÔ‚Ì‹——£‚ğŒvZ
	Vector2 vect = circleA.center - circleB.center;
	float distSq = Vector2::LengthSquare(vect);

	// 2‚Â‚Ì‰~‚Ì”¼Œa‚Ì‡Œv‚ğŒvZ
	float rad = circleA.radius + circleB.radius;
	// ‹——£‚ª2æ‚³‚ê‚Ä‚¢‚é‚½‚ß”¼Œa‚à2æ‚·‚é
	float radSq = rad * rad;

	// ”¼Œa‚Ì‡Œv‚æ‚è‹——£‚ª’·‚©‚Á‚½‚çŒğ·‚µ‚Ä‚¢‚È‚¢
	if (distSq > radSq) return false;

	// ‚±‚±‚Ü‚ÅğŒ‚ğ–‚½‚³‚È‚©‚Á‚½‚çŒğ·‚µ‚Ä‚¢‚é
	return true;
}

bool Collision::IsIntersect(const Rect& rect, const Circle& circle)
{
	// 2‚Â‚Ì‰~‚Ì”¼Œa‚Ì‡Œv‚ğŒvZ
	float rad = circle.radius + circle.radius;
	// ‹——£‚ª2æ‚³‚ê‚Ä‚¢‚é‚½‚ß”¼Œa‚à2æ‚·‚é
	float radSq = rad * rad;

	Vector2 pos;

	pos = Vector2(rect.left, rect.top);
	if (circle.center.x < pos.x - circle.radius) return false;
	pos = Vector2(rect.left, rect.bottom);
	if (circle.center.x > pos.x + circle.radius) return false;
	pos = Vector2(rect.right, rect.top);
	if (circle.center.y < pos.y - circle.radius) return false;
	pos = Vector2(rect.right, rect.bottom);
	if (circle.center.y > pos.y + circle.radius) return false;

	pos = Vector2(rect.left, rect.top);
	if (Vector2::LengthSquare(pos - circle.center) < radSq) return true;
	pos = Vector2(rect.left, rect.bottom);
	if (Vector2::LengthSquare(pos - circle.center) < radSq) return true;
	pos = Vector2(rect.right, rect.top);
	if (Vector2::LengthSquare(pos - circle.center) < radSq) return true;
	pos = Vector2(rect.right, rect.bottom);
	if (Vector2::LengthSquare(pos - circle.center) < radSq) return true;

	return false;
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
