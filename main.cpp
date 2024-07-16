#include <Novice.h>
#include "Script/Matrix.h"
#include "Script/MyTools.h"
#include "Script/Draw.h"
#include <imgui.h>

const char kWindowTitle[] = "LE2A_17_ミヤザワ_ナオキ_MT3_04_01_円運動_確認課題";

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
	Vector3 c = { 0.0f, 0.0f, 0.0f };
	float r = 0.8f;

	MyBase::Ball ball{};
	ball.position = { 0.8f, 0.0f, 0.0f };
	ball.mass = 2.0f;
	ball.radius = 0.05f;
	ball.color = WHITE;

	float deltaTime = 1.0f / 60.0f;
	float angularVelocity = 3.14f;
	float angle = 0.0f;					// 角速度
	float omega = angularVelocity * deltaTime;

	Vector3 p = { r, 0.0f, 0.0f };
	ball.position = p;

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
				p = { r, 0.0f, 0.0f };
				angle = 0.0f;
			}

			ImGui::Text("\n");

			ImGui::Text("BallPos : %.2f, %.2f, %.2f", ball.position.x, ball.position.y, ball.position.z);
			ImGui::Text("BallVelocity : %.6f, %.6f, %.2f", ball.velocity.x, ball.velocity.y, ball.velocity.z);
			ImGui::Text("BallAcceleration : %.6f, %.6f, %.2f", ball.acceleration.x, ball.acceleration.y, ball.acceleration.z);
			ImGui::Text("BallRadius : %.2f", ball.radius);

			ImGui::Text("\n");

			ImGui::DragFloat3("c", &c.x, 0.01f);
			ball.position = { c.x + r, c.y, c.z };
			ImGui::DragFloat("r", &r, 0.01f);
			ball.position.x = c.x + r;

			ImGui::Text("\n");

			ImGui::DragFloat("angularVelocity", &angularVelocity, 0.01f);
			ImGui::DragFloat("deltaTime", &deltaTime, 0.01f);
			omega = angularVelocity * deltaTime;
			ImGui::Text("angle : %.2f", angle);
			ImGui::Text("omega : %.2f", omega);
		}
		else
		{
			if (ImGui::Button("Stop", { 50.f, 20.f }))
			{
				isPlay = !isPlay;
			}
			ImGui::Text("\n");

			ImGui::Text("BallPos : %.2f, %.2f, %.2f", ball.position.x, ball.position.y, ball.position.z);
			ImGui::Text("BallVelocity : %.6f, %.6f, %.2f", ball.velocity.x, ball.velocity.y, ball.velocity.z);
			ImGui::Text("BallAcceleration : %.6f, %.6f, %.2f", ball.acceleration.x, ball.acceleration.y, ball.acceleration.z);
			//ImGui::Text("BallMass : %.2f", ball.mass);
			ImGui::Text("BallRadius : %.2f", ball.radius);

			ImGui::Text("\n");

			ImGui::Text("c : %.2f, %.2f, %.2f", c.x, c.y, c.z);
			ImGui::Text("r : %.2f", r);

			ImGui::Text("\n");

			ImGui::Text("angularVelocity : %.2f", angularVelocity);
			ImGui::Text("angle : %.2f", angle);
			ImGui::Text("omega : %.2f", omega);
		}

		
			
		ImGui::End();

#endif // _DEBUG

		if (isPlay)
		{
			angle += omega;

			p = ball.position;

			ball.velocity.x = -r * omega * std::sinf(angle);
			ball.velocity.y = r * omega * std::cosf(angle);

			ball.acceleration.x = -powf(omega, 2) * (p.x - c.x);
			ball.acceleration.y = -powf(omega, 2) * (p.y - c.y);

			p.x += ball.velocity.x + ball.acceleration.x;
			p.y += ball.velocity.y + ball.acceleration.y;
			p.z = c.z;
			ball.position = p/* + c*/;
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
			c = { 0.0f, 0.0f, 0.0f };
			p = { r, 0.0f, 0.0f };
			r = 0.8f;

			ball.position = { r, 0.0f, 0.0f };
			ball.mass = 2.0f;
			ball.radius = 0.05f;
			ball.color = WHITE;
			ball.acceleration = { 0.0f, 0.0f, 0.0f };
			ball.velocity = { 0.0f, 0.0f, 0.0f };

			deltaTime = 1.0f / 60.0f;
			angularVelocity = 3.14f / 2.f;
			angle = 0.0f;

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