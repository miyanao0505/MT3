﻿#include "Draw.h"
#include "Novice.h"
#include <vector>

///
/// デバッグ用関数 ここから
/// 

/// <summary>
/// グリッドの表示
/// </summary>
void Draw::DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix)
{
	const float kGridHalfWidth = 2.0f;										// Gridの半分の幅
	const uint32_t kSubdivision = 10;										// 分割数
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision);	// 1つ分の長さ
	// 奥から手前への線を順々に引いていく
	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex)
	{
		// 上の情報を使ってワールド座標系上の始点と終点を求める
		Vector3 worldPositionStart = { -kGridEvery * 5.f, 0.f, kGridEvery * (-5.f + xIndex) };
		Vector3 worldPositionEnd = { kGridEvery * 5.f, 0.f, kGridEvery * (-5.f + xIndex) };
		// スクリーン座標系まで変換をかける
		Matrix4x4 worldMatrixStart = Matrix::MakeAffineMatrix({ 1.f, 1.f, 1.f }, { 0.f, 0.f, 0.f }, worldPositionStart);
		Matrix4x4 worldViewProjectionMatrixStart = Matrix::Multiply(worldMatrixStart, viewProjectionMatrix);
		Vector3 ndcVertexStart = Matrix::Transform({ 0.f, 0.f, 0.f }, worldViewProjectionMatrixStart);
		Vector3 screenStartPosition = Matrix::Transform(ndcVertexStart, viewportMatrix);

		Matrix4x4 worldMatrixEnd = Matrix::MakeAffineMatrix({ 1.f, 1.f, 1.f }, { 0.f, 0.f, 0.f }, worldPositionEnd);
		Matrix4x4 worldViewProjevtionMatrixEnd = Matrix::Multiply(worldMatrixEnd, viewProjectionMatrix);
		Vector3 ndcVertexEnd = Matrix::Transform({ 0.f, 0.f, 0.f }, worldViewProjevtionMatrixEnd);
		Vector3 screenEndPosition = Matrix::Transform(ndcVertexEnd, viewportMatrix);
		// 変換した座標を使って表示。色は薄い灰色(0xAAAAAAFF)、原点は黒ぐらいが良いが、何でも良い
		if (xIndex == kSubdivision / 2)
		{
			Novice::DrawLine(
				int(screenStartPosition.x), int(screenStartPosition.y),
				int(screenEndPosition.x), int(screenEndPosition.y),
				0x000000FF
			);
		}
		else
		{
			Novice::DrawLine(
				int(screenStartPosition.x), int(screenStartPosition.y),
				int(screenEndPosition.x), int(screenEndPosition.y),
				0xAAAAAAFF
			);
		}
	}

	// 左から右も同じように順々に引いていく
	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex)
	{
		// 上の情報を使ってワールド座標系上の始点と終点を求める
		Vector3 worldPositionStart = { kGridEvery * (-5.f + zIndex), 0.f, -kGridEvery * 5.f };
		Vector3 worldPositionEnd = { kGridEvery * (-5.f + zIndex), 0.f, kGridEvery * 5.f };
		// スクリーン座標系まで変換をかける
		Matrix4x4 worldMatrixStart = Matrix::MakeAffineMatrix({ 1.f, 1.f, 1.f }, { 0.f, 0.f, 0.f }, worldPositionStart);
		Matrix4x4 worldViewProjectionMatrixStart = Matrix::Multiply(worldMatrixStart, viewProjectionMatrix);
		Vector3 ndcVertexStart = Matrix::Transform({ 0.f, 0.f, 0.f }, worldViewProjectionMatrixStart);
		Vector3 screenStartPosition = Matrix::Transform(ndcVertexStart, viewportMatrix);

		Matrix4x4 worldMatrixEnd = Matrix::MakeAffineMatrix({ 1.f, 1.f, 1.f }, { 0.f, 0.f, 0.f }, worldPositionEnd);
		Matrix4x4 worldViewProjevtionMatrixEnd = Matrix::Multiply(worldMatrixEnd, viewProjectionMatrix);
		Vector3 ndcVertexEnd = Matrix::Transform({ 0.f, 0.f, 0.f }, worldViewProjevtionMatrixEnd);
		Vector3 screenEndPosition = Matrix::Transform(ndcVertexEnd, viewportMatrix);
		// 変換した座標を使って表示。色は薄い灰色(0xAAAAAAFF)、原点は黒ぐらいが良いが、何でも良い
		if (zIndex == kSubdivision / 2)
		{
			Novice::DrawLine(
				int(screenStartPosition.x), int(screenStartPosition.y),
				int(screenEndPosition.x), int(screenEndPosition.y),
				0x000000FF
			);
		}
		else
		{
			Novice::DrawLine(
				int(screenStartPosition.x), int(screenStartPosition.y),
				int(screenEndPosition.x), int(screenEndPosition.y),
				0xAAAAAAFF
			);
		}
	}
}

/// 
/// デバッグ用関数 ここまで
/// 

/// 
/// オブジェクト用 ここから
/// 

/// 直線の描画
void Draw::DrawLine(const Line& line, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	// Screen座標系まで変換
	Matrix4x4 worldMatrixOrigin = Matrix::MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, line.origin);
	Matrix4x4 worldViewProjectionMatrixOrigin = Matrix::Multiply(worldMatrixOrigin, viewProjectionMatrix);
	Vector3 ndcVectorOrigin = Matrix::Transform({ 0.0f, 0.0f, 0.0f }, worldViewProjectionMatrixOrigin);
	Vector3 screenPositionOrigin = Matrix::Transform(ndcVectorOrigin, viewportMatrix);

	Matrix4x4 worldMatrixEnd = Matrix::MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, MyTools::Add(line.origin, line.diff));
	Matrix4x4 worldViewProjectionMatrixEnd = Matrix::Multiply(worldMatrixEnd, viewProjectionMatrix);
	Vector3 ndcVectorEnd = Matrix::Transform({ 0.0f, 0.0f, 0.0f }, worldViewProjectionMatrixEnd);
	Vector3 screenPositionEnd = Matrix::Transform(ndcVectorEnd, viewportMatrix);

	// 線を描画する
	Novice::DrawLine(int(screenPositionOrigin.x), int(screenPositionOrigin.y), int(screenPositionEnd.x), int(screenPositionEnd.y), color);
}

/// 半直線の描画
void Draw::DrawRay(const Ray& ray, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	// Screen座標系まで変換
	Matrix4x4 worldMatrixOrigin = Matrix::MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, ray.origin);
	Matrix4x4 worldViewProjectionMatrixOrigin = Matrix::Multiply(worldMatrixOrigin, viewProjectionMatrix);
	Vector3 ndcVectorOrigin = Matrix::Transform({ 0.0f, 0.0f, 0.0f }, worldViewProjectionMatrixOrigin);
	Vector3 screenPositionOrigin = Matrix::Transform(ndcVectorOrigin, viewportMatrix);

	Matrix4x4 worldMatrixEnd = Matrix::MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, MyTools::Add(ray.origin, ray.diff));
	Matrix4x4 worldViewProjectionMatrixEnd = Matrix::Multiply(worldMatrixEnd, viewProjectionMatrix);
	Vector3 ndcVectorEnd = Matrix::Transform({ 0.0f, 0.0f, 0.0f }, worldViewProjectionMatrixEnd);
	Vector3 screenPositionEnd = Matrix::Transform(ndcVectorEnd, viewportMatrix);

	// 線を描画する
	Novice::DrawLine(int(screenPositionOrigin.x), int(screenPositionOrigin.y), int(screenPositionEnd.x), int(screenPositionEnd.y), color);
}

/// 線分の描画
void Draw::DrawSegment(const Segment& segment, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	// Screen座標系まで変換
	Matrix4x4 worldMatrixOrigin = Matrix::MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, segment.origin);
	Matrix4x4 worldViewProjectionMatrixOrigin = Matrix::Multiply(worldMatrixOrigin, viewProjectionMatrix);
	Vector3 ndcVectorOrigin = Matrix::Transform({ 0.0f, 0.0f, 0.0f }, worldViewProjectionMatrixOrigin);
	Vector3 screenPositionOrigin = Matrix::Transform(ndcVectorOrigin, viewportMatrix);

	Matrix4x4 worldMatrixEnd = Matrix::MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, MyTools::Add(segment.origin, segment.diff));
	Matrix4x4 worldViewProjectionMatrixEnd = Matrix::Multiply(worldMatrixEnd, viewProjectionMatrix);
	Vector3 ndcVectorEnd = Matrix::Transform({ 0.0f, 0.0f, 0.0f }, worldViewProjectionMatrixEnd);
	Vector3 screenPositionEnd = Matrix::Transform(ndcVectorEnd, viewportMatrix);

	// 線を描画する
	Novice::DrawLine(int(screenPositionOrigin.x), int(screenPositionOrigin.y), int(screenPositionEnd.x), int(screenPositionEnd.y), color);
}

/// 球の描画
void Draw::DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	const uint32_t kSubdivision = 10;							// 分割数
	const float kLonEvery = 2.f * float(M_PI) / kSubdivision;	// 経度分割1つ分の角度
	const float kLatEvery = float(M_PI) / kSubdivision;			// 緯度分割1つ分の角度
	// 緯度の方向に分割 -π/2 ～ π/2
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -float(M_PI) / 2.0f + kLatEvery * latIndex;	// 現在の緯度
		// 経度の方向に分割 0 ～ 2π
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery;					// 現在の経度
			// world座標系でのa, b, cを求める
			Vector3 a, b, c;
			a = MyTools::Add(sphere.center, MyTools::Multiply(sphere.radius, { cos(lat) * cos(lon), sin(lat), cos(lat) * sin(lon) }));
			b = MyTools::Add(sphere.center, MyTools::Multiply(sphere.radius, { cos(lat + kLatEvery) * cos(lon), sin(lat + kLatEvery), cos(lat + kLatEvery) * sin(lon) }));
			c = MyTools::Add(sphere.center, MyTools::Multiply(sphere.radius, { cos(lat) * cos(lon + kLonEvery), sin(lat), cos(lat) * sin(lon + kLonEvery) }));
			// a,b,cをScreen座標系まで変換
			Matrix4x4 worldMatrixA = Matrix::MakeAffineMatrix({ 1.f, 1.f, 1.f }, { 0.f, 0.f, 0.f }, a);
			Matrix4x4 worldViewProjectionMatrixA = Matrix::Multiply(worldMatrixA, viewProjectionMatrix);
			Vector3 ndcVertexA = Matrix::Transform({ 0.f, 0.f, 0.f }, worldViewProjectionMatrixA);
			Vector3 screenPositionA = Matrix::Transform(ndcVertexA, viewportMatrix);

			Matrix4x4 worldMatrixB = Matrix::MakeAffineMatrix({ 1.f, 1.f, 1.f }, { 0.f, 0.f, 0.f }, b);
			Matrix4x4 worldViewProjectionMatrixB = Matrix::Multiply(worldMatrixB, viewProjectionMatrix);
			Vector3 ndcVertexB = Matrix::Transform({ 0.f, 0.f, 0.f }, worldViewProjectionMatrixB);
			Vector3 screenPositionB = Matrix::Transform(ndcVertexB, viewportMatrix);

			Matrix4x4 worldMatrixC = Matrix::MakeAffineMatrix({ 1.f, 1.f, 1.f }, { 0.f, 0.f, 0.f }, c);
			Matrix4x4 worldViewProjectionMatrixC = Matrix::Multiply(worldMatrixC, viewProjectionMatrix);
			Vector3 ndcVertexC = Matrix::Transform({ 0.f, 0.f, 0.f }, worldViewProjectionMatrixC);
			Vector3 screenPositionC = Matrix::Transform(ndcVertexC, viewportMatrix);

			// ab,acで線を引く
			Novice::DrawLine(int(screenPositionA.x), int(screenPositionA.y), int(screenPositionB.x), int(screenPositionB.y), color);
			Novice::DrawLine(int(screenPositionA.x), int(screenPositionA.y), int(screenPositionC.x), int(screenPositionC.y), color);
		}
	}
}

/// 円の描画
void Draw::DrawEllipse(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	Matrix4x4 worldMatrix = Matrix::MakeAffineMatrix({ 1.f, 1.f, 1.f }, { 0.f, 0.f, 0.f }, sphere.center);
	Matrix4x4 worldViewProjectionMatrix = Matrix::Multiply(worldMatrix, viewProjectionMatrix);
	Vector3 ndcVErtex = Matrix::Transform({ 0.f, 0.f, 0.f }, worldViewProjectionMatrix);
	Vector3 screenPosition = Matrix::Transform(ndcVErtex, viewportMatrix);

	// 円の描画
	Novice::DrawEllipse(int(screenPosition.x), int(screenPosition.y), int(sphere.radius), int(sphere.radius), 0.0f, color, kFillModeSolid);
}


/// 平面の描画
void Draw::DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	Vector3 center = MyTools::Multiply(plane.distance, plane.normal);
	Vector3 perpendiculars[4];
	perpendiculars[0] = MyTools::Normalize(MyTools::Perpendicular(plane.normal));
	perpendiculars[1] = { -perpendiculars[0].x, -perpendiculars[0].y, -perpendiculars[0].z };
	perpendiculars[2] = MyTools::Cross(plane.normal, perpendiculars[0]);
	perpendiculars[3] = { -perpendiculars[2].x, -perpendiculars[2].y, -perpendiculars[2].z };

	Vector3 points[4];
	for (int32_t index = 0; index < 4; ++index)
	{
		Vector3 extend = MyTools::Multiply(2.0f, perpendiculars[index]);
		Vector3 point = MyTools::Add(center, extend);
		points[index] = Matrix::Transform(Matrix::Transform(point, viewProjectionMatrix), viewportMatrix);
	}

	Novice::DrawLine(int(points[0].x), int(points[0].y), int(points[2].x), int(points[2].y), color);
	Novice::DrawLine(int(points[1].x), int(points[1].y), int(points[3].x), int(points[3].y), color);
	Novice::DrawLine(int(points[2].x), int(points[2].y), int(points[1].x), int(points[1].y), color);
	Novice::DrawLine(int(points[3].x), int(points[3].y), int(points[0].x), int(points[0].y), color);
}

/// 三角形の描画
void Draw::DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	// screen座標系の3頂点
	Vector3 screenPosition[3];

	// screen座標系まで変換
	for (int32_t i = 0; i < 3; ++i)
	{
		Matrix4x4 worldMatrixOrigin = Matrix::MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, triangle.vertices[i]);
		Matrix4x4 worldViewProjectionMatrixOrigin = Matrix::Multiply(worldMatrixOrigin, viewProjectionMatrix);
		Vector3 ndcVectorOrigin = Matrix::Transform({ 0.0f, 0.0f, 0.0f }, worldViewProjectionMatrixOrigin);
		screenPosition[i] = Matrix::Transform(ndcVectorOrigin, viewportMatrix);
	}

	// 描画
	Novice::DrawTriangle(
		int(screenPosition[0].x), int(screenPosition[0].y),
		int(screenPosition[1].x), int(screenPosition[1].y),
		int(screenPosition[2].x), int(screenPosition[2].y),
		color, kFillModeWireFrame
	);
}

/// AABBの描画
void Draw::DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	// AABBを構成する8頂点を求める
	Vector3 vertex[8] = {
		{ aabb.min.x, aabb.min.y, aabb.min.z },
		{ aabb.min.x, aabb.max.y, aabb.min.z },
		{ aabb.max.x, aabb.max.y, aabb.min.z },
		{ aabb.max.x, aabb.min.y, aabb.min.z },
		{ aabb.min.x, aabb.min.y, aabb.max.z },
		{ aabb.min.x, aabb.max.y, aabb.max.z },
		{ aabb.max.x, aabb.max.y, aabb.max.z },
		{ aabb.max.x, aabb.min.y, aabb.max.z }
	};
	Vector3 screenVertex[8];

	// screen座標系まで変換
	for (int32_t i = 0; i < 8; ++i)
	{
		Matrix4x4 worldMatrix = Matrix::MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, vertex[i]);
		Matrix4x4 worldViewProjectionMatrix = Matrix::Multiply(worldMatrix, viewProjectionMatrix);
		Vector3 ndcVector = Matrix::Transform({ 0.0f, 0.0f, 0.0f }, worldViewProjectionMatrix);
		screenVertex[i] = Matrix::Transform(ndcVector, viewportMatrix);
	}

	// 描画
	// 手前
	Novice::DrawLine(int(screenVertex[0].x), int(screenVertex[0].y), int(screenVertex[1].x), int(screenVertex[1].y), color);
	Novice::DrawLine(int(screenVertex[1].x), int(screenVertex[1].y), int(screenVertex[2].x), int(screenVertex[2].y), color);
	Novice::DrawLine(int(screenVertex[2].x), int(screenVertex[2].y), int(screenVertex[3].x), int(screenVertex[3].y), color);
	Novice::DrawLine(int(screenVertex[3].x), int(screenVertex[3].y), int(screenVertex[0].x), int(screenVertex[0].y), color);
	// 奥
	Novice::DrawLine(int(screenVertex[4].x), int(screenVertex[4].y), int(screenVertex[5].x), int(screenVertex[5].y), color);
	Novice::DrawLine(int(screenVertex[5].x), int(screenVertex[5].y), int(screenVertex[6].x), int(screenVertex[6].y), color);
	Novice::DrawLine(int(screenVertex[6].x), int(screenVertex[6].y), int(screenVertex[7].x), int(screenVertex[7].y), color);
	Novice::DrawLine(int(screenVertex[7].x), int(screenVertex[7].y), int(screenVertex[4].x), int(screenVertex[4].y), color);
	// 横
	Novice::DrawLine(int(screenVertex[0].x), int(screenVertex[0].y), int(screenVertex[4].x), int(screenVertex[4].y), color);
	Novice::DrawLine(int(screenVertex[1].x), int(screenVertex[1].y), int(screenVertex[5].x), int(screenVertex[5].y), color);
	Novice::DrawLine(int(screenVertex[2].x), int(screenVertex[2].y), int(screenVertex[6].x), int(screenVertex[6].y), color);
	Novice::DrawLine(int(screenVertex[3].x), int(screenVertex[3].y), int(screenVertex[7].x), int(screenVertex[7].y), color);
}

/// OBBの描画
void Draw::DrawOBB(const OBB& obb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	// AABBでの各頂点座標(ローカル座標)を求める
	Vector3 vertex[8] =
	{
		{ -obb.size.x, obb.size.y, -obb.size.z },	// 左上前
		{ obb.size.x, obb.size.y, -obb.size.z },	// 右上前
		{ -obb.size.x, -obb.size.y, -obb.size.z },	// 左下前
		{ obb.size.x, -obb.size.y, -obb.size.z },	// 右下前
		{ -obb.size.x, obb.size.y, obb.size.z },	// 左上奥
		{ obb.size.x, obb.size.y, obb.size.z },		// 右上奥
		{ -obb.size.x, -obb.size.y, obb.size.z },	// 左下奥
		{ obb.size.x, -obb.size.y, obb.size.z },	// 右下奥
	};
	Vector3 screenVertex[8];						// スクリーン座標
	Matrix4x4 worldMatrix =
	{
		{
			obb.orientations[0].x, obb.orientations[0].y, obb.orientations[0].z, 0,
			obb.orientations[1].x, obb.orientations[1].y, obb.orientations[1].z, 0,
			obb.orientations[2].x, obb.orientations[2].y, obb.orientations[2].z, 0,
			obb.center.x, obb.center.y, obb.center.z, 1
		}
	};

	// screen座標系まで変換
	for (int32_t i = 0; i < 8; i++)
	{
		Matrix4x4 worldViewProjectionMatrix = Matrix::Multiply(worldMatrix, viewProjectionMatrix);
		Vector3 ndcVector = Matrix::Transform(vertex[i], worldViewProjectionMatrix);
		screenVertex[i] = Matrix::Transform(ndcVector, viewportMatrix);
	}

	// 描画
	// 手前
	Novice::DrawLine(int(screenVertex[0].x), int(screenVertex[0].y), int(screenVertex[1].x), int(screenVertex[1].y), color);	// 上辺
	Novice::DrawLine(int(screenVertex[0].x), int(screenVertex[0].y), int(screenVertex[2].x), int(screenVertex[2].y), color);	// 左辺
	Novice::DrawLine(int(screenVertex[1].x), int(screenVertex[1].y), int(screenVertex[3].x), int(screenVertex[3].y), color);	// 右辺
	Novice::DrawLine(int(screenVertex[2].x), int(screenVertex[2].y), int(screenVertex[3].x), int(screenVertex[3].y), color);	// 下辺
	// 奥
	Novice::DrawLine(int(screenVertex[4].x), int(screenVertex[4].y), int(screenVertex[5].x), int(screenVertex[5].y), color);	// 上辺
	Novice::DrawLine(int(screenVertex[4].x), int(screenVertex[4].y), int(screenVertex[6].x), int(screenVertex[6].y), color);	// 左辺
	Novice::DrawLine(int(screenVertex[5].x), int(screenVertex[5].y), int(screenVertex[7].x), int(screenVertex[7].y), color);	// 右辺
	Novice::DrawLine(int(screenVertex[6].x), int(screenVertex[6].y), int(screenVertex[7].x), int(screenVertex[7].y), color);	// 下辺
	// 横
	Novice::DrawLine(int(screenVertex[0].x), int(screenVertex[0].y), int(screenVertex[4].x), int(screenVertex[4].y), color);	// 左上
	Novice::DrawLine(int(screenVertex[1].x), int(screenVertex[1].y), int(screenVertex[5].x), int(screenVertex[5].y), color);	// 右上
	Novice::DrawLine(int(screenVertex[2].x), int(screenVertex[2].y), int(screenVertex[6].x), int(screenVertex[6].y), color);	// 左下
	Novice::DrawLine(int(screenVertex[3].x), int(screenVertex[3].y), int(screenVertex[7].x), int(screenVertex[7].y), color);	// 右下
}

/// ベジェ曲線の描画
void Draw::DrawBezier(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	float t = 0.0f;
	const uint32_t kSubdivision = 100;
	Vector3 drawPoints[(kSubdivision + 1)];

	// 
	for (uint32_t i = 0; i < kSubdivision + 1; i++)
	{
		// 制御点p0, p1を線形補間
		Vector3 r0r1 = MyTools::Lerp(controlPoint0, controlPoint1, t);
		// 制御点p1, p2を線形補間
		Vector3 r1r2 = MyTools::Lerp(controlPoint1, controlPoint2, t);
		// 補間店r0r1, r1r2をさらに線形補間
		Vector3 p = MyTools::Lerp(r0r1, r1r2, t);

		// 描画用配列にセット
		drawPoints[i] = p;

		// 媒介変数の更新
		t = float(i) / float(kSubdivision);
	}

	// 描画！
	// 線
	for (uint32_t i = 0; i < kSubdivision; i++)
	{
		Draw::DrawSegment(Segment{ .origin = drawPoints[i], .diff = MyTools::Subtract(drawPoints[i + 1], drawPoints[i]) }, viewProjectionMatrix, viewportMatrix, color);
	}
	color;
	// コントロールポイント
	Draw::DrawSphere(Sphere{ .center = controlPoint0, .radius = 0.01f }, viewProjectionMatrix, viewportMatrix, 0x000000FF);
	Draw::DrawSphere(Sphere{ .center = controlPoint1, .radius = 0.01f }, viewProjectionMatrix, viewportMatrix, 0x000000FF);
	Draw::DrawSphere(Sphere{ .center = controlPoint2, .radius = 0.01f }, viewProjectionMatrix, viewportMatrix, 0x000000FF);
}

/// Catmull-rom曲線の描画
void Draw::DrawCatmullRom(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2, const Vector3& controlPoint3, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	const size_t kSubdivision = 400;
	std::vector<Vector3> drawPoints;

	std::vector<Vector3> controlPoints = {
		controlPoint0, controlPoint1, controlPoint2, controlPoint3
	};

	for (size_t i = 0; i < kSubdivision + 1; i++)
	{
		float t = 1.0f / kSubdivision * i;

		// 座標計算
		Vector3 pos = MyTools::CatmullRomPosition(controlPoints, t);

		// 描画用リストにセット
		drawPoints.push_back(pos);
	}

	// 描画！
	// 線
	// 線
	for (size_t i = 0; i < drawPoints.size() - 1; i++)
	{
		Draw::DrawSegment(Segment{ .origin = drawPoints.at(i), .diff = MyTools::Subtract(drawPoints.at(i + 1), drawPoints.at(i))}, viewProjectionMatrix, viewportMatrix, color);
	}
	// コントロールポイント
	Draw::DrawSphere(Sphere{ .center = controlPoint0, .radius = 0.01f }, viewProjectionMatrix, viewportMatrix, 0x000000FF);
	Draw::DrawSphere(Sphere{ .center = controlPoint1, .radius = 0.01f }, viewProjectionMatrix, viewportMatrix, 0x000000FF);
	Draw::DrawSphere(Sphere{ .center = controlPoint2, .radius = 0.01f }, viewProjectionMatrix, viewportMatrix, 0x000000FF);
	Draw::DrawSphere(Sphere{ .center = controlPoint3, .radius = 0.01f }, viewProjectionMatrix, viewportMatrix, 0x000000FF);
}

/// 
/// オブジェクト用 ここから
/// 
