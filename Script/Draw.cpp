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
}

/// 
/// デバッグ用関数 ここまで
/// 

