#include "ImGuiManager.h"
#include "MTFunction.h"
#include <Novice.h>
// #include"ViewProjection.h"

const char kWindowTitle[] = "GC2B_15_ヒラジマ_ヒデマサ＿MT3";




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
	// Sphere sphere2 = {{}, 0.3f};
	uint32_t color = WHITE;

	Vector3 a = {1, 1, 0};
	Vector3 b = {0.5, 0.5, 0};
	Vector3 c = {0, 1, 0};
	Vector3 v1 = Subtract(b, a);
	Vector3 v2 = Subtract(c, b);
	Plane plane = {Cross(v1, v2), 0.5f};

	Segment segment{
	    {-2.0f, -1.0f, 0.0f},
        {3.0f,  2.0f,  2.0f}
    };
	Triangle triangle = {a, b, c};

	AABB aabb1 = {
	    {-0.5f,-0.5f, -0.5f},
	    {0.5f, 0.5f, 0.5f},
	};
	AABB aabb2 = {
	    {-0.4f,-0.4f,-0.5f},
        {0.6f,0.6f,0.5f},
    };

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

		ImGui::Begin("window");
		ImGui::DragFloat3("aabb1,min", &aabb1.min.x,0.01f);
		ImGui::DragFloat3("aabb1,max", &aabb1.max.x,0.01f);
		ImGui::DragFloat3("sphere.center", &sphere1.center.x,0.01f);
		ImGui::DragFloat("sphere.radius",  &sphere1.radius,0.01f);
		ImGui::End();

		aabb1.min.x = (std::min)(aabb1.min.x, aabb1.max.x);
		aabb1.min.y = (std::min)(aabb1.min.y, aabb1.max.y);
		aabb1.min.z = (std::min)(aabb1.min.z, aabb1.max.z);
		aabb1.max.x = (std::max)(aabb1.min.x, aabb1.max.x);
		aabb1.max.y = (std::max)(aabb1.min.y, aabb1.max.y);
		aabb1.max.z = (std::max)(aabb1.min.z, aabb1.max.z);

		



		Matrix4x4 worldMatrix = MakeAffineMatrix({1.0f, 1.0f, 1.0f}, rotate, translate);
		Matrix4x4 cameraMatrix = MakeAffineMatrix({1.0f, 1.0f, 1.0f}, cameraRotate, cameraPosition);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveMatrix(0.45f, float(kWindowWidth) / float(kWindoweHeight), 0.1f, 100.0f);
		Matrix4x4 viewProjectionMatrix = Multiply(viewMatrix, projectionMatrix);
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindoweHeight), 0.0f, 1.0f);

		if (AABBAndSphereIsCollision(aabb1,sphere1)) {
			color = RED;
		} else {
			color = WHITE;
		}
		debugCamera_->Update();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(viewProjectionMatrix, viewportMatrix);
		DrawAABB(aabb1, viewProjectionMatrix, viewportMatrix, color);
		//DrawAABB(aabb2, viewProjectionMatrix, viewportMatrix, WHITE);
		DrawSphere(sphere1, viewProjectionMatrix, viewportMatrix, WHITE);
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