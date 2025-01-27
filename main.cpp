#include <Novice.h>
#include "Script/Matrix.h"
#include "Script/MyTools.h"
#include "Script/Quaternion.h"
#include "Script/Draw.h"
#include <imgui.h>

const char kWindowTitle[] = "LE2B_22_ミヤザワ_ナオキ_MT4_1_04_Quaternioonによるベクトルの回転";

// ウィンドウサイズ
const int kWindowWidth = 1280, kWindowHeight = 720;

/// 二項演算子
Vector3 operator+(const Vector3& v1, const Vector3& v2) { return MyTools::Add(v1, v2); }
Vector3 operator-(const Vector3& v1, const Vector3& v2) { return MyTools::Subtract(v1, v2); }
Vector3 operator*(float s, const Vector3& v) { return MyTools::Multiply(s, v); }
Vector3 operator*(const Vector3& v, float s) { return s * v; }
Vector3 operator/(const Vector3& v, float s) { return MyTools::Multiply(1.0f / s, v); }
/// 二項演算子
Quaternion operator+(const Quaternion& q1, const Quaternion& q2) { return Quaternion::Add(q1, q2); }
Quaternion operator-(const Quaternion& q1, const Quaternion& q2) { return Quaternion::Subtract(q1, q2); }
Quaternion operator*(float s, const Quaternion& q) { return Quaternion::Multiply(s, q); }
Quaternion operator*(const Quaternion& q, float s) { return s * q; }
Quaternion operator/(const Quaternion& q, float s) { return Quaternion::Multiply(1.0f / s, q); }

/// 単項演算子
Vector3 operator-(const Vector3& v) { return { -v.x, -v.y, -v.z }; }
Vector3 operator+(const Vector3& v) { return v; }
/// 単項演算子
Quaternion operator-(const Quaternion& q) { return { -q.x, -q.y, -q.z, -q.w }; }
Quaternion operator+(const Quaternion& q) { return q; }

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
	Quaternion rotation0 = Quaternion::MakeRotateAxisAngleQuaternion({ 0.71f, 0.71f, 0.0f }, 0.3f);
	Quaternion rotation1 = Quaternion::MakeRotateAxisAngleQuaternion({ 0.71f, 0.0f, 0.71f }, 3.141592f);

	Quaternion interpolate0 = Quaternion::Slerp(rotation0, rotation1, 0.0f);
	Quaternion interpolate1 = Quaternion::Slerp(rotation0, rotation1, 0.3f);
	Quaternion interpolate2 = Quaternion::Slerp(rotation0, rotation1, 0.5f);
	Quaternion interpolate3 = Quaternion::Slerp(rotation0, rotation1, 0.7f);
	Quaternion interpolate4 = Quaternion::Slerp(rotation0, rotation1, 1.0f);

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

		Quaternion::QuaternionScreenPrintf(0, Quaternion::kRowHeight * 0, interpolate0, "Slerp(q0, q1, 0.0f)");
		Quaternion::QuaternionScreenPrintf(0, Quaternion::kRowHeight * 1, interpolate1, "Slerp(q0, q1, 0.3f)");
		Quaternion::QuaternionScreenPrintf(0, Quaternion::kRowHeight * 2, interpolate2, "Slerp(q0, q1, 0.5f)");
		Quaternion::QuaternionScreenPrintf(0, Quaternion::kRowHeight * 3, interpolate3, "Slerp(q0, q1, 0.7f)");
		Quaternion::QuaternionScreenPrintf(0, Quaternion::kRowHeight * 4, interpolate4, "Slerp(q0, q1, 1.0f)");

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