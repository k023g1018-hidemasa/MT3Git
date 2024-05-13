#include <Novice.h>

const char kWindowTitle[] = "GC2B_15_ヒラジマ_ヒデマサ＿MT3";

static const int kRowHeight = 20;
static const int kColumnWidth = 60;


struct Matrix4x4 {
	float m[4][4];
};
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix,const char* ladel) { 
	Novice::ScreenPrintf(x, y - 20, "%s", ladel);
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight, "%6.02f", matrix.m[row][column]);
		}
	}

}
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
Matrix4x4 MakeIdentity () {
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
Matrix4x4 Inverse(Matrix4x4 a) { 
	Matrix4x4 result{};
	result.m[0][0] =  a.m[1][1]*a.m[2][2]*a.m[3][3] + a.m[1][2]*a.m[2][3]*a.m[3][1] + a.m[1][3]*a.m[2][1]*a.m[3][2] 
		            - a.m[1][3]*a.m[2][2]*a.m[3][1] - a.m[1][2]*a.m[2][1]*a.m[3][3] - a.m[1][1]*a.m[2][3]*a.m[3][2];
	result.m[0][1] = -a.m[0][1]*a.m[2][2]*a.m[3][3] - a.m[0][2]*a.m[2][3]*a.m[3][1] - a.m[0][3]*a.m[2][1]*a.m[3][2] 
		            + a.m[1][3]*a.m[2][2]*a.m[3][1] + a.m[0][2]*a.m[2][1]*a.m[3][3] + a.m[0][1]*a.m[2][3]*a.m[3][2];
	result.m[0][2] =  a.m[0][1]*a.m[1][2]*a.m[3][3] + a.m[0][2]*a.m[1][3]*a.m[3][1] + a.m[0][3]*a.m[1][1]*a.m[3][2] 
		            - a.m[1][3]*a.m[1][2]*a.m[3][1] - a.m[0][2]*a.m[1][1]*a.m[3][3] - a.m[0][1]*a.m[1][3]*a.m[3][2];
	result.m[0][3] = -a.m[0][1]*a.m[1][2]*a.m[2][3] - a.m[0][2]*a.m[1][3]*a.m[2][1] - a.m[0][3]*a.m[1][1]*a.m[2][2] 
		            + a.m[1][3]*a.m[1][2]*a.m[2][1] + a.m[0][2]*a.m[1][1]*a.m[2][3] + a.m[0][1]*a.m[1][3]*a.m[2][2];

	result.m[1][0] = - a.m[1][1]*a.m[2][2]*a.m[3][3] - a.m[1][2]*a.m[2][3]*a.m[3][1] - a.m[1][3]*a.m[2][0]*a.m[3][2] 
		              +a.m[1][3]*a.m[2][2]*a.m[3][0] + a.m[1][2]*a.m[2][0]*a.m[3][3] + a.m[1][1]*a.m[2][3]*a.m[3][2];
	result.m[1][1] = + a.m[0][1]*a.m[2][2]*a.m[3][3] + a.m[0][2]*a.m[2][3]*a.m[3][1] + a.m[0][3]*a.m[2][0]*a.m[3][2] 
		            -  a.m[1][3]*a.m[2][2]*a.m[3][0] - a.m[0][2]*a.m[2][0]*a.m[3][3] - a.m[0][1]*a.m[2][3]*a.m[3][2];
	result.m[1][2] = - a.m[0][1]*a.m[1][2]*a.m[3][3] - a.m[0][2]*a.m[1][3]*a.m[3][1] - a.m[0][3]*a.m[1][0]*a.m[3][2] 
		            +  a.m[1][3]*a.m[1][2]*a.m[3][0] + a.m[0][2]*a.m[1][0]*a.m[3][3] + a.m[0][1]*a.m[1][3]*a.m[3][2];
	result.m[1][3] = + a.m[0][1]*a.m[1][2]*a.m[2][3] + a.m[0][2]*a.m[1][3]*a.m[2][1] + a.m[0][3]*a.m[1][0]*a.m[2][2] 
		            -  a.m[1][3]*a.m[1][2]*a.m[2][0] - a.m[0][2]*a.m[1][0]*a.m[2][3] - a.m[0][1]*a.m[1][3]*a.m[2][2];

	result.m[2][0] =  a.m[1][0]*a.m[2][1]*a.m[3][3] + a.m[1][1]*a.m[2][3]*a.m[3][0] + a.m[1][3]*a.m[2][0]*a.m[3][1] 
		            - a.m[1][3]*a.m[2][1]*a.m[3][0] - a.m[1][1]*a.m[2][0]*a.m[3][3] - a.m[1][0]*a.m[2][3]*a.m[3][1];
	result.m[2][1] = -a.m[0][0]*a.m[2][1]*a.m[3][3] - a.m[0][1]*a.m[2][3]*a.m[3][0] - a.m[0][3]*a.m[2][0]*a.m[3][1] 
		            + a.m[1][3]*a.m[2][1]*a.m[3][0] + a.m[0][1]*a.m[2][0]*a.m[3][3] + a.m[0][0]*a.m[2][3]*a.m[3][1];
	result.m[2][2] =  a.m[0][0]*a.m[1][1]*a.m[3][3] + a.m[0][1]*a.m[1][3]*a.m[3][0] + a.m[0][3]*a.m[1][0]*a.m[3][1] 
		            - a.m[1][3]*a.m[1][1]*a.m[3][0] - a.m[0][1]*a.m[1][0]*a.m[3][3] - a.m[0][0]*a.m[1][3]*a.m[3][1];
	result.m[2][3] = -a.m[0][0]*a.m[1][1]*a.m[2][3] - a.m[0][1]*a.m[1][3]*a.m[2][0] - a.m[0][3]*a.m[1][0]*a.m[2][1] 
		            + a.m[1][3]*a.m[1][1]*a.m[2][0] + a.m[0][1]*a.m[1][0]*a.m[2][3] + a.m[0][0]*a.m[1][3]*a.m[2][1];

	result.m[3][0] = -a.m[1][0]*a.m[2][1]*a.m[3][2] - a.m[1][1]*a.m[2][2]*a.m[3][0] - a.m[1][2]*a.m[2][0]*a.m[3][1] 
		            + a.m[1][2]*a.m[2][1]*a.m[3][0] + a.m[1][1]*a.m[2][0]*a.m[3][2] + a.m[1][0]*a.m[2][2]*a.m[3][1];
	result.m[3][1] = +a.m[0][0]*a.m[2][1]*a.m[3][2] + a.m[0][1]*a.m[2][2]*a.m[3][0] + a.m[0][2]*a.m[2][0]*a.m[3][1] 
		            - a.m[0][2]*a.m[2][1]*a.m[3][0] - a.m[0][1]*a.m[2][0]*a.m[3][2] - a.m[0][0]*a.m[2][2]*a.m[3][1];
	result.m[3][2] = -a.m[0][0]*a.m[1][1]*a.m[3][2] - a.m[0][1]*a.m[1][2]*a.m[3][0] - a.m[0][2]*a.m[1][0]*a.m[3][1] 
		             +a.m[0][2]*a.m[1][1]*a.m[3][0] + a.m[0][1]*a.m[1][0]*a.m[3][2] + a.m[0][0]*a.m[1][2]*a.m[3][1];
	result.m[3][3] = +a.m[0][0]*a.m[1][1]*a.m[2][2] + a.m[0][1]*a.m[1][2]*a.m[2][0] + a.m[0][2]*a.m[1][0]*a.m[2][1] 
		            - a.m[0][2]*a.m[1][1]*a.m[2][0] - a.m[0][1]*a.m[1][0]*a.m[2][2] - a.m[0][0]*a.m[1][2]*a.m[2][1];
	//10ページのAをあたまにいれて今作ってるやつはA()でおけ
    return result;
}
/// <summary>
/// 転置行列
/// </summary>
/// <param name="a"></param>
/// <returns></returns>
Matrix4x4 Transpose(const Matrix4x4 a) { //12コイル
	Matrix4x4 retult{};
	retult.m[1][0] =a.m[0][1] ;
	retult.m[2][1] = a.m[1][2];
	retult.m[3][2] = a.m[2][3];
	retult.m[2][0] = a.m[0][2];
	retult.m[3][0] = a.m[0][3];
	retult.m[3][1] = a.m[1][3];

	retult.m[0][1] = a.m[1][0];
	retult.m[1][2] = a.m[2][1];
	retult.m[2][3] = a.m[3][2];
	retult.m[0][2] = a.m[2][0];
	retult.m[0][3] = a.m[3][0];
	retult.m[1][3] = a.m[3][1];
	return retult;
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};
	Matrix4x4 m1 = {
		3.2f,0.7f,9.6f,4.4f,
	    5.5f,1.3f,7.8f,2.1f,
        6.9f,8.0f,2.6f,1.0f,	
	    0.5f,7.2f,5.1f,3.3f,
	};
	Matrix4x4 m2 = {
		4.1f,6.5f,3.3f,2.2f,
		8.8f,0.6f,9.9f,7.7f,
		1.1f,5.5f,6.6f,0.0f,
		3.3f,9.9f,8.8f,2.2f,
	};

	Matrix4x4 resultAdd = Add(m1, m2);
	Matrix4x4 resultMultiply = Multiplication(m1, m2);
	Matrix4x4 resultSubtract = Subtraction(m1, m2);
	Matrix4x4 inverseM1 = Inverse(m1);
	Matrix4x4 invarseM2 = Inverse(m2);
	Matrix4x4 transposeM1 = Transpose(m1);
	Matrix4x4 transposeM2 = Transpose(m2);
	Matrix4x4 identity = MakeIdentity();


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
		
	MatrixScreenPrintf(0, 0+20, resultAdd, " Add");
		MatrixScreenPrintf(0, kRowHeight * 5 + 20, resultSubtract, "Subtract");
	MatrixScreenPrintf(0, kRowHeight * 5 * 2 + 20, resultMultiply, "Multiply");
		MatrixScreenPrintf(0, kRowHeight * 5 * 3 + 20, inverseM1, "inverseM1");
	MatrixScreenPrintf(0, kRowHeight * 5 * 4 + 20, invarseM2, "inverseM2");
		MatrixScreenPrintf(kColumnWidth * 5, 0+20, transposeM1, "transposeM1");
	MatrixScreenPrintf(kColumnWidth * 5, kRowHeight * 5 + 20, transposeM2, "transposeM2");
	MatrixScreenPrintf(kColumnWidth * 5, kRowHeight * 5 * 2 + 20, identity, "identity");

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
