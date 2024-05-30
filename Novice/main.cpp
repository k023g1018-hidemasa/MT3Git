#include <Novice.h>
#include"MTFunction.h"

const char kWindowTitle[] = "GC2B_15_ヒラジマ_ヒデマサ＿MT3";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};


	Vector3 v1{1.2f, -3.9f, 2.5f};
	Vector3 v2{2.8f, 0.4f, -1.3f};
	Vector3 cross = Cross(v1, v2);

	Vector3 rotate{};//ゼロで初期化
	Vector3 translate{100.0f, 100.0f, 100.0f};
	Vector3 cameraPosition{1.0f,1.0f,1.0f};//多分ALとのこと,なかった//ここは多分前後に動いたときの変数
	Vector3 kLocalVertices[3]{300.0f, 600.0f, 100.0f,//ここを回転させるときに動く多分最初は定数でヨシ
		100.0f, 300.0f, 300.0f, 
		600.0f, 300.0f, 600.0f};
	



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
	//	Matrix4x4 worldMatrix = MakeAffineMatrix({1.0f, 1.0f, 1.0f}, rotate, translate);
	//	Matrix4x4 cameraMatrix = MakeAffineMatrix({1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, 1);
		if (keys[DIK_A]) {
			rotate.x += 0.01f;
		    rotate.y += 0.01f;
		    rotate.z += 0.01f;
		}else if (keys[DIK_D]) {
			rotate.x -= 0.01f;
		    rotate.y -= 0.01f;
		    rotate.z -= 0.01f;
		}
		if (keys[DIK_W]) {
			translate.x += 3;
			translate.y += 3;
			translate.z += 3;
		} else if (keys[DIK_S]) {
			translate.x -= 3;
			translate.y -= 3;
			translate.z -= 3;
		}

	Matrix4x4 worldMatrix = MakeAffineMatrix({1.0f, 1.0f, 1.0f}, rotate, translate);
	Matrix4x4 cameraMatrix = MakeAffineMatrix({1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, cameraPosition);
	Matrix4x4 viewMatrix = Inverse(cameraMatrix);
	Matrix4x4 projectionMatrix = MakePerspectiveMatrix(0.45f, float(kWindowWidth) / float(kWindoweHeight), 0.1f, 100.0f);
	Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
	Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindoweHeight), 0.0f, 1.0f);
	Vector3 screenVertices[3];
	for (uint32_t i = 0; i < 3; ++i) {
		Vector3 ndcVertex = Transform(kLocalVertices[i], worldViewProjectionMatrix);
		screenVertices[i] = Transform(ndcVertex, viewportMatrix);
	}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		VectorScreenPrintf(0, 0, cross, "Cross");

		Novice::DrawTriangle(
		    int(screenVertices[0].x), int(screenVertices[0].y), int(screenVertices[1].x), int(screenVertices[1].y)
			,int(screenVertices[2].x),int(screenVertices[2].y),RED,kFillModeSolid
		);
		Novice::DrawTriangle(
		    300, 300,
			100, 300,
			600, 300,
			RED, kFillModeSolid
		);

		Novice::ScreenPrintf(50, 50, "%d,%d,%d,%d,%d,%d",
			int(screenVertices[0].x), int(screenVertices[0].y),
			int(screenVertices[1].x), int(screenVertices[1].y),
			int(screenVertices[2].x),int(screenVertices[2].y)
		);
		VectorScreenPrintf(90, 90, rotate, "rotate");
		VectorScreenPrintf(90, 90*2, translate, "translate");
		//Novice::ScreenPrintf(70, 70, "wMatrix%d  cameraMatrix;%d viewMatrix%d", worldMatrix, cameraMatrix, viewMatrix);
		/*MatrixScreenPrintf(50, 90, worldMatrix, " worldMatrix");
		MatrixScreenPrintf(50, 90*2, cameraMatrix, "cameraMatrix");
		MatrixScreenPrintf(50, 90*3, viewMatrix, " viewMatrix");*/
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
