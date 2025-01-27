#pragma once
#include "Matrix.h"

// クォータニオン
class Quaternion
{
public:	// メンバ変数
	static const int kColumnWidth = 70;			// 表示文字サイズ_横幅
	static const int kRowHeight = 20;			// 表示文字サイズ_縦幅

public:	// メンバ変数
	float x, y, z, w;

public:	// メンバ関数
	// コンストラクタ
	Quaternion() : w(1.0f), x(0.0f), y(0.0f), z(0.0f) {}
	Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

	/// 複合代入演算子
	Quaternion& operator*=(float s) { x *= s; y *= s; z *= s; w *= s; return *this; }
	Quaternion& operator-=(const Quaternion& q) { x -= q.x; y -= q.y; z -= q.z; w -= q.w; return *this; }
	Quaternion& operator+=(const Quaternion& q) { x += q.x; y += q.y; z += q.z; w += q.w; return *this; }
	Quaternion& operator/=(float s) { x /= s; y /= s; z /= s; w /= s; return *this; }

	// Quaternionの和
	static Quaternion Add(const Quaternion& q, const Quaternion& r);
	// Quaternionの差
	static Quaternion Subtract(const Quaternion& q, const Quaternion& r);
	// Quaternionの積
	static Quaternion Multiply(const float s, const Quaternion& q);
	// Quaternionの積
	static Quaternion Multiply(const Quaternion& q, const Quaternion& r);
	// Quaternionの内積
	static float Dot(const Quaternion& q, const Quaternion& r);
	// 単位Quaternionを返す
	static Quaternion IdentityQuaternion();
	// 共役Quaternionを返す
	static Quaternion Conjugate(const Quaternion& quaternion);
	// Quaternionのnormを返す
	static float Norm(const Quaternion& quaternion);
	// 正規化したQuaternionを返す
	static Quaternion Normalize(const Quaternion& quaternion);
	//  逆Quaternionを返す
	static Quaternion Inverse(const Quaternion& quaternion);
	// 任意軸回転を表すQuaternionの生成
	static Quaternion MakeRotateAxisAngleQuaternion(const Vector3& axis, float angle);
	// ベクトルをQuaternionで回転させた結果のベクトルを求める
	static Vector3 RotateVector(const Vector3& vector, const Quaternion& quaternion);
	// Quaternionから回転行列を求める
	static Matrix::Matrix4x4 MakeRotateMatrix(const Quaternion& quaternion);
	// 球面線形補間
	static Quaternion Slerp(const Quaternion& q0, const Quaternion& q1, float t);

	/// <summary>
	/// クォータニオンの表示
	/// </summary>
	/// <param name="x">表示するデバッグ用文字列の左上座標 X</param>
	/// <param name="y">表示するデバッグ用文字列の左上座標 Y</param>
	/// <param name="vector">表示したいクォータニオンの変数</param>
	/// <param name="label">表示したいクォータニオンの名前</param>
	static void QuaternionScreenPrintf(int x, int y, const Quaternion& quaternion, const char* label);

};

