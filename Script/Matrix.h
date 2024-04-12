#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <assert.h>
#include "MyBase.h"

class Matrix :
	public MyBase
{
public:
	/// 定数
	static const int kRowHeight = 20;		// 縦：一文字、20
	static const int kColumnWidth = 55;		// 横：一文字、11

	/// 関数
	/// <summary>
	/// 2x2の行列
	/// </summary>
	static Matrix2x2 MakeRotateMatrix2x2(float);						// 回転行列の作成
	static Matrix2x2 Add(Matrix2x2 matrix1, Matrix2x2 matrix2);			// 行列の加法
	static Matrix2x2 Subtract(Matrix2x2 matrix1, Matrix2x2 matrix2);	// 行列の減法
	static Matrix2x2 Multiply(Matrix2x2 matrix1, Matrix2x2 matrix2);	// 行列の積
	static Matrix2x2 Multiply(float scalar, Matrix2x2 matrix);			// スカラーと行列の積
	static Vec2 Multiply(Vec2 vector, Matrix2x2 matrix);				// ベクトルと行列の積
	static Matrix2x2 Inverse(Matrix2x2 matrix);							// 逆行列の取得
	static Matrix2x2 Transpose(Matrix2x2);								// 転置行列の取得

	/// <summary>
	/// 3x3の行列
	/// </summary>
	static Matrix3x3 MakeScaleMatrix(Vec2 scale);									// 拡縮行列の作成
	static Matrix3x3 MakeRotateMatrix(float);										// 回転行列の作成
	static Matrix3x3 MakeTranslateMatrix(Vec2 translate);							// 平行移動行列の作成関数
	static Matrix3x3 MakeAffineMatrix(Vec2 scale, float rotate, Vec2 translate);	// アフィン変換行列の作成
	static Matrix3x3 MakeOrthographicMatrix(float, float, float, float);			// 正射影行列の作成
	static Matrix3x3 MakeViewportMatrix(float, float, float, float);				// ビューポート行列の作成
	static Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2);				// 行列の積
	static Matrix3x3 Multipty(float scalar, Matrix3x3 matrix);						// スカラーと行列の積
	static Vec2 Transform(Vec2 vector, Matrix3x3 matrix);							// 2次元ベクトルを同次座標として変換する
	static Matrix3x3 Inverse(Matrix3x3 matrix);										// 逆行列の取得
	static Matrix3x3 Transpose(Matrix3x3);											// 転置行列の取得

	/// <summary>
	/// 描画
	/// </summary>
	static void VectorScreenPrintf(int, int, Vec2);			// ベクトルの表示
	static void MatrixScreenPrintf(int, int, Matrix2x2);	// 行列の表示
	static void MatrixScreenPrintf(int, int, Matrix3x3);	// 行列の表示

};

