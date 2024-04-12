#include <Novice.h>
#include "Script/Matrix.h"
#include "Script/MyTools.h"

const char kWindowTitle[] = "LE2A_17_ミヤザワ_ナオキ_MT3_0_4_3次元での回転_確認課題";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// 3次元ベクトル
	MyBase::Vec3 rotate = { 0.4f, 1.43f, -0.8f };

	// 結果
	MyBase::Matrix4x4 rotateXMatrix = Matrix::MakeRotateXMatrix4x4(rotate.x);
	MyBase::Matrix4x4 rotateYMatrix = Matrix::MakeRotateYMatrix4x4(rotate.y);
	MyBase::Matrix4x4 rotateZMatrix = Matrix::MakeRotateZMatrix4x4(rotate.z);
	MyBase::Matrix4x4 rotateXYZMatrix = Matrix::Multiply(rotateXMatrix, Matrix::Multiply(rotateYMatrix, rotateZMatrix));

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

		Matrix::MatrixScreenPrintf(0, 0, rotateXMatrix, "rotateXMatrix");
		Matrix::MatrixScreenPrintf(0, Matrix::kRowHeight * 5, rotateYMatrix, "rotateYMatrix");
		Matrix::MatrixScreenPrintf(0, Matrix::kRowHeight * 5 * 2, rotateZMatrix, "rotateZMatrix");
		Matrix::MatrixScreenPrintf(0, Matrix::kRowHeight * 5 * 3, rotateXYZMatrix, "rotateXYZMatrix");

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