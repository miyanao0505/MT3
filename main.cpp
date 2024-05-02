#include <Novice.h>
#include "Script/Matrix.h"
#include "Script/MyTools.h"
#include "Script/Draw.h"
#include <imgui.h>

const char kWindowTitle[] = "LE2A_17_ミヤザワ_ナオキ_MT3_02_00_点と線の距離_確認課題";

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
	MyBase::Segment segment = { { -2.0f, -1.0f, 0.0f }, { 3.0f, 2.0f, 2.0f } };
	Vector3 point = { -1.5f, 0.6f, 0.6f };

	Vector3 project = MyTools::Project(MyTools::Subtract(point, segment.origin), segment.diff);
	Vector3 closestPoint = MyTools::ClosestPoint(point, segment);

	MyBase::Sphere pointSphere = { point, 0.01f };		// 1cmの球を描画
	MyBase::Sphere closestPointSphere = { closestPoint, 0.01f };

	// 各種行列の計算
	Matrix4x4 cameraMatrix = Matrix::MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, cameraRotate, cameraTranslate);
	Matrix4x4 viewMatrix = Matrix::Inverse(cameraMatrix);
	Matrix4x4 projectionMatrix = Matrix::MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
	Matrix4x4 viewProjectionMatrix = Matrix::Matrix::Multiply(viewMatrix, projectionMatrix);
	Matrix4x4 viewportMatrix = Matrix::MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

	Vector3 start = Matrix::Transform(Matrix::Transform(segment.origin, viewProjectionMatrix), viewportMatrix);
	Vector3 end = Matrix::Transform(Matrix::Transform(MyTools::Add(segment.origin, segment.diff), viewProjectionMatrix), viewportMatrix);

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

		ImGui::Begin("Window");
		ImGui::InputFloat3("Point", &point.x, "%.3f");
		ImGui::InputFloat3("Segment origin", &segment.origin.x, "%.3f");
		ImGui::InputFloat3("Segment diff", &segment.diff.x, "%.3f");
		ImGui::InputFloat3("Project", &project.x, "%.3f");
		ImGui::End();

		// 各種行列の計算
		cameraMatrix = Matrix::MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, cameraRotate, cameraTranslate);
		viewMatrix = Matrix::Inverse(cameraMatrix);
		projectionMatrix = Matrix::MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		viewProjectionMatrix = Matrix::Multiply(viewMatrix, projectionMatrix);
		viewportMatrix = Matrix::MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		project = MyTools::Project(MyTools::Subtract(point, segment.origin), segment.diff);
		closestPoint = MyTools::ClosestPoint(point, segment);

		pointSphere = { point, 0.01f };
		closestPointSphere = { closestPoint, 0.01f };

		start = Matrix::Transform(Matrix::Transform(segment.origin, viewProjectionMatrix), viewportMatrix);
		end = Matrix::Transform(Matrix::Transform(MyTools::Add(segment.origin, segment.diff), viewProjectionMatrix), viewportMatrix);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// グリッドの描画
		Draw::DrawGrid(viewProjectionMatrix, viewportMatrix);

		// 球の描画
		Draw::DrawSphere(pointSphere, viewProjectionMatrix, viewportMatrix, RED);
		Draw::DrawSphere(closestPointSphere, viewProjectionMatrix, viewportMatrix, BLACK);

		// 線分の描画
		Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), WHITE);

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