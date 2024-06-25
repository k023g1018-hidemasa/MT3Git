#include "MTFunction.h"
#include <Novice.h>
#include"ImGuiManager.h"
//#include"ViewProjection.h"

const char kWindowTitle[] = "GC2B_15_ヒラジマ_ヒデマサ＿MT3";

		bool IsCollision(const Sphere& s1, const Sphere& s2) {

			float distance = Length(Subtract(s2.center, s1.center));

			if (distance <= s1.radius + s2.radius) {
				return true;
			}
			return false;
		}
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Vector3 rotate{};
	Vector3 translate{};
	Vector3 cameraRotate = {0.26f};
	Vector3 cameraPosition{0.0f, 1.9f, -6.49f};

	Sphere sphere1 = {{}, 0.5f};
	Sphere sphere2 = {{}, 0.3f};
	uint32_t color = WHITE;
	debugCamera_ = new DebugCamera(1280, 720);



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
		
		if (IsCollision(sphere1, sphere2)) {
			color = RED;
		} else {
			color = WHITE;
		}

		Matrix4x4 worldMatrix = MakeAffineMatrix({1.0f, 1.0f, 1.0f}, rotate, translate);
		Matrix4x4 cameraMatrix = MakeAffineMatrix({1.0f, 1.0f, 1.0f}, cameraRotate, cameraPosition);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveMatrix(0.45f, float(kWindowWidth) / float(kWindoweHeight), 0.1f, 100.0f);
		Matrix4x4 viewProjectionMatrix = Multiply(viewMatrix, projectionMatrix);
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindoweHeight), 0.0f, 1.0f);

		debugCamera_->Update();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(viewProjectionMatrix, viewportMatrix);
	
		
		DrawSphere(sphere1, viewProjectionMatrix, viewportMatrix, color);
		DrawSphere(sphere2, viewProjectionMatrix, viewportMatrix, BLACK);

		

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
	delete debugCamera_;
	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
