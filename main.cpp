#include <Novice.h>
#include "Script/Matrix.h"
#include "Script/MyTools.h"
#include "Script/Draw.h"
#include <imgui.h>

const char kWindowTitle[] = "LE2A_17_ミヤザワ_ナオキ_MT3_04_00_ばねを作ってみよう_確認課題";

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
	MyBase::Spring spring{};
	spring.anchor = { 0.0f, 0.0f, 0.0f };
	spring.naturalLength = 1.0f;
	spring.stiffness = 100.0f;
	spring.dampungCoefficient = 2.0f;

	MyBase::Ball ball{};
	ball.position = { 1.2f, 0.0f, 0.0f };
	ball.mass = 2.0f;
	ball.radius = 0.05f;
	ball.color = BLUE;

	float deltaTime = 1.0f / 60.0f;

	Vector3 diff = ball.position - spring.anchor;
	Vector3 direction;
	Vector3 restPosition;
	Vector3 displacement;
	Vector3 restoringForce;
	Vector3 dampingForce;
	Vector3 force;
	float length = MyTools::Length(diff);
	if (length != 0.0f) {
		direction = MyTools::Normalize(diff);
		restPosition = spring.anchor + direction * spring.naturalLength;
		displacement = length * (ball.position - restPosition);
		restoringForce = -spring.stiffness * displacement;
		// 減衰抵抗を計算する
		dampingForce = -spring.dampungCoefficient * ball.velocity;
		// 減衰抵抗も加味して、物体にかかるちからを決定する
		force = restoringForce + dampingForce;
		ball.acceleration = force / ball.mass;
	}
	// 加速度も速度もどちらも秒を基準とした値である
	// それが、1/60秒間(deltaTime)適用されたと考える
	ball.velocity += ball.acceleration * deltaTime;
	ball.position += ball.velocity * deltaTime;

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

		ImGui::SetNextWindowPos(ImVec2(750, 50), ImGuiCond_Once);							// ウィンドウの座標(プログラム起動時のみ読み込み)
		ImGui::SetNextWindowSize(ImVec2(450, 400), ImGuiCond_Once);							// ウィンドウのサイズ(プログラム起動時のみ読み込み)

		ImGui::Begin("Window");
		
		if (!isPlay)
		{
			if (ImGui::Button("Start", { 50.f, 20.f }))
			{
				isPlay = !isPlay;

				spring.anchor = { 0.0f, 0.0f, 0.0f };
				spring.naturalLength = 1.0f;
				spring.stiffness = 100.0f;
				spring.dampungCoefficient = 2.0f;

				ball.position = { 1.2f, 0.0f, 0.0f };
				ball.mass = 2.0f;
				ball.radius = 0.05f;
				ball.color = BLUE;

				ball.acceleration = { 0.0f, 0.0f, 0.0f };
				ball.velocity = { 0.0f, 0.0f, 0.0f };
			}
		}
		else
		{
			if (ImGui::Button("Stop", { 50.f, 20.f }) || MyTools::Length(ball.velocity) == 0.0f)
			{
				isPlay = !isPlay;
			}
			ImGui::Text("\n");

			ImGui::Text("BallPos : %.2f, %.2f, %.2f", ball.position.x, ball.position.y, ball.position.z);
			ImGui::Text("BallVelocity : %.2f, %.2f, %.2f", ball.velocity.x, ball.velocity.y, ball.velocity.z);
			ImGui::Text("BallAcceleration : %.2f, %.2f, %.2f", ball.acceleration.x, ball.acceleration.y, ball.acceleration.z);
			ImGui::Text("BallMass : %.2f", ball.mass);
			ImGui::Text("BallRadius : %.2f", ball.radius);

			ImGui::Text("\n");

			ImGui::Text("SpringAnchor : %.2f, %.2f, %.2f", spring.anchor.x, spring.anchor.y, spring.anchor.z);
			ImGui::Text("SpringNaturalLength : %.2f", spring.naturalLength);
			ImGui::Text("SpringStiffness : %.2f", spring.stiffness);
			ImGui::Text("SpringDampungCoefficient : %.2f", spring.dampungCoefficient);
		}

		

		ImGui::End();

#endif // _DEBUG

		if (isPlay)
		{
			diff = ball.position - spring.anchor;
			length = MyTools::Length(diff);
			if (length != 0.0f) {
				direction = MyTools::Normalize(diff);
				restPosition = spring.anchor + direction * spring.naturalLength;
				displacement = length * (ball.position - restPosition);
				restoringForce = -spring.stiffness * displacement;
				dampingForce = -spring.dampungCoefficient * ball.velocity;
				force = restoringForce + dampingForce;
				ball.acceleration = force / ball.mass;
			}
			// 加速度も速度もどちらも秒を基準とした値である
			// それが、1/60秒間(deltaTime)適用されたと考える
			ball.velocity += ball.acceleration * deltaTime;
			ball.position += ball.velocity * deltaTime;
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

		// 線分の描画
		Draw::DrawSegment(MyBase::Segment{ .origin = spring.anchor, .diff = MyTools::Subtract(ball.position, spring.anchor) }, viewProjectionMatrix, viewportMatrix, 0xFFFFFFFF);
				
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