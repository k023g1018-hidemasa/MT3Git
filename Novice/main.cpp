#include "ImGuiManager.h"
#include "MTFunction.h"
#include <Novice.h>
#include <cmath>
// #include"ViewProjection.h"

const char kWindowTitle[] = "GC2B_15_ヒラジマ_ヒデマサ＿MT3";

bool PlaneIsCollision(const Sphere& sphere, const Plane& plane) {
	float d = plane.distance;
	// nが法線の向き？ならｄはｎじゃないの？
	Vector3 n = plane.normal;

	Vector3 c = sphere.center;
	float k; // 平面と中心点の距離らしい
	k =  Dot(n,c)-d;
	// ここの変換てどうすんの｜中身↑｜らしいから多分返還しろってこと
	// 関数の中身知るかヴォケお前らみたいに脳みそ詰まってないんじゃ人のことも考えろや自己中どもが

	return abs(k) <= sphere.radius;
	// 焼身
}

void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4 viewportMatrix, uint32_t color) {
	Vector3 center = Scale(plane.distance, plane.normal); // 変換がない何処にかいてんねん
	Vector3 perpendicular[4];
	perpendicular[0] = Normalize(Perpendicular(plane.normal));
	perpendicular[1] = {-perpendicular[0].x, -perpendicular[0].y, -perpendicular[0].z};
	perpendicular[2] = Cross(plane.normal, perpendicular[0]);
	perpendicular[3] = {-perpendicular[2].x, -perpendicular[2].y, -perpendicular[2].z};

	Vector3 points[4];
	for (int32_t i = 0; i < 4; ++i) {
		Vector3 extend = Scale(2.0f, perpendicular[i]);
		Vector3 point = Add(center, extend);
		points[i] = Transform(Transform(point, viewProjectionMatrix), viewportMatrix);
	}
	Novice::DrawLine(int(points[3].x), int(points[3].y), int(points[1].x), int(points[1].y), color);
	Novice::DrawLine(int(points[0].x), int(points[0].y), int(points[2].x), int(points[2].y), color);
	Novice::DrawLine(int(points[0].x), int(points[0].y), int(points[3].x), int(points[3].y), color);
	Novice::DrawLine(int(points[2].x), int(points[2].y), int(points[1].x), int(points[1].y), color);
	// mazuuturan
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

	Vector3 a = {1, 1, 0};
	Vector3 b = {0.5, 0.5, 0};
	Vector3 c = {0, 1, 0};
	Vector3 v1 = Subtract(b, a);
	Vector3 v2 = Subtract(c, b);

	Sphere sphere1 = {{}, 0.5f};
	Sphere sphere2 = {{}, 0.3f};
	Plane plane = {Cross(v1, v2), 0.5f};
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

		if (PlaneIsCollision(sphere1, plane)) {
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
		// DrawSphere(sphere2, viewProjectionMatrix, viewportMatrix, BLACK);
		DrawPlane(plane, viewProjectionMatrix, viewportMatrix, RED);

		ImGui::Begin("Window");
		ImGui::DragFloat3("Sphere1 Tranlate", &sphere1.center.x, 0.01f);
		ImGui::End();

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
