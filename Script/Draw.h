#pragma once
#include "MyTools.h"
#include "Matrix.h"

class Draw :
	public MyBase
{
public:

	/// <summary>
	/// デバッグ用
	/// </summary>
	/// グリッド描画
	static void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);




};

