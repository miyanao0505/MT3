#include <Novice.h>
#include "Script/Matrix.h"
#include "Script/MyTools.h"
#include "Script/Draw.h"
#include <imgui.h>

const char kWindowTitle[] = "LE2A_17_ミヤザワ_ナオキ_MT3_04_02_振り子を作ってみよう_確認課題";

// ウィンドウサイズ
const int kWindowWidth = 1280, kWindowHeight = 720;

/// 二項演算子
Vector3 operator+(const Vector3& v1, const Vector3& v2) { return MyTools::Add(v1, v2); }
Vector3 operator-(const Vector3& v1, const Vector3& v2) { return MyTools::Subtract(v1, v2); }
Vector3 operator*(float s, const Vector3& v) { return MyTools::Multiply(s, v); }
Vector3 operator*(const Vector3& v, float s) { return s * v; }
Vector3 operator/(const Vector3& v, float s) { return MyTools::Multiply(1.0f / s, v); }
Matrix4x4 operator+(const Matrix4x4& m1, const Matrix4x4& m2) { return Matrix::Add(m1, m2); }
Matrix4x4 operator-(const Matrix4x4& m1, const Matrix4x4& m2) { return Matrix::Subtract(m1, m2); }
Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2) { return Matrix::Multiply(m1, m2); }

/// 単項演算子
Vector3 operator-(const Vector3& v) { return { -v.x, -v.y, -v.z }; }
Vector3 operator+(const Vector3& v) { return v; }

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
	MyBase::Pendulum pendulum;
	pendulum.anchor = { 0.0f, 1.0f, 0.0f };
	pendulum.length = 0.8f;
	pendulum.angle = 0.7f;
	pendulum.angularVelocity = 0.0f;
	pendulum.angularAcceleration = 0.0f;

	MyBase::Ball ball{};
	ball.position = pendulum.anchor;
	ball.position.y -= pendulum.length;
	ball.mass = 2.0f;
	ball.radius = 0.05f;
	ball.color = WHITE;

	float deltaTime = 1.0f / 60.0f;

	Vector3 p = { 0.0f, 0.0f, 0.0f };

	bool isPlay = false;

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

		ImGui::SetNextWindowPos(ImVec2(20, 150), ImGuiCond_Once);							// ウィンドウの座標(プログラム起動時のみ読み込み)
		ImGui::SetNextWindowSize(ImVec2(400, 350), ImGuiCond_Once);							// ウィンドウのサイズ(プログラム起動時のみ読み込み)

		ImGui::Begin("Window");
		
		if (!isPlay)
		{
			if (ImGui::Button("Start", { 50.f, 20.f }))
			{
				isPlay = !isPlay;
				p = { 0.0f, 0.0f, 0.0f };
			}

			ImGui::Text("\n");

			if (ImGui::Button("Reset", { 50.f, 20.f }))
			{
				pendulum.anchor = { 0.0f, 1.0f, 0.0f };
				pendulum.length = 0.8f;
				pendulum.angle = 0.7f;
				pendulum.angularVelocity = 0.0f;
				pendulum.angularAcceleration = 0.0f;

				ball.position = pendulum.anchor;
				ball.position.y -= pendulum.length;
				ball.mass = 2.0f;
				ball.radius = 0.05f;
				ball.color = WHITE;

				deltaTime = 1.0f / 60.0f;

				p = { 0.0f, 0.0f, 0.0f };

				// カメラ
				cameraTranslate = { 0.0f, 1.9f, -6.49f };
				cameraRotate = { 0.26f, 0.0f, 0.0f };
			}

			ImGui::Text("\n");

			ImGui::DragFloat3("pendulumAnchor", &pendulum.anchor.x, 0.01f);
			ImGui::DragFloat("pendulumLength", &pendulum.length, 0.01f);
			ball.position = pendulum.anchor;
			ball.position.y -= pendulum.length;
			ImGui::DragFloat("pendulumAngle", &pendulum.angle, 0.01f);

			ImGui::Text("\n");

			ImGui::Text("BallPos : %.2f, %.2f, %.2f", ball.position.x, ball.position.y, ball.position.z);
			ImGui::Text("BallRadius : %.2f", ball.radius);

			ImGui::Text("\n");

			ImGui::DragFloat("deltaTime", &deltaTime, 0.01f);
		}
		else
		{
			if (ImGui::Button("Stop", { 50.f, 20.f }))
			{
				isPlay = !isPlay;
			}
			ImGui::Text("\n");
			
			ImGui::Text("pendulumAnchor : %.2f, %.2f, %.2f", pendulum.anchor.x, pendulum.anchor.y, pendulum.anchor.z);
			ImGui::Text("pendulumLength : %.2f", pendulum.length);
			ImGui::Text("pendulumAngle : %.2f", pendulum.angle);
			ImGui::Text("pendulumAngularVelocity : %.2f", pendulum.angularVelocity);
			ImGui::Text("pendulumAngularAcceleration : %.f", pendulum.angularAcceleration);

			ImGui::Text("\n");

			ImGui::Text("BallPos : %.2f, %.2f, %.2f", ball.position.x, ball.position.y, ball.position.z);
			ImGui::Text("BallRadius : %.2f", ball.radius);

			ImGui::Text("\n");

			ImGui::Text("deltaTime", &deltaTime, 0.01f);
		}

		
			
		ImGui::End();

#endif // _DEBUG

		if (isPlay)
		{
			pendulum.angularAcceleration = -(9.8f / pendulum.length) * std::sin(pendulum.angle);
			pendulum.angularVelocity += pendulum.angularAcceleration * deltaTime;
			pendulum.angle += pendulum.angularVelocity * deltaTime;

			// pは振り子の先端の位置、取り付けたいものを取り付ければ良い
			p.x = pendulum.anchor.x + std::sin(pendulum.angle) * pendulum.length;
			p.y = pendulum.anchor.y - std::cos(pendulum.angle) * pendulum.length;
			p.z = pendulum.anchor.z;
			ball.position = p;
		}

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
			pendulum.anchor = { 0.0f, 1.0f, 0.0f };
			pendulum.length = 0.8f;
			pendulum.angle = 0.7f;
			pendulum.angularVelocity = 0.0f;
			pendulum.angularAcceleration = 0.0f;

			ball.position = pendulum.anchor;
			ball.position.y -= pendulum.length;
			ball.mass = 2.0f;
			ball.radius = 0.05f;
			ball.color = WHITE;

			deltaTime = 1.0f / 60.0f;

			p = { 0.0f, 0.0f, 0.0f };

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
		
		// 線分の描画
		Draw::DrawSegment(MyBase::Segment{ .origin = pendulum.anchor, .diff = ball.position - pendulum.anchor }, viewProjectionMatrix, viewportMatrix, WHITE);

		// 球の描画
		Draw::DrawSphere(MyBase::Sphere{ .center = ball.position, .radius = ball.radius }, viewProjectionMatrix, viewportMatrix, ball.color);

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