#include <Novice.h>
#include "Script/Matrix.h"
#include "Script/MyTools.h"

const char kWindowTitle[] = "LE2A_17_ミヤザワ_ナオキ_MT3_0_1_3次元への拡張(ベクトル)_確認課題";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// 定数
	const int kRowHeight = 20;			// 縦：一文字、20
	//const int kColumnWidth = 55;		// 横：一文字、11

	// 変数
	MyBase::Vec3 v1 = { 1.0f, 3.0f, -5.0f };
	MyBase::Vec3 v2 = { 4.0f, -1.0f, 2.0f };
	float k = { 4.0f };

	MyBase::Vec3 resultAdd = MyTools::Add(v1, v2);
	MyBase::Vec3 resultSubtract = MyTools::Subtract(v1, v2);
	MyBase::Vec3 resultMultiply = MyTools::Multiply(k, v1);
	float resultDot = MyTools::Dot(v1, v2);
	float resultLength = MyTools::Length(v1);
	MyBase::Vec3 resultNormalize = MyTools::Normalize(v2);

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

		MyTools::VectorScreenPrintf(0, 0, resultAdd, "  : Add");
		MyTools::VectorScreenPrintf(0, kRowHeight, resultSubtract, "  : Subtract");
		MyTools::VectorScreenPrintf(0, kRowHeight * 2, resultMultiply, "  : Multiply");
		Novice::ScreenPrintf(0, kRowHeight * 3, "%.02f  : Dot", resultDot);
		Novice::ScreenPrintf(0, kRowHeight * 4, "%.02f  : Length", resultLength);
		MyTools::VectorScreenPrintf(0, kRowHeight * 5, resultNormalize, "  : Normalize");

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