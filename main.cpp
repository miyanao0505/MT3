#include <Novice.h>
#include "Script/Matrix.h"
#include "Script/MyTools.h"

const char kWindowTitle[] = "LE2A_17_ミヤザワ_ナオキ_MT3_1_0_レンダリングパイプラインVer2_確認課題";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// 結果
	Matrix::Matrix4x4 orthographicMatrix = Matrix::MakeOrthographicMatrix(-160.f, 160.f, 200.0f, 300.0f, 0.0f, 1000.0f);
	Matrix::Matrix4x4 perspectiveFovMatrix = Matrix::MakePerspectiveFovMatrix(0.63f, 1.33f, 0.1f, 1000.0f);
	Matrix::Matrix4x4 viewportMatrix = Matrix::MakeViewportMatrix(100.0f, 200.0f, 600.0f, 300.0f, 0.0f, 1.0f);

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

		Matrix::MatrixScreenPrintf(0, 0, orthographicMatrix, "orthographicMatrix");
		Matrix::MatrixScreenPrintf(0, Matrix::kRowHeight * 5, perspectiveFovMatrix, "perspectiveFovMatrix");
		Matrix::MatrixScreenPrintf(0, Matrix::kRowHeight * 10, viewportMatrix, "viewportMatrix");

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