#include <Novice.h>
#include "Script/Matrix.h"
#include "Script/MyTools.h"
#include "Script/Draw.h"
#include <imgui.h>

const char kWindowTitle[] = "LE2A_17_ミヤザワ_ナオキ_MT3_04_04_平面にボールを落としてみよう_確認課題";

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
	MyBase::Plane plane;
	plane.normal = MyTools::Normalize({ -0.2f, 0.9f, -0.3f });
	plane.distance = 0.0f;

	MyBase::Ball ball{};
	ball.position = { 0.8f, 1.2f, 0.3f };
	ball.mass = 2.0f;
	ball.radius = 0.05f;
	ball.color = WHITE;

	Vector3 accele = { 0.0f, -9.8f, 0.0f };

	float deltaTime = 1.0f / 60.0f;
	float e = 0.5f;

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

				ball.velocity = { 0.0f, 0.0f, 0.0f };
				ball.acceleration = accele;
			}

			ImGui::Text("\n");

			if (ImGui::Button("Reset", { 50.f, 20.f }))
			{
				plane.normal = MyTools::Normalize({ -0.2f, 0.9f, -0.3f });
				plane.distance = 0.0f;

				ball.position = { 0.8f, 1.2f, 0.3f };
				ball.mass = 2.0f;
				ball.radius = 0.05f;
				ball.color = WHITE;

				accele = { 0.0f, -9.8f, 0.0f };

				e = 0.5f;

				deltaTime = 1.0f / 60.0f;

				// カメラ
				cameraTranslate = { 0.0f, 1.9f, -6.49f };
				cameraRotate = { 0.26f, 0.0f, 0.0f };
			}

			ImGui::Text("\n");

			ImGui::DragFloat3("planeNormal", &plane.normal.x, 0.01f);
			plane.normal = MyTools::Normalize(plane.normal);
			ImGui::DragFloat("planeDistance", &plane.distance, 0.01f);

			ImGui::Text("\n");

			ImGui::DragFloat3("ballPosition", &ball.position.x, 0.01f);
			ImGui::DragFloat("ball.radius", &ball.radius, 0.01f);

			ImGui::Text("\n");

			ImGui::DragFloat3("accele", &accele.x, 0.01f);
			ImGui::DragFloat("e", &e, 0.01f);
			ImGui::DragFloat("deltaTime", &deltaTime, 0.01f);
		}
		else
		{
			if (ImGui::Button("Stop", { 50.f, 20.f }))
			{
				isPlay = !isPlay;

				ball.position = { 0.8f, 1.2f, 0.3f };
			}

			ImGui::Text("\n");

			ImGui::Text("planeNormal : %.2f, %.2f, %.2f", plane.normal.x, plane.normal.y, plane.normal.z);
			ImGui::Text("planeDistance : %.2f", plane.distance);

			ImGui::Text("\n");

			ImGui::Text("ballPosition : %.2f, %.2f, %.2f", ball.position.x, ball.position.y, ball.position.z);
			ImGui::Text("ball.radius : %.2f", ball.radius);

			ImGui::Text("\n");
			
			ImGui::Text("accele : %.2f, %.2f, %.2f", accele.x, accele.y, accele.z);
			ImGui::Text("e : %.2f", e);
			ImGui::Text("deltaTime : %.2f", deltaTime);
		}
			
		ImGui::End();

#endif // _DEBUG

		if (isPlay)
		{
			ball.velocity += ball.acceleration * deltaTime;
			ball.position += ball.velocity * deltaTime;
			if (MyTools::IsCollision(MyBase::Sphere{ ball.position, ball.radius }, plane))
			{
				Vector3 reflected = MyTools::Reflect(ball.velocity, plane.normal);
				Vector3 projectToNormal = MyTools::Project(reflected, plane.normal);
				Vector3 movingDirection = reflected - projectToNormal;
				ball.velocity = projectToNormal * e + movingDirection;
			}
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
			plane.normal = MyTools::Normalize({ -0.2f, 0.9f, -0.3f });
			plane.distance = 0.0f;

			ball.position = { 0.8f, 1.2f, 0.3f };
			ball.mass = 2.0f;
			ball.radius = 0.05f;
			ball.color = WHITE;

			e = 0.5f;

			deltaTime = 1.0f / 60.0f;

			isPlay = false;

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

		// 平面の描画
		Draw::DrawPlane(plane, viewProjectionMatrix, viewportMatrix, WHITE);

		// ボールの描画
		Draw::DrawSphere(MyBase::Sphere{ ball.position, ball.radius }, viewProjectionMatrix, viewportMatrix, WHITE);

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