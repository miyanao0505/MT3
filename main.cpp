#include <Novice.h>
#include "Script/Matrix.h"
#include "Script/MyTools.h"

const char kWindowTitle[] = "LE2A_17_ミヤザワ_ナオキ_MT3_0_3_拡大縮小と平行移動_確認課題";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// 3次元ベクトル
	MyBase::Vec3 translate{ 4.1f, 2.6f, 0.8f };
	MyBase::Vec3 scale = { 1.5f, 5.2f, 7.3f };
	MyBase::Vec3 point = { 2.3f, 3.8f, 1.4f };

	// 4x4行列
	MyBase::Matrix4x4 transformMatrix = {
		1.0f, 2.0f, 3.0f, 4.0f,
		3.0f, 1.0f, 1.0f, 2.0f,
		1.0f, 4.0f, 2.0f, 3.0f,
		2.0f, 2.0f, 1.0f, 3.0f
	};

	// 結果
	MyBase::Matrix4x4 translateMatrix = Matrix::MakeTranslateMatrix(translate);
	MyBase::Matrix4x4 scaleMatrix = Matrix::MakeScaleMatrix(scale);
	MyBase::Vec3 transformed = Matrix::Transform(point, transformMatrix);

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

		// 表示
		MyTools::VectorScreenPrintf(0, 0, transformed, "transformed");
		Matrix::MatrixScreenPrintf(0, Matrix::kRowHeight, translateMatrix, "translateMatrix");
		Matrix::MatrixScreenPrintf(0, Matrix::kRowHeight * 6, scaleMatrix, "scaleMatrix");

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