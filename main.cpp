#include <Novice.h>
#include "Script/Matrix.h"
#include "Script/MyTools.h"
#include "Script/Draw.h"
#include <imgui.h>

const char kWindowTitle[] = "LE2A_17_ミヤザワ_ナオキ_MT3_02_10_3次元衝突判定(OBBとOBB/AABB)_確認課題";

// ウィンドウサイズ
const int kWindowWidth = 1280, kWindowHeight = 720;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);
	                                 
	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// 規定値
	Vector3 cameraTranslate = { 0.0f, 1.9f, -6.49f };
	Vector3 cameraRotate = { 0.26f, 0.0f, 0.0f };

	// 変動値
	Vector3 rotate1{ 0.0f, 0.0f, 0.0f };
	Vector3 rotate2{ -0.05f, -2.49f, 0.15f };
	MyBase::OBB obb1{
		.center{-0.0f, 0.0f, 0.0f},
		.orientations = {{1.0f, 0.0f, 0.0f},
						 {0.0f, 1.0f, 0.0f},
						 {0.0f, 0.0f, 1.0f}},
		.size{0.83f, 0.26f, 0.24f}
	};
	MyBase::OBB obb2{
		.center{0.9f, 0.66f, 0.78f},
		.orientations = {{1.0f, 0.0f, 0.0f},
						 {0.0f, 1.0f, 0.0f},
						 {0.0f, 0.0f, 1.0f}},
		.size{0.5f, 0.37f, 0.5f}
	};

	// 各種行列の計算
	Matrix4x4 cameraMatrix = Matrix::MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, cameraRotate, cameraTranslate);
	Matrix4x4 viewMatrix = Matrix::Inverse(cameraMatrix);
	Matrix4x4 projectionMatrix = Matrix::MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
	Matrix4x4 viewProjectionMatrix = Matrix::Matrix::Multiply(viewMatrix, projectionMatrix);
	Matrix4x4 viewportMatrix = Matrix::MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

#ifdef _DEBUG

	// デバッグ用
	float cameraRadian = 1.f / 300.f * float(M_PI);

#endif // _DEBUG

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
		 
#ifdef _DEBUG

		ImGui::SetNextWindowPos(ImVec2(750, 50), ImGuiCond_Once);							// ウィンドウの座標(プログラム起動時のみ読み込み)
		ImGui::SetNextWindowSize(ImVec2(450, 400), ImGuiCond_Once);							// ウィンドウのサイズ(プログラム起動時のみ読み込み)

		ImGui::Begin("Window");
		ImGui::DragFloat3("obb1.center", &obb1.center.x, 0.01f);
		ImGui::DragFloat("rotate1X", &rotate1.x, 0.01f);
		ImGui::DragFloat("rotate1Y", &rotate1.y, 0.01f);
		ImGui::DragFloat("rotate1Z", &rotate1.z, 0.01f);

		// 回転行列の生成
		Matrix4x4 rotateMatrix1 = Matrix::Multiply(Matrix::MakeRotateXMatrix4x4(rotate1.x), Matrix::Multiply(Matrix::MakeRotateYMatrix4x4(rotate1.y), Matrix::MakeRotateZMatrix4x4(rotate1.z)));

		// 回転行列から軸を抽出
		obb1.orientations[0].x = rotateMatrix1.m[0][0];
		obb1.orientations[0].y = rotateMatrix1.m[0][1];
		obb1.orientations[0].z = rotateMatrix1.m[0][2];

		obb1.orientations[1].x = rotateMatrix1.m[1][0];
		obb1.orientations[1].y = rotateMatrix1.m[1][1];
		obb1.orientations[1].z = rotateMatrix1.m[1][2];

		obb1.orientations[2].x = rotateMatrix1.m[2][0];
		obb1.orientations[2].y = rotateMatrix1.m[2][1];
		obb1.orientations[2].z = rotateMatrix1.m[2][2];

		ImGui::DragFloat3("obb1.orientations[0]", &obb1.orientations[0].x, 0.01f);
		ImGui::DragFloat3("obb1.orientations[1]", &obb1.orientations[1].x, 0.01f);
		ImGui::DragFloat3("obb1.orientations[2]", &obb1.orientations[2].x, 0.01f);
		ImGui::DragFloat3("obb1.size", &obb1.size.x, 0.01f);
		
		ImGui::DragFloat3("obb2.center", &obb2.center.x, 0.01f);
		ImGui::DragFloat("rotate2X", &rotate2.x, 0.01f);
		ImGui::DragFloat("rotate2Y", &rotate2.y, 0.01f);
		ImGui::DragFloat("rotate2Z", &rotate2.z, 0.01f);

		// 回転行列の生成
		Matrix4x4 rotateMatrix2 = Matrix::Multiply(Matrix::MakeRotateXMatrix4x4(rotate2.x), Matrix::Multiply(Matrix::MakeRotateYMatrix4x4(rotate2.y), Matrix::MakeRotateZMatrix4x4(rotate2.z)));

		// 回転行列から軸を抽出
		obb2.orientations[0].x = rotateMatrix2.m[0][0];
		obb2.orientations[0].y = rotateMatrix2.m[0][1];
		obb2.orientations[0].z = rotateMatrix2.m[0][2];

		obb2.orientations[1].x = rotateMatrix2.m[1][0];
		obb2.orientations[1].y = rotateMatrix2.m[1][1];
		obb2.orientations[1].z = rotateMatrix2.m[1][2];

		obb2.orientations[2].x = rotateMatrix2.m[2][0];
		obb2.orientations[2].y = rotateMatrix2.m[2][1];
		obb2.orientations[2].z = rotateMatrix2.m[2][2];

		ImGui::DragFloat3("obb2.orientations[0]", &obb2.orientations[0].x, 0.01f);
		ImGui::DragFloat3("obb2.orientations[1]", &obb2.orientations[1].x, 0.01f);
		ImGui::DragFloat3("obb2.orientations[2]", &obb2.orientations[2].x, 0.01f);
		ImGui::DragFloat3("obb2.size", &obb2.size.x, 0.01f);

		ImGui::End();

#endif // _DEBUG

		// 各種行列の計算
		cameraMatrix = Matrix::MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, cameraRotate, cameraTranslate);
		viewMatrix = Matrix::Inverse(cameraMatrix);
		projectionMatrix = Matrix::MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		viewProjectionMatrix = Matrix::Multiply(viewMatrix, projectionMatrix);
		viewportMatrix = Matrix::MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

#ifdef _DEBUG

		// カメラの移動
		if (!keys[DIK_LCONTROL])
		{
			// X座標
			if (keys[DIK_LEFT])
			{
				cameraTranslate.x -= 0.02f;
			}
			if (keys[DIK_RIGHT])
			{
				cameraTranslate.x += 0.02f;
			}
			// Y座標
			if (!keys[DIK_LSHIFT] && keys[DIK_UP])
			{
				cameraTranslate.y += 0.02f;
			}
			if (!keys[DIK_LSHIFT] && keys[DIK_DOWN])
			{
				cameraTranslate.y -= 0.02f;
			}
			// Z座標
			if (keys[DIK_LSHIFT] && keys[DIK_UP])
			{
				cameraTranslate.z += 0.02f;
			}
			if (keys[DIK_LSHIFT] && keys[DIK_DOWN])
			{
				cameraTranslate.z -= 0.02f;
			}
		}

		// カメラの回転
		if (keys[DIK_LCONTROL])
		{
			// X軸
			if (keys[DIK_DOWN])
			{
				cameraRotate.x += cameraRadian;
			}
			if (keys[DIK_UP])
			{
				cameraRotate.x -= cameraRadian;
			}
			// Y軸
			if (!keys[DIK_LSHIFT] && keys[DIK_LEFT])
			{
				cameraRotate.y -= cameraRadian;
			}
			if (!keys[DIK_LSHIFT] && keys[DIK_RIGHT])
			{
				cameraRotate.y += cameraRadian;
			}
			// Z軸
			if (keys[DIK_LSHIFT] && keys[DIK_LEFT])
			{
				cameraRotate.z -= cameraRadian;
			}
			if (keys[DIK_LSHIFT] && keys[DIK_RIGHT])
			{
				cameraRotate.z += cameraRadian;
			}
		}

		// リセット
		if (keys[DIK_R] && !preKeys[DIK_R])
		{
			obb1 = {
				.center{-0.0f, 0.0f, 0.0f},
				.orientations = {{1.0f, 0.0f, 0.0f},
								 {0.0f, 1.0f, 0.0f},
								 {0.0f, 0.0f, 1.0f}},
				.size{0.83f, 0.26f, 0.24f}
			};

			obb2 = {
				.center{0.9f, 0.66f, 0.78f},
				.orientations = {{1.0f, 0.0f, 0.0f},
								 {0.0f, 1.0f, 0.0f},
								 {0.0f, 0.0f, 1.0f}},
				.size{0.5f, 0.37f, 0.5f}
			};

			// カメラ
			cameraTranslate = { 0.0f, 1.9f, -6.49f };
			cameraRotate = { 0.26f, 0.0f, 0.0f };
		}

		ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiCond_Once);							// ウィンドウの座標(プログラム起動時のみ読み込み)
		ImGui::SetNextWindowSize(ImVec2(400, 80), ImGuiCond_Once);							// ウィンドウのサイズ(プログラム起動時のみ読み込み)

		ImGui::Begin("camera");
		ImGui::DragFloat3("translate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("rotate", &cameraRotate.x, 0.01f);
		ImGui::End();

#endif // _DEBUG


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// グリッドの描画
		Draw::DrawGrid(viewProjectionMatrix, viewportMatrix);

		// OBBの描画
		if (MyTools::IsCollision(obb1, obb2, viewProjectionMatrix, viewportMatrix))
		{
			Draw::DrawOBB(obb1, viewProjectionMatrix, viewportMatrix, RED);
		}
		else
		{
			Draw::DrawOBB(obb1, viewProjectionMatrix, viewportMatrix, WHITE);
		}
		// Sphereの描画
		Draw::DrawOBB(obb2, viewProjectionMatrix, viewportMatrix, WHITE);

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