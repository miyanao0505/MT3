#include "Quaternion.h"
#include "MyTools.h"
#include "Novice.h"

// Quaternionの積
Quaternion Quaternion::Multiply(const Quaternion& q, const Quaternion& r)
{
	Quaternion ans(0.0f, 0.0f, 0.0f, 0.0f);
	
	float w = q.w * r.w - MyTools::Dot({ q.x, q.y, q.z }, { r.x, r.y, r.z });
	Vector3 result = MyTools::Cross({ q.x, q.y, q.z }, { r.x, r.y, r.z });
	result = MyTools::Add(result, MyTools::Multiply(r.w, { q.x, q.y, q.z }));
	result = MyTools::Add(result, MyTools::Multiply(q.w, { r.x, r.y, r.z }));
	
	ans = { result.x, result.y, result.z, w };

	return ans;
}

// Quaternionの内積
float Quaternion::Dot(const Quaternion& q, const Quaternion& r)
{
	return q.x * r.x + q.y * r.y + q.z * r.z + q.w * r.w;
}

// 単位Quaternionを返す
Quaternion Quaternion::IdentityQuaternion()
{
	return Quaternion{ 0.0f, 0.0f, 0.0f, 1.0f };
}

// 共役Quaternionを返す
Quaternion Quaternion::Conjugate(const Quaternion& quaternion)
{
	return Quaternion{ -quaternion.x, -quaternion.y, -quaternion.z, quaternion.w };
}

// Quaternionのnormを返す
float Quaternion::Norm(const Quaternion& quaternion)
{
	float ans = 0.0f;

	ans = sqrtf(Dot(quaternion, quaternion));

	return ans;
}

// 正規化したQuaternionを返す
Quaternion Quaternion::Normalize(const Quaternion& quaternion)
{
	float norm = Norm(quaternion);
	float x = quaternion.x, y = quaternion.y, z = quaternion.z, w = quaternion.w;
	if (norm != 0) {
		x /= norm;
		y /= norm;
		z /= norm;
		w /= norm;
	}

	return Quaternion{ x, y, z, w };
}

//  逆Quaternionを返す
Quaternion Quaternion::Inverse(const Quaternion& quaternion)
{
	Quaternion identity = IdentityQuaternion();
	Quaternion conjugate = Conjugate(quaternion);
	float normPow2 = powf(Norm(quaternion),2);

	if (quaternion.x == identity.x && quaternion.y == identity.y && quaternion.z == identity.z && quaternion.w == identity.w) {
		return conjugate;
	}

	return { conjugate.x / normPow2, conjugate.y / normPow2, conjugate.z / normPow2, conjugate.w / normPow2 };
}

/// クォータニオンの表示
void Quaternion::QuaternionScreenPrintf(int x, int y, const Quaternion& quaternion, const char* label)
{
	Novice::ScreenPrintf(x, y, "%.02f", quaternion.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", quaternion.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", quaternion.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%.02f", quaternion.w);
	Novice::ScreenPrintf(x + kColumnWidth * 4, y, ": %s", label);
}
