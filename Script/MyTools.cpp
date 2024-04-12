#include "MyTools.h"
#include "Novice.h"

///
/// 2次元ベクトル ここから
///
/// <summary>
/// 長さ(ノルム)関数
/// </summary>
float MyTools::Length(float x, float y)
{
	return sqrtf(x * x + y * y);
}

/// <summary>
/// 正規化関数
/// </summary>
MyTools::Vec2 MyTools::Normalize(float x, float y)
{
	float length = Length(x, y);
	if (length != 0) {
		x = x / length;
		y = y / length;
	}
	return Vector2{ x,y };
}

/// <summary>
/// 方向を求める関数
/// </summary>
MyTools::Vec2 MyTools::Direction(float x, float y)
{
	return Normalize(x, y);
}

///
/// 2次元ベクトル ここまで
/// 

///
/// 3次元ベクトル ここから
/// 

/// <summary>
/// 加算
/// </summary>
MyTools::Vec3 MyTools::Add(const Vec3& v1, const Vec3& v2)
{
	return Vec3{ v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}

/// <summary>
/// 減算
/// </summary>
MyTools::Vec3 MyTools::Subtract(const Vec3& v1, const Vec3& v2)
{
	return Vec3{ v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}

/// <summary>
/// スカラー倍
/// </summary>
MyTools::Vec3 MyTools::Multiply(float scalar, const Vec3& v)
{
	return Vec3{ scalar * v.x, scalar * v.y, scalar * v.z };
}

/// <summary>
/// 内積
/// </summary>
float MyTools::Dot(const Vec3& v1, const Vec3& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

/// <summary>
/// 長さ(ノルム)
/// </summary>
float MyTools::Length(const Vec3& v)
{
	return sqrtf(Dot(v, v));
}

/// <summary>
/// 正規化
/// </summary>
MyTools::Vec3 MyTools::Normalize(const Vec3& v)
{
	float length = Length(v);
	float x = v.x, y = v.y, z = v.z;
	if (length != 0)
	{
		x /= length;
		y /= length;
		z /= length;
	}

	return Vec3{ x, y, z };
}

/// 
/// 3次元ベクトル ここまで
/// 

///
/// 描画関数 ここから
/// 

/// <summary>
/// 2次元ベクトルの表示
/// </summary>
void MyTools::VectorScreenPrintf(int x, int y, const Vec2& vector, const char* label)
{
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%s", label);
}

/// <summary>
/// 3次元ベクトルの表示
/// </summary>
void MyTools::VectorScreenPrintf(int x, int y, const Vec3& vector, const char* label)
{
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}

/// 
/// 描画関数 ここまで
/// 

