#pragma once

#include <cmath>
#include <DxLib.h>
#include <cassert>

/// <summary>
/// 2次元ベクトルを扱うクラス
/// </summary>
class Vector2
{
public:

	/// <summary>
	/// Xコンポーネント
	/// </summary>
	float x;
	/// <summary>
	/// Yコンポーネント
	/// </summary>
	float y;

	/// <summary>
	/// コンストラクタ
	/// 各コンポーネントを0で初期化する
	/// </summary>
	Vector2() :
		x(0.0f),
		y(0.0f)
	{
	}

	/// <summary>
	/// コンストラクタ
	/// 各コンポーネントを指定した値で初期化する
	/// </summary>
	/// <param name="x">Xコンポーネント</param>
	/// <param name="y">Yコンポーネント</param>
	Vector2(float x, float y) :
		x(x),
		y(y)
	{
	}

	/// <summary>
	/// ベクトル同士の各コンポーネントを加算
	/// </summary>
	/// <param name="a">左</param>
	/// <param name="b">右</param>
	/// <returns>加算結果</returns>
	friend Vector2 operator+(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x + b.x, a.y + b.y);
	}

	/// <summary>
	/// ベクトル同士の各コンポーネントを減算
	/// </summary>
	/// <param name="a">左</param>
	/// <param name="b">右</param>
	/// <returns>減算結果</returns>
	friend Vector2 operator-(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x - b.x, a.y - b.y);
	}

	/// <summary>
	/// ベクトルとスカラーを乗算
	/// </summary>
	/// <param name="v">ベクトル</param>
	/// <param name="s">スカラー</param>
	/// <returns>乗算結果</returns>
	friend Vector2 operator*(const Vector2& v, const float s)
	{
		return Vector2(v.x * s, v.y * s);
	}

	/// <summary>
	/// ベクトルとスカラーを乗算
	/// </summary>
	/// <param name="s">ベクトル</param>
	/// <param name="v">スカラー</param>
	/// <returns>乗算結果</returns>
	friend Vector2 operator*(const float s, const Vector2& v)
	{
		return Vector2(v.x * s, v.y * s);
	}

	/// <summary>
	/// ベクトルをスカラーで除算
	/// </summary>
	/// <param name="v">ベクトル</param>
	/// <param name="s">スカラー</param>
	/// <returns>除算結果</returns>
	friend Vector2 operator/(const Vector2& v, const float s)
	{
		if (s == 0.0f)
		{
			assert(false, "ゼロ除算が発生しました。長さ0のベクトルを返します");
			return Vector2::Zero;
		}

		return Vector2(v.x / s, v.y / s);
	}

	/// <summary>
	/// コピー代入
	/// </summary>
	/// <param name="v">ベクトル</param>
	/// <returns>自身の実体</returns>
	Vector2& operator=(const Vector2& v)
	{
		x = v.x;
		y = v.y;

		return *this;
	}

	/// <summary>
	/// 加算代入
	/// </summary>
	/// <param name="v">ベクトル</param>
	/// <returns>自身の実体</returns>
	Vector2& operator+=(const Vector2& v)
	{
		x += v.x;
		y += v.y;

		return *this;
	}

	/// <summary>
	/// 減算代入
	/// </summary>
	/// <param name="v">ベクトル</param>
	/// <returns>自身の実体</returns>
	Vector2& operator-=(const Vector2& v)
	{
		x -= v.x;
		y -= v.y;

		return *this;
	}

	/// <summary>
	/// 乗算代入
	/// </summary>
	/// <param name="s">スカラー</param>
	/// <returns>自身の実体</returns>
	Vector2& operator*=(const float s)
	{
		x *= s;
		y *= s;

		return *this;
	}

	/// <summary>
	/// 除算代入
	/// </summary>
	/// <param name="s">スカラー</param>
	/// <returns>自身の実体</returns>
	Vector2& operator/=(const float s)
	{
		if (s == 0.0f)
		{
			assert(false, "ゼロ除算が発生しました。値を変更せずに返します");
			return *this;
		}

		x /= s;
		y /= s;

		return *this;
	}

	/// <summary>
	/// 符号を反転させる
	/// </summary>
	/// <returns>自身の実体</returns>
	Vector2& operator-()
	{
		x = -x;
		y = -y;

		return *this;
	}

	/// <summary>
	/// 2つのベクトルが等しいかチェック
	/// </summary>
	/// <param name="v">ベクトル</param>
	/// <returns>各コンポーネント同士が等しいならtrue</returns>
	bool operator==(const Vector2& v)
	{
		return (this->x == v.x && this->y == v.y);
	}

	/// <summary>
	/// 2つのベクトルが等しくないかチェック
	/// </summary>
	/// <param name="v">ベクトル</param>
	/// <returns>各コンポーネント同士が等しくないならtrue</returns>
	bool operator!=(const Vector2& v)
	{
		return (this->x != v.x && this->y != v.y);
	}

	/// <summary>
	/// 2つのベクトルの内積を求める
	/// </summary>
	/// <param name="a">内積するベクトル</param>
	/// <param name="b">内積するベクトル</param>
	/// <returns>内積値</returns>
	static float Dot(const Vector2& a, const Vector2& b)
	{
		return (a.x * b.x) + (a.y * b.y);
	}

	/// <summary>
	/// 2つのベクトルの外積を求める
	/// </summary>
	/// <param name="a">外積するベクトル</param>
	/// <param name="b">外積するベクトル</param>
	/// <returns>外積値</returns>
	static float Cross(const Vector2& a, const Vector2& b)
	{
		return (a.x * b.y) - (a.y * b.x);
	}

	/// <summary>
	/// 2点の距離を求める
	/// </summary>
	/// <param name="a">点1</param>
	/// <param name="b">点2</param>
	/// <returns>2点の距離</returns>
	static float Distance(const Vector2& a, const Vector2& b)
	{
		return Length(a - b);
	}

	/// <summary>
	/// ベクトルの長さを求める
	/// </summary>
	/// <param name="v">長さを求めたいベクトル</param>
	/// <returns>ベクトルの長さ</returns>
	static float Length(const Vector2& v)
	{
		return sqrtf(v.x * v.x + v.y * v.y);
	}

	/// <summary>
	/// ベクトルの長さの2乗を求める
	/// 平方根を求めない分軽い
	/// </summary>
	/// <param name="v">長さを求めたいベクトル</param>
	/// <returns>ベクトルの長さの2乗</returns>
	static float LengthSquare(const Vector2& v)
	{
		return v.x * v.x + v.y * v.y;
	}

	/// <summary>
	/// ベクトルを正規化する
	/// </summary>
	/// <param name="v">正規化したいベクトル</param>
	/// <returns>正規化されたベクトル</returns>
	static Vector2 Normalize(const Vector2& v)
	{
		return v / Length(v);
	}

	/// <summary>
	/// DXライブラリのベクトルに変換する
	/// </summary>
	/// <returns>DXライブラリのベクトル</returns>
	VECTOR ToDxVector()
	{
		return VGet(x, y, 0.0f);
	}

	// 静的定数
	static const Vector2 Zero;
	static const Vector2 One;
};

/// <summary>
/// 3次元ベクトルを扱うクラス
/// </summary>
class Vector3
{
public:

	/// <summary>
	/// Xコンポーネント
	/// </summary>
	float x;
	/// <summary>
	/// Yコンポーネント
	/// </summary>
	float y;
	/// <summary>
	/// Zコンポーネント
	/// </summary>
	float z;

	/// <summary>
	/// コンストラクタ
	/// 各コンポーネントを0で初期化する
	/// </summary>
	Vector3() :
		x(0.0f),
		y(0.0f),
		z(0.0f)
	{
	}

	/// <summary>
	/// コンストラクタ
	/// 各コンポーネントを指定した値で初期化する
	/// </summary>
	/// <param name="x">Xコンポーネント</param>
	/// <param name="y">Yコンポーネント</param>
	/// <param name="z">Zコンポーネント</param>
	Vector3(float x, float y, float z) :
		x(x),
		y(y),
		z(z)
	{
	}

	/// <summary>
	/// ベクトル同士の各コンポーネントを加算
	/// </summary>
	/// <param name="a">左</param>
	/// <param name="b">右</param>
	/// <returns>加算結果</returns>
	friend Vector3 operator+(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
	}

	/// <summary>
	/// ベクトル同士の各コンポーネントを減算
	/// </summary>
	/// <param name="a">左</param>
	/// <param name="b">右</param>
	/// <returns>減算結果</returns>
	friend Vector3 operator-(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	/// <summary>
	/// ベクトル同士の各コンポーネントを乗算
	/// </summary>
	/// <param name="a">左</param>
	/// <param name="b">右</param>
	/// <returns>乗算結果</returns>
	friend Vector3 operator*(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x * b.x, a.y * b.y, a.z * b.z);
	}

	/// <summary>
	/// ベクトルとスカラーを乗算
	/// </summary>
	/// <param name="v">ベクトル</param>
	/// <param name="s">スカラー</param>
	/// <returns>乗算結果</returns>
	friend Vector3 operator*(const Vector3& v, const float& s)
	{
		return Vector3(v.x * s, v.y * s, v.z * s);
	}

	/// <summary>
	/// ベクトルとスカラーを乗算
	/// </summary>
	/// <param name="s">ベクトル</param>
	/// <param name="v">スカラー</param>
	/// <returns>乗算結果</returns>
	friend Vector3 operator*(const float& s, const Vector3& v)
	{
		return Vector3(v.x * s, v.y * s, v.z * s);
	}

	/// <summary>
	/// ベクトルをスカラーで除算
	/// </summary>
	/// <param name="v">ベクトル</param>
	/// <param name="s">スカラー</param>
	/// <returns>除算結果</returns>
	friend Vector3 operator/(const Vector3& v, const float& s)
	{
		if (s == 0.0f)
		{
			assert(false, "ゼロ除算が発生しました。長さ0のベクトルを返します");
			return Vector3::Zero;
		}

		return Vector3(v.x / s, v.y / s, v.z / s);
	}

	/// <summary>
	/// 符号を反転させる
	/// </summary>
	/// <returns>自身の実体</returns>
	Vector3& operator-()
	{
		x = -x;
		y = -y;
		z = -z;

		return *this;
	}

	/// <summary>
	/// コピー代入
	/// </summary>
	/// <param name="v">ベクトル</param>
	/// <returns>自身の実体</returns>
	Vector3& operator=(const Vector3& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;

		return *this;
	}

	/// <summary>
	/// 加算代入
	/// </summary>
	/// <param name="v">ベクトル</param>
	/// <returns>自身の実体</returns>
	Vector3& operator+=(const Vector3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;

		return *this;
	}

	/// <summary>
	/// 減算代入
	/// </summary>
	/// <param name="v">ベクトル</param>
	/// <returns>自身の実体</returns>
	Vector3& operator-=(const Vector3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;

		return *this;
	}

	/// <summary>
	/// 乗算代入
	/// </summary>
	/// <param name="v">ベクトル</param>
	/// <returns>自身の実体</returns>
	Vector3& operator*=(const Vector3& v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;

		return *this;
	}

	/// <summary>
	/// 乗算代入
	/// </summary>
	/// <param name="s">スカラー</param>
	/// <returns>自身の実体</returns>
	Vector3& operator*=(const float& s)
	{
		x *= s;
		y *= s;
		z *= s;

		return *this;
	}

	/// <summary>
	/// 除算代入
	/// </summary>
	/// <param name="s">スカラー</param>
	/// <returns>自身の実体</returns>
	Vector3& operator/=(const float& s)
	{
		if (s == 0.0f)
		{
			assert(false, "ゼロ除算が発生しました。値を変更せずに返します");
			return *this;
		}

		x /= s;
		y /= s;
		z /= s;

		return *this;
	}

	/// <summary>
	/// 2つのベクトルが等しいかチェック
	/// </summary>
	/// <param name="v">ベクトル</param>
	/// <returns>各コンポーネント同士が等しいならtrue</returns>
	bool operator==(const Vector3& v)
	{
		return (this->x == v.x && this->y == v.y && this->z == v.z);
	}

	/// <summary>
	/// 2つのベクトルが等しくないかチェック
	/// </summary>
	/// <param name="v">ベクトル</param>
	/// <returns>各コンポーネント同士が等しくないならtrue</returns>
	bool operator!=(const Vector3& v)
	{
		return (this->x != v.x && this->y != v.y && this->z != v.z);
	}

	/// <summary>
	/// 2つのベクトルの内積を求める
	/// </summary>
	/// <param name="a">内積するベクトル</param>
	/// <param name="b">内積するベクトル</param>
	/// <returns>内積値</returns>
	static float Dot(const Vector3& a, const Vector3& b)
	{
		return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	}

	/// <summary>
	/// 2つのベクトルの外積を求める
	/// </summary>
	/// <param name="a">外積するベクトル</param>
	/// <param name="b">外積するベクトル</param>
	/// <returns>外積値</returns>
	static Vector3 Cross(const Vector3& a, const Vector3& b)
	{
		return Vector3(
			(a.y * b.z) - (a.z * b.y),
			(a.z * b.x) - (a.x * b.z),
			(a.x * b.y) - (a.y * b.x)
		);
	}

	/// <summary>
	/// 2点の距離を求める
	/// </summary>
	/// <param name="a">点1</param>
	/// <param name="b">点2</param>
	/// <returns>2点の距離</returns>
	static float Distance(const Vector3& a, const Vector3& b)
	{
		return Length(a - b);
	}

	/// <summary>
	/// ベクトルの長さを求める
	/// </summary>
	/// <param name="v">長さを求めたいベクトル</param>
	/// <returns>ベクトルの長さ</returns>
	static float Length(const Vector3& v)
	{
		return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	}

	/// <summary>
	/// ベクトルの長さの2乗を求める
	/// 平方根を求めない分軽い
	/// </summary>
	/// <param name="v">長さを求めたいベクトル</param>
	/// <returns>ベクトルの長さの2乗</returns>
	static float LengthSquare(const Vector3& v)
	{
		return v.x * v.x + v.y * v.y + v.z * v.z;
	}

	/// <summary>
	/// ベクトルを正規化する
	/// </summary>
	/// <param name="v">正規化したいベクトル</param>
	/// <returns>正規化されたベクトル</returns>
	static Vector3 Normalize(const Vector3& v)
	{
		return v / Length(v);
	}

	/// <summary>
	/// DXライブラリのベクトルに変換する
	/// </summary>
	/// <returns>DXライブラリのベクトル</returns>
	VECTOR ToDxVector()
	{
		return VGet(x, y, z);
	}

	// 静的定数
	static const Vector3 Zero;
	static const Vector3 One;
};
