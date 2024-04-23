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


};

