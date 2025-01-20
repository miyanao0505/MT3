#include <Novice.h>
#include "Script/Matrix.h"
#include "Script/MyTools.h"
#include "Script/Quaternion.h"
#include "Script/Draw.h"
#include <imgui.h>

const char kWindowTitle[] = "LE2B_22_ミヤザワ_ナオキ_MT4_1_03_Quaternionことはじめ";

// ウィンドウサイズ
const int kWindowWidth = 1280, kWindowHeight = 720;

/// 二項演算子
Vector3 operator+(const Vector3& v1, const Vector3& v2) { return MyTools::Add(v1, v2); }
Vector3 operator-(const Vector3& v1, const Vector3& v2) { return MyTools::Subtract(v1, v2); }
Vector3 operator*(float s, const Vector3& v) { return MyTools::Multiply(s, v); }
Vector3 operator*(const Vector3& v, float s) { return s * v; }
Vector3 operator/(const Vector3& v, float s) { return MyTools::Multiply(1.0f / s, v); }

/// 単項演算子
Vector3 operator-(const Vector3& v) { return { -v.x, -v.y, -v.z }; }
Vector3 operator+(const Vector3& v) { return v; }

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// 規定値
	Vector3 cameraTranslate = { 0.0f, 1.9f, -6.49f };
	Vector3 cameraRotate = { 0.26f, 0.0f, 0.0f };

	// 変動値

	// 各種行列の計算
	MyBase::Matrix4x4 cameraMatrix = Matrix::MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, cameraRotate, cameraTranslate);
	MyBase::Matrix4x4 viewMatrix = Matrix::Inverse(cameraMatrix);
	MyBase::Matrix4x4 projectionMatrix = Matrix::MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
	MyBase::Matrix4x4 viewProjectionMatrix = Matrix::Matrix::Multiply(viewMatrix, projectionMatrix);
	MyBase::Matrix4x4 viewportMatrix = Matrix::MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

	// お試し
	Vector3 from0 = MyTools::Normalize(Vector3{ 1.0f, 0.7f, 0.5f });
	Vector3 to0 = -from0;
	Vector3 from1 = MyTools::Normalize(Vector3{ -0.6f, 0.9f, 0.2f });
	Vector3 to1 = MyTools::Normalize(Vector3{ 0.4f, 0.7f, -0.5f });
	Matrix::Matrix4x4 rotateMatrix0 = Matrix::MakeDirectionToDirection(MyTools::Normalize(Vector3{ 1.0f, 0.0f, 0.0f }), MyTools::Normalize(Vector3{ -1.0f, 0.0f, 0.0f }));
	Matrix::Matrix4x4 rotateMatrix1 = Matrix::MakeDirectionToDirection(from0, to0);
	Matrix::Matrix4x4 rotateMatrix2 = Matrix::MakeDirectionToDirection(from1, to1);

	/*Quaternion q1 = { 2.0f, 3.0f, 4.0f, 1.0f };
	Quaternion q2 = { 1.0f, 3.0f, 5.0f, 2.0f };
	Quaternion identity = Quaternion::IdentityQuaternion();
	Quaternion conj = Quaternion::Conjugate(q1);
	Quaternion inv = Quaternion::Inverse(q1);
	Quaternion normal = Quaternion::Normalize(q1);
	Quaternion mul1 = Quaternion::Multiply(q1, q2);
	Quaternion mul2 = Quaternion::Multiply(q2, q1);
	float norm = Quaternion::Norm(q1);*/

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

		ImGui::SetNextWindowPos(ImVec2(20, 150), ImGuiCond_Once);							// ウィンドウの座標(プログラム起動時のみ読み込み)
		ImGui::SetNextWindowSize(ImVec2(400, 350), ImGuiCond_Once);							// ウィンドウのサイズ(プログラム起動時のみ読み込み)

		/*ImGui::Begin("Window");

		ImGui::End();*/

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
			// カメラ
			cameraTranslate = { 0.0f, 1.9f, -6.49f };
			cameraRotate = { 0.26f, 0.0f, 0.0f };
		}

		ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiCond_Once);							// ウィンドウの座標(プログラム起動時のみ読み込み)
		ImGui::SetNextWindowSize(ImVec2(400, 80), ImGuiCond_Once);							// ウィンドウのサイズ(プログラム起動時のみ読み込み)

		/*ImGui::Begin("camera");
		ImGui::DragFloat3("translate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("rotate", &cameraRotate.x, 0.01f);
		ImGui::End();*/

#endif // _DEBUG


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// グリッドの描画
		//Draw::DrawGrid(viewProjectionMatrix, viewportMatrix);

		Matrix::MatrixScreenPrintf(0, 0, rotateMatrix0, "rotateMatrix0");
		Matrix::MatrixScreenPrintf(0, Matrix::kRowHeight * 5, rotateMatrix1, "rotateMatrix1");
		Matrix::MatrixScreenPrintf(0, Matrix::kRowHeight * 10, rotateMatrix2, "rotateMatrix2");

		/*Quaternion::QuaternionScreenPrintf(0, 0, identity, "Identity");
		Quaternion::QuaternionScreenPrintf(0, Quaternion::kRowHeight, conj, "Conjugate");
		Quaternion::QuaternionScreenPrintf(0, Quaternion::kRowHeight * 2, inv, "Inverse");
		Quaternion::QuaternionScreenPrintf(0, Quaternion::kRowHeight * 3, normal, "Normalize");
		Quaternion::QuaternionScreenPrintf(0, Quaternion::kRowHeight * 4, mul1, "Multiply(q1, q2)");
		Quaternion::QuaternionScreenPrintf(0, Quaternion::kRowHeight * 5, mul2, "Multiply(q2, q1)");
		Novice::ScreenPrintf(0, Quaternion::kRowHeight * 6, "%.02f                            : Norm", norm);*/

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