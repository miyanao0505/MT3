#pragma once
#include "MyTools.h"
#include "Matrix.h"

class Draw :
	public MyBase
{
public:

	/// 
	/// デバッグ用 ここから
	/// 

	/// <summary>
	/// グリッドの表示
	/// </summary>
	/// <param name="viewProjectionMatrix">ビュープロジェクション行列</param>
	/// <param name="viewportMatrix">ビューポート行列</param>
	static void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);

	/// 
	/// デバッグ用 ここまで
	/// 

	/// 
	/// オブジェクト用 ここから
	/// 
	
	/// <summary>
	/// 球の描画
	/// </summary>
	/// <param name="sphere">球の情報</param>
	/// <param name="viewProjectionMatrix">ビュープロジェクション行列</param>
	/// <param name="viewportMatrix">ビューポート行列</param>
	/// <param name="color">色</param>
	static void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

	/// <summary>
	/// 平面の描画
	/// </summary>
	/// <param name="plane">平面の情報</param>
	/// <param name="viewProjectionMatrix">ビュープロジェクション行列</param>
	/// <param name="viewportMatrix">ビューポート行列</param>
	/// <param name="color">色</param>
	static void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

	/// 
	/// オブジェクト用 ここから
	/// 

};

