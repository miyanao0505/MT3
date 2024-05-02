#include "Draw.h"
#include "Novice.h"

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
				0xAAAAAAFF
			);
		}
		else
		{
			Novice::DrawLine(
				int(screenStartPosition.x), int(screenStartPosition.y),
				int(screenEndPosition.x), int(screenEndPosition.y),
				0x000000FF
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

/// 
/// オブジェクト用 ここから
/// 
