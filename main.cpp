#include <Novice.h>
#include "Script/Matrix.h"
#include "Script/MyTools.h"
#include "Script/Draw.h"
#include <imgui.h>

const char kWindowTitle[] = "LE2A_17_ミヤザワ_ナオキ_MT3_03_01_階層構造_確認課題";

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
	Vector3 translates[3] = {
		{0.2f, 1.0f, 0.0f},		// 肩
		{0.4f, 0.0f, 0.0f},		// 肘
		{0.3f, 0.0f, 0.0f},		// 手
	};
	Vector3 rotates[3] = {
		{0.0f, 0.0f, -6.8f},	// 肩
		{0.0f, 0.0f, -1.4f},	// 肘
		{0.0f, 0.0f, 0.0f},		// 手
	};
	Vector3 scales[3] = {
		{1.0f, 1.0f, 1.0f},		// 肩
		{1.0f, 1.0f, 1.0f},		// 肘
		{1.0f, 1.0f, 1.0f},		// 手
	};
	Matrix4x4 localMatrix[3] = {
		Matrix::MakeAffineMatrix(scales[0], rotates[0], translates[0]),		// 肩
		Matrix::MakeAffineMatrix(scales[1], rotates[1], translates[1]),		// 肘
		Matrix::MakeAffineMatrix(scales[2], rotates[2], translates[2]),		// 手
	};
	Matrix4x4 worldMatrix[3] = {
		localMatrix[0],														// 肩
		Matrix::Multiply(localMatrix[1], worldMatrix[0]),					// 肘
		Matrix::Multiply(localMatrix[2], worldMatrix[1]),					// 手
	};
	MyBase::Sphere spheres[3] = {
		MyBase::Sphere{.center{worldMatrix[0].m[3][0], worldMatrix[0].m[3][1], worldMatrix[0].m[3][2]}, .radius{0.1f}},		// 肩
		MyBase::Sphere{.center{worldMatrix[1].m[3][0], worldMatrix[1].m[3][1], worldMatrix[1].m[3][2]}, .radius{0.1f}},		// 肘
		MyBase::Sphere{.center{worldMatrix[2].m[3][0], worldMatrix[2].m[3][1], worldMatrix[2].m[3][2]}, .radius{0.1f}},		// 手
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
		
		ImGui::DragFloat3("translates[0]", &translates[0].x, 0.01f);
		ImGui::DragFloat3("rotates[0]", &rotates[0].x, 0.01f);
		ImGui::DragFloat3("scales[0]", &scales[0].x, 0.01f);
		localMatrix[0] = Matrix::MakeAffineMatrix(scales[0], rotates[0], translates[0]);

		ImGui::DragFloat3("translates[1]", &translates[1].x, 0.01f);
		ImGui::DragFloat3("rotates[1]", &rotates[1].x, 0.01f);
		ImGui::DragFloat3("scales[1]", &scales[1].x, 0.01f);
		localMatrix[1] = Matrix::MakeAffineMatrix(scales[1], rotates[1], translates[1]);

		ImGui::DragFloat3("translates[2]", &translates[2].x, 0.01f);
		ImGui::DragFloat3("rotates[2]", &rotates[2].x, 0.01f);
		ImGui::DragFloat3("scales[2]", &scales[2].x, 0.01f);
		localMatrix[2] = Matrix::MakeAffineMatrix(scales[2], rotates[2], translates[2]);

		// ワールド
		worldMatrix[0] = localMatrix[0];
		worldMatrix[1] = Matrix::Multiply(localMatrix[1], worldMatrix[0]);
		worldMatrix[2] = Matrix::Multiply(localMatrix[2], worldMatrix[1]);

		// 球
		spheres[0] = MyBase::Sphere{ .center{worldMatrix[0].m[3][0], worldMatrix[0].m[3][1], worldMatrix[0].m[3][2]}, .radius{0.1f} };
		spheres[1] = MyBase::Sphere{ .center{worldMatrix[1].m[3][0], worldMatrix[1].m[3][1], worldMatrix[1].m[3][2]}, .radius{0.1f} };
		spheres[2] = MyBase::Sphere{ .center{worldMatrix[2].m[3][0], worldMatrix[2].m[3][1], worldMatrix[2].m[3][2]}, .radius{0.1f} };

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
			// 肩
			translates[0] = { 0.2f, 1.0f, 0.0f };
			rotates[0] = { 0.0f, 0.0f, -6.8f };
			scales[0] = { 1.0f, 1.0f, 1.0f };
			
			// 肘
			translates[1] = { 0.4f, 0.0f, 0.0f };
			rotates[1] = { 0.0f, 0.0f, -1.4f };
			scales[1] = { 1.0f, 1.0f, 1.0f };

			// 手
			translates[2] = { 0.3f, 0.0f, 0.0f };
			rotates[2] = { 0.0f, 0.0f, 0.0f };
			scales[2] = { 1.0f, 1.0f, 1.0f };

			// ローカル
			localMatrix[0] = Matrix::MakeAffineMatrix(scales[0], rotates[0], translates[0]);
			localMatrix[1] = Matrix::MakeAffineMatrix(scales[1], rotates[1], translates[1]);
			localMatrix[2] = Matrix::MakeAffineMatrix(scales[2], rotates[2], translates[2]);

			// ワールド
			worldMatrix[0] = localMatrix[0];
			worldMatrix[1] = Matrix::Multiply(localMatrix[1], worldMatrix[0]);
			worldMatrix[2] = Matrix::Multiply(localMatrix[2], worldMatrix[1]);

			// 球
			spheres[0] = MyBase::Sphere{ .center{worldMatrix[0].m[3][0], worldMatrix[0].m[3][1], worldMatrix[0].m[3][2]}, .radius{0.1f} };
			spheres[1] = MyBase::Sphere{ .center{worldMatrix[1].m[3][0], worldMatrix[1].m[3][1], worldMatrix[1].m[3][2]}, .radius{0.1f} };
			spheres[2] = MyBase::Sphere{ .center{worldMatrix[2].m[3][0], worldMatrix[2].m[3][1], worldMatrix[2].m[3][2]}, .radius{0.1f} };

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
		
		// 肩の描画
		Draw::DrawSphere(spheres[0], viewProjectionMatrix, viewportMatrix, 0xFF0000FF);

		// 肘の描画
		Draw::DrawSphere(spheres[1], viewProjectionMatrix, viewportMatrix, 0x00FF00FF);

		// 手の描画
		Draw::DrawSphere(spheres[2], viewProjectionMatrix, viewportMatrix, 0x0000FFFF);

		// 肩-肘の描画
		Draw::DrawSegment(MyBase::Segment{ .origin = spheres[0].center, .diff = MyTools::Subtract(spheres[1].center, spheres[0].center) }, viewProjectionMatrix, viewportMatrix, 0xFFFFFFFF);

		// 肘-手の描画
		Draw::DrawSegment(MyBase::Segment{ .origin = spheres[1].center, .diff = MyTools::Subtract(spheres[2].center, spheres[1].center) }, viewProjectionMatrix, viewportMatrix, 0xFFFFFFFF);
		
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