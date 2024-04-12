#include "Matrix.h"
#include <Novice.h>

///
/// 2x2行列関数ここから
/// 

// 回転行列の作成関数
Matrix::Matrix2x2 Matrix::MakeRotateMatrix2x2(float theta)
{
	Matrix2x2 ans = { 0 };

	ans.m[0][0] = cosf(theta);
	ans.m[0][1] = sinf(theta);
	ans.m[1][0] = sinf(theta) * -1.f;
	ans.m[1][1] = cosf(theta);

	return ans;
}

// 行列の加法
Matrix::Matrix2x2 Matrix::Add(Matrix2x2 matrix1, Matrix2x2 matrix2)
{
	Matrix2x2 ans = { 0 };

	for (int i = 0; i < 2; i++)
	{
		for (int k = 0; k < 2; k++)
		{
			ans.m[i][k] = matrix1.m[i][k] + matrix2.m[i][k];
		}
	}

	return ans;
}

// 行列の減法
Matrix::Matrix2x2 Matrix::Subtract(Matrix2x2 matrix1, Matrix2x2 matrix2)
{
	Matrix2x2 ans = { 0 };

	for (int i = 0; i < 2; i++)
	{
		for (int k = 0; k < 2; k++)
		{
			ans.m[i][k] = matrix1.m[i][k] - matrix2.m[i][k];
		}
	}

	return ans;
}

// 行列の積
Matrix::Matrix2x2 Matrix::Multiply(Matrix2x2 matrix1, Matrix2x2 matrix2)
{
	Matrix2x2 ans = { 0 };

	ans.m[0][0] = matrix1.m[0][0] * matrix2.m[0][0] + matrix1.m[0][1] * matrix2.m[1][0];
	ans.m[0][1] = matrix1.m[0][0] * matrix2.m[0][1] + matrix1.m[0][1] * matrix2.m[1][1];
	ans.m[1][0] = matrix1.m[1][0] * matrix2.m[0][0] + matrix1.m[1][1] * matrix2.m[1][0];
	ans.m[1][1] = matrix1.m[1][0] * matrix2.m[0][1] + matrix1.m[1][1] * matrix2.m[1][1];

	return ans;
}

// スカラーと行列の積
Matrix::Matrix2x2 Matrix::Multiply(float scalar, Matrix2x2 matrix)
{
	Matrix2x2 ans = { 0 };

	for (int i = 0; i < 2; i++)
	{
		for (int k = 0; k < 2; k++)
		{
			ans.m[i][k] = scalar * matrix.m[i][k];
		}
	}

	return ans;
}

// ベクトルと行列の積
Matrix::Vec2 Matrix::Multiply(Vec2 vector, Matrix2x2 matrix)
{
	Vec2 ans;

	ans.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0];
	ans.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1];

	return ans;
}

// 逆行列の取得
Matrix::Matrix2x2 Matrix::Inverse(Matrix2x2 matrix)
{
	Matrix2x2 ans = { 0 };

	if (matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0] == 0)
	{
		ans = matrix;
	}
	else
	{
		float scalar = 1 / (matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0]);

		ans.m[0][0] = matrix.m[1][1];
		ans.m[0][1] = matrix.m[0][1] * -1.f;
		ans.m[1][0] = matrix.m[1][0] * -1.f;
		ans.m[1][1] = matrix.m[0][0];

		ans = Multiply(scalar, ans);
	}

	return ans;
}

// 転置行列の取得
Matrix::Matrix2x2 Matrix::Transpose(Matrix2x2 matrix)
{
	Matrix2x2 ans = { 0 };

	for (int i = 0; i < 2; i++)
	{
		for (int k = 0; k < 2; k++)
		{
			ans.m[k][i] = matrix.m[i][k];
		}
	}

	return ans;
}

///
/// 2x2行列関数ここまで
/// 

/// 
/// 3x3行列関数ここから
/// 

// 拡縮行列の作成
Matrix::Matrix3x3 Matrix::MakeScaleMatrix(Vec2 scale)
{
	Matrix3x3 ans = { 0 };

	ans.m[0][0] = scale.x;
	ans.m[1][1] = scale.y;
	ans.m[2][2] = 1;

	return ans;
}

// 回転行列の作成
Matrix::Matrix3x3 Matrix::MakeRotateMatrix(float theta)
{
	Matrix3x3 ans = { 0 };

	ans.m[0][0] = cosf(theta);
	ans.m[0][1] = sinf(theta);
	ans.m[1][0] = sinf(theta) * -1.f;
	ans.m[1][1] = cosf(theta);
	ans.m[2][2] = 1;

	return ans;
}

// 平行移動行列の作成関数
Matrix::Matrix3x3 Matrix::MakeTranslateMatrix(Vec2 translate)
{
	Matrix3x3 ans = { 0 };

	ans.m[0][0] = 1;
	ans.m[1][1] = 1;
	ans.m[2][2] = 1;

	ans.m[2][0] = translate.x;
	ans.m[2][1] = translate.y;

	return ans;
}

// アフィン変換行列の作成
Matrix::Matrix3x3 Matrix::MakeAffineMatrix(Vec2 scale, float rotate, Vec2 translate)
{
	Matrix3x3 scaleMatrix = { 0 };
	Matrix3x3 rotateMatrix = { 0 };
	Matrix3x3 translateMatrix = { 0 };
	Matrix3x3 worldMatrix = { 0 };

	// 拡縮行列を作成
	scaleMatrix = MakeScaleMatrix(scale);

	// 回転行列を作成
	rotateMatrix = MakeRotateMatrix(rotate);

	// 平行移動行列を作成
	translateMatrix = MakeTranslateMatrix(translate);

	// 結合
	worldMatrix = Multiply(scaleMatrix, rotateMatrix);
	worldMatrix = Multiply(worldMatrix, translateMatrix);

	return worldMatrix;
}

// 正射影行列の作成
Matrix::Matrix3x3 Matrix::MakeOrthographicMatrix(float left, float top, float right, float bottom)
{
	Matrix3x3 ans = { 0 };

	ans.m[0][0] = 2.f / (right - left);
	ans.m[1][1] = 2.f / (top - bottom);
	ans.m[2][0] = (left + right) / (left - right);
	ans.m[2][1] = (top + bottom) / (bottom - top);
	ans.m[2][2] = 1;

	return ans;
}

// ビューポート行列の作成
Matrix::Matrix3x3 Matrix::MakeViewportMatrix(float left, float top, float width, float height)
{
	Matrix3x3 ans = { 0 };

	ans.m[0][0] = width / 2;
	ans.m[1][1] = height / 2 * -1.f;
	ans.m[2][0] = left + width / 2;
	ans.m[2][1] = top + height / 2;
	ans.m[2][2] = 1;

	return ans;
}

// 行列の積
Matrix::Matrix3x3 Matrix::Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2)
{
	Matrix3x3 ans = { 0 };

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				ans.m[i][j] += matrix1.m[i][k] * matrix2.m[k][j];
			}
		}
	}

	return ans;
}

// スカラーと行列の積
Matrix::Matrix3x3 Matrix::Multipty(float scalar, Matrix3x3 matrix)
{
	Matrix3x3 ans;

	for (int i = 0; i < 3; i++)
	{
		for (int k = 0; k < 3; k++)
		{
			ans.m[i][k] = scalar * matrix.m[i][k];
		}
	}

	return ans;
}

// 2次元ベクトルを同次座標として変換する関数
Matrix::Vec2 Matrix::Transform(Vec2 vector, Matrix3x3 matrix)
{
	Vec2 result;

	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + 1.f * matrix.m[2][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + 1.f * matrix.m[2][1];
	float w = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + 1.f * matrix.m[2][2];

	assert(w != 0.0f);

	result.x /= w;
	result.y /= w;

	return result;
}

// 逆行列の取得
Matrix::Matrix3x3 Matrix::Inverse(Matrix3x3 matrix)
{
	Matrix3x3 ans;

	if (matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2] + matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0] + matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1] - matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0] - matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2] - matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1] == 0)
	{
		ans = matrix;
	}
	else
	{
		float scalar = 1 / (matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2] + matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0] + matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1] - matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0] - matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2] - matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1]);

		ans.m[0][0] = matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1];
		ans.m[0][1] = -(matrix.m[0][1] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][1]);
		ans.m[0][2] = matrix.m[0][1] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][1];
		ans.m[1][0] = -(matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][0]);
		ans.m[1][1] = matrix.m[0][0] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][0];
		ans.m[1][2] = -(matrix.m[0][0] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][0]);
		ans.m[2][0] = matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0];
		ans.m[2][1] = -(matrix.m[0][0] * matrix.m[2][1] - matrix.m[0][1] * matrix.m[2][0]);
		ans.m[2][2] = matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0];

		ans = Multipty(scalar, ans);
	}

	return ans;
}

// 転置行列の取得
Matrix::Matrix3x3 Matrix::Transpose(Matrix3x3 matrix)
{
	Matrix3x3 ans;

	for (int i = 0; i < 3; i++)
	{
		for (int k = 0; k < 3; k++)
		{
			ans.m[k][i] = matrix.m[i][k];
		}
	}

	return ans;
}


///
/// 3x3行列関数ここまで
/// 

///
/// 描画関数ここから
/// 

// ベクトルの表示
void Matrix::VectorScreenPrintf(int x, int y, Vec2 vector)
{
	Novice::ScreenPrintf(x, y, "%4.2f", vector.x);
	Novice::ScreenPrintf(x + 44, y, "%4.2f", vector.y);
}

// 行列の表示
void Matrix::MatrixScreenPrintf(int x, int y, Matrix2x2 matrix)
{
	for (int row = 0; row < 2; ++row)
	{
		for (int column = 0; column < 2; ++column)
		{
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight, "%.02f", matrix.m[row][column]);
		}
	}
}

// 行列の表示
void Matrix::MatrixScreenPrintf(int x, int y, Matrix3x3 matrix)
{
	for (int row = 0; row < 3; ++row)
	{
		for (int column = 0; column < 3; ++column)
		{
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight, "%5.02f", matrix.m[row][column]);
		}
	}
}

///
/// 描画関数ここまで
/// 
