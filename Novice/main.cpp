#include "ImGuiManager.h"
#include "MTFunction.h"
#include <Novice.h>
// #include"ViewProjection.h"

const char kWindowTitle[] = "GC2B_15_ヒラジマ_ヒデマサ＿MT3";



struct Triangle {
	Vector3 vertices[3];
};
void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color){
	Vector3 screenVertices[3] = {
	    Transform(Transform(triangle.vertices[0], viewProjectionMatrix), viewportMatrix),
	    Transform(Transform(triangle.vertices[1], viewProjectionMatrix), viewportMatrix),
	    Transform(Transform(triangle.vertices[2], viewProjectionMatrix), viewportMatrix),
	};
	//この中で変換させる？
	Novice::DrawTriangle(
	    int(screenVertices[0].x), int(screenVertices[0].y),
		int(screenVertices[1].x),int(screenVertices[1].y),
		int(screenVertices[2].x),int(screenVertices[2].y),color,kFillModeWireFrame);
};
bool ToriangleIsCollision(const Triangle& triangle, const Segment& segment){
    Vector3 v01 = Subtract(triangle.vertices[1], triangle.vertices[0]);
	Vector3 v12 = Subtract(triangle.vertices[2], triangle.vertices[1]);
	Vector3 normal = Normalize(Cross(v01, v12));
	Plane plane{.normal = normal, .distance = Dot(triangle.vertices[0], normal)};
	float dot = Dot(plane.normal, segment.diff);
	if (dot == 0.0f) {
		return false;
	}
	float t = (plane.distance - Dot(segment.origin, plane.normal)) / dot;
	if ((t < 0) || (1 < t)) {
		return false;
	}
	Vector3 intersect = Add(segment.origin, Scale(t, segment.diff));
	Vector3 v1p = Subtract(intersect, triangle.vertices[1]);
	if (Dot(Cross(v01, v1p), normal) < 0.0f) {
		return false;
	}
	Vector3 v2p = Subtract(intersect, triangle.vertices[2]);
	if (Dot(Cross(v12, v2p), normal) < 0.0f) {
		return false;
	}
	Vector3 v0p = Subtract(intersect, triangle.vertices[0]);
	Vector3 v20 = Subtract(triangle.vertices[0], triangle.vertices[2]);
	if (Dot(Cross(v20, v0p), normal) < 0.0f) {
		return false;
	}
	return true;


};




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
	Triangle triangle={a,b,c};


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
		ImGui::DragFloat3("segment.Center", &segment.origin.x, 0.01f);
		ImGui::DragFloat3(" segment.Radius", &segment.diff.x, 0.01f);
		ImGui::DragFloat3("triangre.v0", &triangle.vertices[0].x, 0.01f);
		ImGui::DragFloat3("triangre.v1", &triangle.vertices[1].x, 0.01f);
		ImGui::DragFloat3("triangre.v2", &triangle.vertices[2].x, 0.01f);
		ImGui::End();
	

		Matrix4x4 worldMatrix = MakeAffineMatrix({1.0f, 1.0f, 1.0f}, rotate, translate);
		Matrix4x4 cameraMatrix = MakeAffineMatrix({1.0f, 1.0f, 1.0f}, cameraRotate, cameraPosition);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveMatrix(0.45f, float(kWindowWidth) / float(kWindoweHeight), 0.1f, 100.0f);
		Matrix4x4 viewProjectionMatrix = Multiply(viewMatrix, projectionMatrix);
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindoweHeight), 0.0f, 1.0f);

			if (ToriangleIsCollision(triangle, segment)) {
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
		DrawSegment(segment, viewProjectionMatrix, viewportMatrix, color);
		DrawTriangle(triangle, viewProjectionMatrix, viewportMatrix, WHITE);



		//DrawSphere(sphere1, viewProjectionMatrix, viewportMatrix, color);
		// DrawSphere(sphere2, viewProjectionMatrix, viewportMatrix, BLACK);
		//DrawPlane(plane, viewProjectionMatrix, viewportMatrix, WHITE);

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