#include <Novice.h>
#include "Script/Matrix.h"
#include "Script/MyTools.h"

const char kWindowTitle[] = "LE2A_17_ミヤザワ_ナオキ_MT3_0_2_3次元への拡張(行列)_確認課題";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// 行列
	Matrix::Matrix4x4 matrix1 = {
		3.2f, 0.7f, 9.6f, 4.4f,
		5.5f, 1.3f, 7.8f, 2.1f,
		6.9f, 8.0f, 2.6f, 1.0f,
		0.5f, 7.2f, 5.1f, 3.3f
	};
	Matrix::Matrix4x4 matrix2 = {
		4.1f, 6.5f, 3.3f, 2.2f,
		8.8f, 0.6f, 9.9f, 7.7f,
		1.1f, 5.5f, 6.6f, 0.0f,
		3.3f, 9.9f, 8.8f, 2.2f
	};

	// 結果
	Matrix::Matrix4x4 resultAdd = Matrix::Add(matrix1, matrix2);
	Matrix::Matrix4x4 resultMultiply = Matrix::Multiply(matrix1, matrix2);
	Matrix::Matrix4x4 resultSubtract = Matrix::Subtract(matrix1, matrix2);
	Matrix::Matrix4x4 inverseMatrix1 = Matrix::Inverse(matrix1);
	Matrix::Matrix4x4 inverseMatrix2 = Matrix::Inverse(matrix2);
	Matrix::Matrix4x4 transposeMatrix1 = Matrix::Transpose(matrix1);
	Matrix::Matrix4x4 transposeMatrix2 = Matrix::Transpose(matrix2);
	Matrix::Matrix4x4 identity = Matrix::MakeIdentity4x4();

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// 行列
		Matrix::MatrixScreenPrintf(0, 0, resultAdd, "Add");
		Matrix::MatrixScreenPrintf(0, Matrix::kRowHeight * 5, resultSubtract, "Subtract");
		Matrix::MatrixScreenPrintf(0, Matrix::kRowHeight * 5 * 2, resultMultiply, "Multiply");
		Matrix::MatrixScreenPrintf(0, Matrix::kRowHeight * 5 * 3, inverseMatrix1, "inverseMatrix1");
		Matrix::MatrixScreenPrintf(0, Matrix::kRowHeight * 5 * 4, inverseMatrix2, "inverseMatrix2");
		Matrix::MatrixScreenPrintf(Matrix::kColumnWidth * 5, 0, transposeMatrix1, "transposeMatrix1");
		Matrix::MatrixScreenPrintf(Matrix::kColumnWidth * 5, Matrix::kRowHeight * 5, transposeMatrix2, "transposeMatrix2");
		Matrix::MatrixScreenPrintf(Matrix::kColumnWidth * 5, Matrix::kRowHeight * 5 * 2, identity, "identity");

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}