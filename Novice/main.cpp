#include <Novice.h>
#include"MTFunction.h"

const char kWindowTitle[] = "GC2B_15_ヒラジマ_ヒデマサ＿MT3";

struct Segment {
	Vector3 origin;//視点
	Vector3 diff;//終点への差分ベクトル
};
//正射影ベクトル
Vector3 Project(const Vector3& v1, const Vector3& v2){
	//正射影ベクトル
	//おいｃどっから出すねんabcなんか知るかｘｙｚで書いてくれ

	float bNol = 1;
	float aNol = 1;//数字は適当
	float cNol = aNol * std::cos(site); // シータはroateになるからｖ1？
	//テンって×だっけ？//ちゃうわこれｘｙ的な感じやった気がする
	float atenb = aNol * bNol * std::cos(site);
	cNol = atenb / bNol;
	//b^がノマラってのは分かるけど||b||と何が違うんや
	//てか普通のｃどっから北





};
//最近接点
Vector3 ClosestPoint(const Vector3& point, const Segment& segment){

	//cPoint=
		//ｔってのは距離？ってことは変数がいるけどセグメントのこと？
		//ｐ単体がおるけどｃｐとどう分けたらええねん



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
	Segment segment{
	    {-2.0f, -1.0f, 0.0f},
        {3.0f,  2.0f,  2.0f}
    };
	Vector3 point{-1.5f, 0.0f, 0.0f};
	Sphere sphere = {1.0f, 1.0f, 1.0f};
	1.0f;
	Vector3 project = Project(Subtract(point, segment.origin), segment.diff);
	Vector3 closetPoint = ClosestPoint(point, segment);

	Sphere pointSphere{point, 0.01f};
	Sphere closestPointSphere{closetPoint, 0.01f};
	uint32_t color = 0xafaaaaff;


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


		Matrix4x4 worldMatrix = MakeAffineMatrix({1.0f, 1.0f, 1.0f}, rotate, translate);
		Matrix4x4 cameraMatrix = MakeAffineMatrix({1.0f, 1.0f, 1.0f}, cameraRotate, cameraPosition);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveMatrix(0.45f, float(kWindowWidth) / float(kWindoweHeight), 0.1f, 100.0f);
		Matrix4x4 viewProjectionMatrix = Multiply(viewMatrix, projectionMatrix);
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindoweHeight), 0.0f, 1.0f);

	Vector3 start = Transform(Transform(segment.origin, viewProjectionMatrix), viewportMatrix);
		Vector3 end = Transform(Transform(Add(segment.origin, segment.diff), viewProjectionMatrix), viewportMatrix);




		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///


		Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), WHITE);




		DrawSphere(pointSphere,viewportMatrix,viewportMatrix,RED);
		DrawSphere(closestPointSphere, viewProjectionMatrix, viewportMatrix, BLACK);

		
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
