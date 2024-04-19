#include <Novice.h>
#include "Script/Matrix.h"
#include "Script/MyTools.h"

const char kWindowTitle[] = "LE2A_17_ミヤザワ_ナオキ_MT3_1_1_ポリゴンを描こう_応用課題";

// ウィンドウサイズ
const int kWindowWidth = 1280, kWindowHeight = 720;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// クロス積の確認用
	MyBase::Vec3 v1 = { 1.2f, -3.9f, 2.5f };
	MyBase::Vec3 v2 = { 2.8f, 0.4f, -1.3f };
	MyBase::Vec3 cross = MyTools::Cross(v1, v2);

	// 規定値
	MyBase::Vec3 kLocalVertices[3] = {
		{ 0.0f, 50.f, 0.0f },
		{ 40.f, -25.f, 0.0f },
		{ -40.f, -25.f, 0.0f }
	};
	MyBase::Vec3 cameraPosition = { 0.0f, 0.0f, 100.f };

	// 変動値
	MyBase::Vec3 rotate = { 0.0f, 0.0f, 0.0f };
	MyBase::Vec3 translate = { 0.0f, 0.0f, 500.f };

	// 各種行列の計算
	MyBase::Matrix4x4 worldMatrix = Matrix::MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, rotate, translate);
	MyBase::Matrix4x4 cameraMatrix = Matrix::MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, cameraPosition);
	MyBase::Matrix4x4 viewMatrix = Matrix::Inverse(cameraMatrix);
	MyBase::Matrix4x4 projectionMatrix = Matrix::MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
	MyBase::Matrix4x4 worldViewProjectionMatrix = Matrix::Multiply(worldMatrix, Matrix::Multiply(viewMatrix, projectionMatrix));
	MyBase::Matrix4x4 viewportMatrix = Matrix::MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);
	MyBase::Vec3 screenVertices[3];
	MyBase::Vec3 ndcVertex;

	// クロス積
	MyBase::Vec3 vectorA = { 0.f, 0.f, 0.f };
	MyBase::Vec3 vectorB = { 0.f, 0.f, 0.f };
	MyBase::Vec3 crossPositive = { 0.f, 0.f, 0.f };
	MyBase::Vec3 crossReverse = { 0.f, 0.f, 0.f };

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

		// 移動
		if (keys[DIK_A])
		{
			translate.x -= 2.f;
		}
		if (keys[DIK_D])
		{
			translate.x += 2.f;
		}
		if (keys[DIK_W])
		{
			translate.z += 5.f;
		}
		if (keys[DIK_S])
		{
			translate.z -= 5.f;
		}

		// 回転
		rotate.y += 1.f / 72 * float(M_PI);
		if (rotate.y > float(M_PI) * 2)
		{
			rotate.y = 0.f;
		}

		// 各種行列の計算
		worldMatrix = Matrix::MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, rotate, translate);
		cameraMatrix = Matrix::MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, cameraPosition);
		viewMatrix = Matrix::Inverse(cameraMatrix);
		projectionMatrix = Matrix::MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		worldViewProjectionMatrix = Matrix::Multiply(worldMatrix, Matrix::Multiply(viewMatrix, projectionMatrix));
		viewportMatrix = Matrix::MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		for (uint32_t i = 0; i < 3; ++i) {
			ndcVertex = Matrix::Transform(kLocalVertices[i], worldViewProjectionMatrix);
			screenVertices[i] = Matrix::Transform(ndcVertex, viewportMatrix);
		}

		// ベクトルA,Bの計算
		vectorA = MyTools::Subtract(screenVertices[1], screenVertices[0]);
		vectorB = MyTools::Subtract(screenVertices[2], screenVertices[1]);
		vectorA.y *= -1.f;
		vectorB.y += -1.f;

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// クロス積の確認用
		MyTools::VectorScreenPrintf(0, 0, cross, "Cross");

		// デバッグ用
		/*for (uint32_t i = 0; i < 3; ++i)
		{
			MyTools::VectorScreenPrintf(0, 20 + 20 * i, screenVertices[i], "screenVertices");
		}*/
		//MyTools::VectorScreenPrintf(0, 20, rotate, "ratate");

		if (MyTools::Dot(cameraPosition, MyTools::Cross(vectorA, vectorB)) <= 0.f)
		{
			// 三角の描画
			Novice::DrawTriangle(
				int(screenVertices[0].x), int(screenVertices[0].y),
				int(screenVertices[1].x), int(screenVertices[1].y),
				int(screenVertices[2].x), int(screenVertices[2].y),
				0xFF0000FF, kFillModeSolid
			);
		}

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