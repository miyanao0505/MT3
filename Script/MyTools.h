#pragma once
#include <cmath>
#include "MyBase.h"

class MyTools :
	public MyBase
{
public:

	// メンバ変数
	static const int kColumnWidth = 60;			// 表示文字サイズ_横幅
	static const int kRowHeight = 20;			// 表示文字サイズ_縦幅

	// メンバ関数

	/// 
	/// ツール関数 ここから
	/// 
	
	/// <summary>
	/// 範囲内の値を返す関数
	/// </summary>
	/// <param name="num">確認する値</param>
	/// <param name="min">最低値</param>
	/// <param name="max">最大値</param>
	/// <returns>範囲内の値</returns>
	static float Clamp(const float& num, const float& min, const float& max);

	/// 
	/// ツール関数 ここまで
	///

	/// 
	/// 2次元ベクトル ここから
	///
	
	/// <summary>
	/// 2次元ベクトルの内積を返す関数
	/// </suumary>
	/// <param name="v1">ベクトルA</param>
	/// <param name="v2">ベクトルB</param>
	static float Dot(const Vector2& v1, const Vector2& v2);

	/// <summary>
	/// 2次元ベクトルのクロス積(外積)を返す関数
	/// </summary>
	/// <param name="v1">ベクトルA</param>
	/// <param name="v2">ベクトルB</param>
	static float Cross(const Vector2& v1, const Vector2& v2);

	/// <summary>
	/// 2次元ベクトルの長さ(ノルム)を返す関数
	/// </summary>
	/// <param name="x">ベクトルのX軸の値</param>
	/// <param name="y">ベクトルのY軸の値</param>
	static float Length(float x, float y);

	/// <summary>
	/// 2次元ベクトルの正規化した値を返す関数
	/// </summary>
	/// <param name="x">ベクトルのX軸の値</param>
	/// <param name="y">ベクトルのY軸の値</param>
	static Vector2 Normalize(float x, float y);

	/// <summary>
	/// 2次元ベクトルの方向を求める関数
	/// </summary>
	/// <param name="x">ベクトルのX軸の値</param>
	/// <param name="y">ベクトルのY軸の値</param>
	static Vector2 Direction(float x, float y);

	/// 
	/// 2次元ベクトル ここまで
	///

	/// 
	/// 3次元ベクトル ここから
	/// 
	
	/// <summary>
	/// 3次元ベクトルの加算を返す関数
	/// </summary>
	/// <param name="v1">ベクトルA</param>
	/// <param name="v2">ベクトルB</param>
	static Vector3 Add(const Vector3& v1, const Vector3& v2);

	/// <summary>
	/// 3次元ベクトルの減算を返す関数
	/// </summary>
	/// <param name="v1">ベクトルA</param>
	/// <param name="v2">ベクトルB</param>
	static Vector3 Subtract(const Vector3& v1, const Vector3& v2);

	/// <summary>
	/// 3次元ベクトルのスカラー倍
	/// </summary>
	/// <param name="scalar">スカラー値</param>
	/// <param name="v">ベクトル</param>
	static Vector3 Multiply(float scalar, const Vector3& v);

	/// <summary>
	/// 3次元ベクトルの内積を返す関数
	/// </summary>
	/// <param name="v1">ベクトルA</param>
	/// <param name="v2">ベクトルB</param>
	static float Dot(const Vector3& v1, const Vector3& v2);

	/// <summary>
	/// 3次元ベクトルのクロス積(外積)を返す関数
	/// </summary>
	/// <param name="v1">ベクトルA</param>
	/// <param name="v2">ベクトルB</param>
	static Vector3 Cross(const Vector3& v1, const Vector3& v2);

	/// <summary>
	/// 3次元ベクトル長さ(ノルム)を返す関数
	/// </summary>
	/// <param name="v">ベクトル</param>
	static float Length(const Vector3& v);

	/// <summary>
	/// 3次元ベクトルの正規化した値を返す関数
	/// </summary>
	/// <param name="v">ベクトル</param>
	static Vector3 Normalize(const Vector3& v);

	/// 
	/// 3次元ベクトル ここまで
	/// 

	/// 
	/// 描画 ここから
	/// 
	
	/// <summary>
	/// 2次元ベクトルの表示
	/// </summary>
	/// <param name="x">表示するデバッグ用文字列の左上座標 X</param>
	/// <param name="y">表示するデバッグ用文字列の左上座標 Y</param>
	/// <param name="vector">表示したいベクトルの変数</param>
	/// <param name="label">表示したいベクトルの名前</param>
	static void VectorScreenPrintf(int x, int y, const Vector2& vector, const char* label);

	/// <summary>
	/// 3次元ベクトルの表示
	/// </summary>
	/// <param name="x">表示するデバッグ用文字列の左上座標 X</param>
	/// <param name="y">表示するデバッグ用文字列の左上座標 Y</param>
	/// <param name="vector">表示したいベクトルの変数</param>
	/// <param name="label">表示したいベクトルの名前</param>
	static void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);

	/// 
	/// 描画 ここまで
	/// 
};