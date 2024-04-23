#include <Novice.h>

const char kWindowTitle[] = "GC2B_15_ヒラジマ_ヒデマサ＿MT3";

struct Matrix4x4 {
	float m[4][4];
};
/// <summary>
/// 加法
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <returns></returns>
Matrix4x4 Add(Matrix4x4 a,Matrix4x4 b) { 
	Matrix4x4 result{};
	result.m[0][0]=a.m[0][0] + b.m[0][0];
	result.m[0][1]=a.m[0][1] + b.m[0][1];
	result.m[0][2]=a.m[0][2] + b.m[0][2];
	result.m[0][3]=a.m[0][3] + b.m[0][3];
	result.m[1][0]=a.m[1][0] + b.m[1][0];
	result.m[1][1]=a.m[1][1] + b.m[1][1];
	result.m[1][2]=a.m[1][2] + b.m[1][2];
	result.m[1][3]=a.m[1][3] + b.m[1][3];
	result.m[2][0]=a.m[2][0] + b.m[2][0];
	result.m[2][1]=a.m[2][1] + b.m[2][1];
	result.m[2][2]=a.m[2][2] + b.m[2][2];
	result.m[2][3]=a.m[2][3] + b.m[2][3];
	result.m[3][0]=a.m[3][0] + b.m[3][0];
	result.m[3][1]=a.m[3][1] + b.m[3][1];
	result.m[3][2]=a.m[3][2] + b.m[3][2];
	result.m[3][3]=a.m[3][3] + b.m[3][3];
	return result;
};
/// <summary>
/// 減法
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <returns></returns>
Matrix4x4 Subtraction(Matrix4x4 a, Matrix4x4 b) {
	Matrix4x4 result{};
	result.m[0][0] = a.m[0][0] - b.m[0][0];
	result.m[0][1] = a.m[0][1] - b.m[0][1];
	result.m[0][2] = a.m[0][2] - b.m[0][2];
	result.m[0][3] = a.m[0][3] - b.m[0][3];
	result.m[1][0] = a.m[1][0] - b.m[1][0];
	result.m[1][1] = a.m[1][1] - b.m[1][1];
	result.m[1][2] = a.m[1][2] - b.m[1][2];
	result.m[1][3] = a.m[1][3] - b.m[1][3];
	result.m[2][0] = a.m[2][0] - b.m[2][0];
	result.m[2][1] = a.m[2][1] - b.m[2][1];
	result.m[2][2] = a.m[2][2] - b.m[2][2];
	result.m[2][3] = a.m[2][3] - b.m[2][3];
	result.m[3][0] = a.m[3][0] - b.m[3][0];
	result.m[3][1] = a.m[3][1] - b.m[3][1];
	result.m[3][2] = a.m[3][2] - b.m[3][2];
	result.m[3][3] = a.m[3][3] - b.m[3][3];
	return result;
};
/// <summary>
/// スカラー
/// </summary>
/// <param name="a"></param>
/// <param name="k"></param>
/// <returns></returns>
Matrix4x4 Scalar(Matrix4x4 a, float k) {
	Matrix4x4 result{};
	result.m[0][0] = a.m[0][0] * k;
	result.m[0][1] = a.m[0][1] * k;
	result.m[0][2] = a.m[0][2] * k;
	result.m[0][3] = a.m[0][3] * k;
	result.m[1][0] = a.m[1][0] * k;
	result.m[1][1] = a.m[1][1] * k;
	result.m[1][2] = a.m[1][2] * k;
	result.m[1][3] = a.m[1][3] * k;
	result.m[2][0] = a.m[2][0] * k;
	result.m[2][1] = a.m[2][1] * k;
	result.m[2][2] = a.m[2][2] * k;
	result.m[2][3] = a.m[2][3] * k;
	result.m[3][0] = a.m[3][0] * k;
	result.m[3][1] = a.m[3][1] * k;
	result.m[3][2] = a.m[3][2] * k;
	result.m[3][3] = a.m[3][3] * k;
	return result;
};
/// <summary>
/// 単位行列
/// </summary>
/// <param name="a"></param>
/// <returns></returns>
Matrix4x4 MakeIdentity (Matrix4x4 a) {
	Matrix4x4 result{};
	result.m[0][0] = 1;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;
	result.m[1][0] = 0;
	result.m[1][1] = 1;
	result.m[1][2] = 0;
	result.m[1][3] = 0;
	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = 1;
	result.m[2][3] = 0;
	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;
	return result;
};
Matrix4x4 Multiplication(Matrix4x4 a, Matrix4x4 b) { 
	Matrix4x4 result{};
	result.m[0][0] = a.m[0][0]*b.m[0][0] + a.m[0][1]*b.m[1][0] + a.m[0][2]*b.m[2][0] + a.m[0][3]*b.m[3][0];//ｍｔ資料1列
	result.m[0][1] = a.m[0][0]*b.m[0][1] + a.m[0][1]*b.m[1][1] + a.m[0][2]*b.m[2][1] + a.m[0][3]*b.m[3][1];//2列
	result.m[0][2] = a.m[0][0]*b.m[0][2] + a.m[0][1]*b.m[1][2] + a.m[0][2]*b.m[2][2] + a.m[0][3]*b.m[3][2];//3列
	result.m[0][3] = a.m[0][0]*b.m[0][3] + a.m[0][1]*b.m[1][3] + a.m[0][2]*b.m[2][3] + a.m[0][3]*b.m[3][3];//4列

	result.m[1][0] = a.m[1][0]*b.m[0][0] + a.m[1][1]*b.m[1][0] + a.m[1][2]*b.m[2][0] + a.m[1][3]*b.m[3][0];//1
	result.m[1][1] = a.m[1][0]*b.m[0][1] + a.m[1][1]*b.m[1][1] + a.m[1][2]*b.m[2][1] + a.m[1][3]*b.m[3][1];//2列
	result.m[1][2] = a.m[1][0]*b.m[0][2] + a.m[1][1]*b.m[1][2] + a.m[1][2]*b.m[2][2] + a.m[1][3]*b.m[3][2];//3列
	result.m[1][3] = a.m[1][0]*b.m[0][3] + a.m[1][1]*b.m[1][3] + a.m[1][2]*b.m[2][3] + a.m[1][3]*b.m[3][3];//4列

	result.m[2][0] = a.m[2][0]*b.m[0][0] + a.m[2][1]*b.m[1][0] + a.m[2][2]*b.m[2][0] + a.m[2][3]*b.m[3][0];//1
	result.m[2][1] = a.m[2][0]*b.m[0][1] + a.m[2][1]*b.m[1][1] + a.m[2][2]*b.m[2][1] + a.m[2][3]*b.m[3][1];//2列
	result.m[2][2] = a.m[2][0]*b.m[0][2] + a.m[2][1]*b.m[1][2] + a.m[2][2]*b.m[2][2] + a.m[2][3]*b.m[3][2];//3列
	result.m[2][3] = a.m[2][0]*b.m[0][3] + a.m[2][1]*b.m[1][3] + a.m[2][2]*b.m[2][3] + a.m[2][3]*b.m[3][3];//4列

	result.m[3][0] = a.m[3][0]*b.m[0][0] + a.m[3][1]*b.m[1][0] + a.m[3][2]*b.m[2][0] + a.m[3][3]*b.m[3][0];//1
	result.m[3][1] = a.m[3][0]*b.m[0][1] + a.m[3][1]*b.m[1][1] + a.m[3][2]*b.m[2][1] + a.m[3][3]*b.m[3][1];//2列
	result.m[3][2] = a.m[3][0]*b.m[0][2] + a.m[3][1]*b.m[1][2] + a.m[3][2]*b.m[2][2] + a.m[3][3]*b.m[3][2];//3列
	result.m[3][3] = a.m[3][0]*b.m[0][3] + a.m[3][1]*b.m[1][3] + a.m[3][2]*b.m[2][3] + a.m[3][3]*b.m[3][3];//4列
	return result;
}
Matrix4x4 Inverse(Matrix4x4 a, Matrix4x4 b) { 
	Matrix4x4 result{};
	result.m[0][0] =  a.m[1][1]*a.m[2][2]*a.m[3][3] + a.m[1][2]*a.m[2][3]*a.m[3][1] + a.m[1][3]*a.m[2][1]*a.m[3][2] 
		            - a.m[1][3]*a.m[2][2]*a.m[3][1] - a.m[1][2]*a.m[2][1]*a.m[3][3] - a.m[1][1]*a.m[2][3]*a.m[3][2];
	result.m[0][1] = -a.m[0][1]*a.m[2][2]*a.m[3][3] - a.m[0][2]*a.m[2][3]*a.m[3][1] - a.m[0][3]*a.m[2][1]*a.m[3][2] 
		            + a.m[1][3]*a.m[2][2]*a.m[3][1] + a.m[0][2]*a.m[2][1]*a.m[3][3] + a.m[0][1]*a.m[2][3]*a.m[3][2];
	result.m[0][2] =  a.m[0][1]*a.m[1][2]*a.m[3][3] + a.m[0][2]*a.m[1][3]*a.m[3][1] + a.m[0][3]*a.m[1][1]*a.m[3][2] 
		            - a.m[1][3]*a.m[1][2]*a.m[3][1] - a.m[0][2]*a.m[1][1]*a.m[3][3] - a.m[0][1]*a.m[1][3]*a.m[3][2];
	result.m[0][3] = -a.m[0][1]*a.m[1][2]*a.m[2][3] - a.m[0][2]*a.m[1][3]*a.m[2][1] - a.m[0][3]*a.m[1][1]*a.m[2][2] 
		            + a.m[1][3]*a.m[1][2]*a.m[2][1] + a.m[0][2]*a.m[1][1]*a.m[2][3] + a.m[0][1]*a.m[1][3]*a.m[2][2];

	result.m[1][0] =  a.m[1][1]*a.m[2][2]*a.m[3][3] + a.m[1][2]*a.m[2][3]*a.m[3][1] + a.m[1][3]*a.m[2][0]*a.m[3][2] 
		            - a.m[1][3]*a.m[2][2]*a.m[3][0] - a.m[1][2]*a.m[2][0]*a.m[3][3] - a.m[1][1]*a.m[2][3]*a.m[3][2];
	result.m[1][1] = -a.m[0][1]*a.m[2][2]*a.m[3][3] - a.m[0][2]*a.m[2][3]*a.m[3][1] - a.m[0][3]*a.m[2][0]*a.m[3][2] 
		            + a.m[1][3]*a.m[2][2]*a.m[3][0] + a.m[0][2]*a.m[2][0]*a.m[3][3] + a.m[0][1]*a.m[2][3]*a.m[3][2];
	result.m[1][2] =  a.m[0][1]*a.m[1][2]*a.m[3][3] + a.m[0][2]*a.m[1][3]*a.m[3][1] + a.m[0][3]*a.m[1][0]*a.m[3][2] 
		            - a.m[1][3]*a.m[1][2]*a.m[3][0] - a.m[0][2]*a.m[1][0]*a.m[3][3] - a.m[0][1]*a.m[1][3]*a.m[3][2];
	result.m[1][3] = -a.m[0][1]*a.m[1][2]*a.m[2][3] - a.m[0][2]*a.m[1][3]*a.m[2][1] - a.m[0][3]*a.m[1][0]*a.m[2][2] 
		            + a.m[1][3]*a.m[1][2]*a.m[2][0] + a.m[0][2]*a.m[1][0]*a.m[2][3] + a.m[0][1]*a.m[1][3]*a.m[2][2];

	result.m[2][0] =  a.m[1][0]*a.m[2][1]*a.m[3][3] + a.m[1][1]*a.m[2][3]*a.m[3][0] + a.m[1][3]*a.m[2][0]*a.m[3][1] 
		            - a.m[1][3]*a.m[2][1]*a.m[3][0] - a.m[1][1]*a.m[2][0]*a.m[3][3] - a.m[1][0]*a.m[2][3]*a.m[3][1];
	result.m[2][1] = -a.m[0][0]*a.m[2][1]*a.m[3][3] - a.m[0][1]*a.m[2][3]*a.m[3][0] - a.m[0][3]*a.m[2][0]*a.m[3][1] 
		            + a.m[1][3]*a.m[2][1]*a.m[3][0] + a.m[0][1]*a.m[2][0]*a.m[3][3] + a.m[0][0]*a.m[2][3]*a.m[3][1];
	result.m[2][2] =  a.m[0][0]*a.m[1][1]*a.m[3][3] + a.m[0][1]*a.m[1][3]*a.m[3][0] + a.m[0][3]*a.m[1][0]*a.m[3][1] 
		            - a.m[1][3]*a.m[1][1]*a.m[3][0] - a.m[0][1]*a.m[1][0]*a.m[3][3] - a.m[0][0]*a.m[1][3]*a.m[3][1];
	result.m[2][3] = -a.m[0][0]*a.m[1][1]*a.m[2][3] - a.m[0][1]*a.m[1][3]*a.m[2][0] - a.m[0][3]*a.m[1][0]*a.m[2][1] 
		            + a.m[1][3]*a.m[1][1]*a.m[2][0] + a.m[0][1]*a.m[1][0]*a.m[2][3] + a.m[0][0]*a.m[1][3]*a.m[2][1];

	result.m[3][0] =  a.m[1][0]*a.m[2][1]*a.m[3][2] + a.m[1][1]*a.m[2][2]*a.m[3][0] + a.m[1][2]*a.m[2][0]*a.m[3][1] 
		            - a.m[1][2]*a.m[2][1]*a.m[3][0] - a.m[1][1]*a.m[2][0]*a.m[3][2] - a.m[1][0]*a.m[2][2]*a.m[3][1];
	result.m[3][1] = -a.m[0][0]*a.m[2][1]*a.m[3][2] - a.m[0][1]*a.m[2][2]*a.m[3][0] - a.m[0][2]*a.m[2][0]*a.m[3][1] 
		            + a.m[0][2]*a.m[2][1]*a.m[3][0] + a.m[0][1]*a.m[2][0]*a.m[3][2] + a.m[0][0]*a.m[2][2]*a.m[3][1];
	result.m[3][2] =  a.m[0][0]*a.m[1][1]*a.m[3][2] + a.m[0][1]*a.m[1][2]*a.m[3][0] + a.m[0][2]*a.m[1][0]*a.m[3][1] 
		            - a.m[0][2]*a.m[1][1]*a.m[3][0] - a.m[0][1]*a.m[1][0]*a.m[3][2] - a.m[0][0]*a.m[1][2]*a.m[3][1];
	result.m[3][3] = -a.m[0][0]*a.m[1][1]*a.m[2][2] - a.m[0][1]*a.m[1][2]*a.m[2][0] - a.m[0][2]*a.m[1][0]*a.m[2][1] 
		            + a.m[0][2]*a.m[1][1]*a.m[2][0] + a.m[0][1]*a.m[1][0]*a.m[2][2] + a.m[0][0]*a.m[1][2]*a.m[2][1];

    return result;
}
Matrix4x4 Transpose(const Matrix4x4 a) { 
	Matrix4x4 retult{};
	retult





}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

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

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

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
