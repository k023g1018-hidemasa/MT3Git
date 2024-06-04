#pragma once
#include <Novice.h>
#include<cmath>
#include<math.h>
#include<assert.h>

static const int kRowHeight = 20;
static const int kColumnWidth = 60;
static const int kWindowWidth = 128;
static const int kWindoweHeight = 72;

struct Matrix4x4 {
	float m[4][4];
};
struct Vector3 {
	float x, y, z;
//	Vector3 operator+=(const Vector3& obj) { // 機能の拡張をしてるからvectorの中に入れてヨシ
	//	Vector3 num{};
		//num.x = x + obj.x;
		//num.y = y + obj.y;
		//num.z = z + obj.z;

		//return num;
	//}
};

//void DrawTriangle(const Triangre& triangle,);

Vector3 Cross(const Vector3& v1, const Vector3& v2) {
	Vector3 resurt{};
	resurt.x = v1.y * v2.z - v1.z * v2.y;
	resurt.y = v1.z * v2.x - v1.x * v2.z;
	resurt.z = v1.x * v2.y - v1.y * v2.x;
	return resurt;
	
};

Matrix4x4 MakeRotateXMatrix(float radian) {
	Matrix4x4 result{};
	result.m[0][0] = 1;
	result.m[1][1] = std::cos(radian);
	result.m[1][2] = std::sin(radian);
	result.m[2][1] = -std::sin(radian);
	result.m[2][2] = std::cos(radian);
	result.m[3][3] = 1;
	return result;
};

Matrix4x4 MakeRotateYMatrix(float radian) {
	Matrix4x4 result{};
	result.m[0][0] = std::cos(radian);
	result.m[2][0] = std::sin(radian);
	result.m[0][2] = -std::sin(radian);
	result.m[1][1] = 1;
	result.m[2][2] = std::cos(radian);
	result.m[3][3] = 1;
	return result;
};

Matrix4x4 MakeRotateZMatrix(float radian) {
	Matrix4x4 result{};
	result.m[0][0] = std::cos(radian);
	result.m[0][1] = std::sin(radian);
	result.m[1][0] = -std::sin(radian);
	result.m[1][1] = std::cos(radian);
	result.m[2][2] = 1;
	result.m[3][3] = 1;

	return result;
};

Vector3 Add(const Vector3& v1, const Vector3& v2) {
	Vector3 result{};
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
};

Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
	Vector3 result{};
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
};

float Dot(const Vector3& v1, const Vector3& v2) {
	float result;
	result = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
	return result;
	
}

float Length(const Vector3& v) {
	float result;
	result = sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	return result;
	
}

Vector3 Normalize(const Vector3& v) {
	Vector3 result{};
	float mag = 1 / sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z)); /// 長さわる１してそれかける元の数
	result.x = mag * v.x;
	result.y = mag * v.y;
	result.z = mag * v.z;
	return result;

};

Matrix4x4 Inverse(Matrix4x4 a) {
	Matrix4x4 result{};
	float A =
	    1 /
	    (a.m[0][0] * a.m[1][1] * a.m[2][2] * a.m[3][3] + a.m[0][0] * a.m[1][2] * a.m[2][3] * a.m[3][1] + a.m[0][0] * a.m[1][3] * a.m[2][1] * a.m[3][2] - a.m[0][0] * a.m[1][3] * a.m[2][2] * a.m[3][1] -
	     a.m[0][0] * a.m[1][2] * a.m[2][1] * a.m[3][3] - a.m[0][0] * a.m[1][1] * a.m[2][3] * a.m[3][2] - a.m[0][1] * a.m[1][0] * a.m[2][2] * a.m[3][3] - a.m[0][2] * a.m[1][0] * a.m[2][3] * a.m[3][1] -
	     a.m[0][3] * a.m[1][0] * a.m[2][1] * a.m[3][2] + a.m[0][3] * a.m[1][0] * a.m[2][2] * a.m[3][1] + a.m[0][2] * a.m[1][0] * a.m[2][1] * a.m[3][3] + a.m[0][1] * a.m[1][0] * a.m[2][3] * a.m[3][2] +
	     a.m[0][1] * a.m[1][2] * a.m[2][0] * a.m[3][3] + a.m[0][2] * a.m[1][3] * a.m[2][0] * a.m[3][1] + a.m[0][3] * a.m[1][1] * a.m[2][0] * a.m[3][2] - a.m[0][3] * a.m[1][2] * a.m[2][0] * a.m[3][1] -
	     a.m[0][2] * a.m[1][1] * a.m[2][0] * a.m[3][3] - a.m[0][1] * a.m[1][3] * a.m[2][0] * a.m[3][2] - a.m[0][1] * a.m[1][2] * a.m[2][3] * a.m[3][0] - a.m[0][2] * a.m[1][3] * a.m[2][1] * a.m[3][0] -
	     a.m[0][3] * a.m[1][1] * a.m[2][2] * a.m[3][0] + a.m[0][3] * a.m[1][2] * a.m[2][1] * a.m[3][0] + a.m[0][2] * a.m[1][1] * a.m[2][3] * a.m[3][0] + a.m[0][1] * a.m[1][3] * a.m[2][2] * a.m[3][0]);

	result.m[0][0] = A * (a.m[1][1] * a.m[2][2] * a.m[3][3] + a.m[1][2] * a.m[2][3] * a.m[3][1] + a.m[1][3] * a.m[2][1] * a.m[3][2] - a.m[1][3] * a.m[2][2] * a.m[3][1] -
	                      a.m[1][2] * a.m[2][1] * a.m[3][3] - a.m[1][1] * a.m[2][3] * a.m[3][2]);
	result.m[0][1] = A * (-a.m[0][1] * a.m[2][2] * a.m[3][3] - a.m[0][2] * a.m[2][3] * a.m[3][1] - a.m[0][3] * a.m[2][1] * a.m[3][2] + a.m[0][3] * a.m[2][2] * a.m[3][1] +
	                      a.m[0][2] * a.m[2][1] * a.m[3][3] + a.m[0][1] * a.m[2][3] * a.m[3][2]);
	result.m[0][2] = A * (a.m[0][1] * a.m[1][2] * a.m[3][3] + a.m[0][2] * a.m[1][3] * a.m[3][1] + a.m[0][3] * a.m[1][1] * a.m[3][2] - a.m[0][3] * a.m[1][2] * a.m[3][1] -
	                      a.m[0][2] * a.m[1][1] * a.m[3][3] - a.m[0][1] * a.m[1][3] * a.m[3][2]);
	result.m[0][3] = A * (-a.m[0][1] * a.m[1][2] * a.m[2][3] - a.m[0][2] * a.m[1][3] * a.m[2][1] - a.m[0][3] * a.m[1][1] * a.m[2][2] + a.m[0][3] * a.m[1][2] * a.m[2][1] +
	                      a.m[0][2] * a.m[1][1] * a.m[2][3] + a.m[0][1] * a.m[1][3] * a.m[2][2]);

	result.m[1][0] = A * (-a.m[1][0] * a.m[2][2] * a.m[3][3] - a.m[1][2] * a.m[2][3] * a.m[3][0] - a.m[1][3] * a.m[2][0] * a.m[3][2] + a.m[1][3] * a.m[2][2] * a.m[3][0] +
	                      a.m[1][2] * a.m[2][0] * a.m[3][3] + a.m[1][0] * a.m[2][3] * a.m[3][2]);
	result.m[1][1] = A * (+a.m[0][0] * a.m[2][2] * a.m[3][3] + a.m[0][2] * a.m[2][3] * a.m[3][0] + a.m[0][3] * a.m[2][0] * a.m[3][2] - a.m[0][3] * a.m[2][2] * a.m[3][0] -
	                      a.m[0][2] * a.m[2][0] * a.m[3][3] - a.m[0][0] * a.m[2][3] * a.m[3][2]);
	result.m[1][2] = A * (-a.m[0][0] * a.m[1][2] * a.m[3][3] - a.m[0][2] * a.m[1][3] * a.m[3][0] - a.m[0][3] * a.m[1][0] * a.m[3][2] + a.m[0][3] * a.m[1][2] * a.m[3][0] +
	                      a.m[0][2] * a.m[1][0] * a.m[3][3] + a.m[0][0] * a.m[1][3] * a.m[3][2]);
	result.m[1][3] = A * (+a.m[0][0] * a.m[1][2] * a.m[2][3] + a.m[0][2] * a.m[1][3] * a.m[2][0] + a.m[0][3] * a.m[1][0] * a.m[2][2] - a.m[0][3] * a.m[1][2] * a.m[2][0] -
	                      a.m[0][2] * a.m[1][0] * a.m[2][3] - a.m[0][0] * a.m[1][3] * a.m[2][2]);

	result.m[2][0] = A * (a.m[1][0] * a.m[2][1] * a.m[3][3] + a.m[1][1] * a.m[2][3] * a.m[3][0] + a.m[1][3] * a.m[2][0] * a.m[3][1] - a.m[1][3] * a.m[2][1] * a.m[3][0] -
	                      a.m[1][1] * a.m[2][0] * a.m[3][3] - a.m[1][0] * a.m[2][3] * a.m[3][1]);
	result.m[2][1] = A * (-a.m[0][0] * a.m[2][1] * a.m[3][3] - a.m[0][1] * a.m[2][3] * a.m[3][0] - a.m[0][3] * a.m[2][0] * a.m[3][1] + a.m[0][3] * a.m[2][1] * a.m[3][0] +
	                      a.m[0][1] * a.m[2][0] * a.m[3][3] + a.m[0][0] * a.m[2][3] * a.m[3][1]);
	result.m[2][2] = A * (a.m[0][0] * a.m[1][1] * a.m[3][3] + a.m[0][1] * a.m[1][3] * a.m[3][0] + a.m[0][3] * a.m[1][0] * a.m[3][1] - a.m[0][3] * a.m[1][1] * a.m[3][0] -
	                      a.m[0][1] * a.m[1][0] * a.m[3][3] - a.m[0][0] * a.m[1][3] * a.m[3][1]);
	result.m[2][3] = A * (-a.m[0][0] * a.m[1][1] * a.m[2][3] - a.m[0][1] * a.m[1][3] * a.m[2][0] - a.m[0][3] * a.m[1][0] * a.m[2][1] + a.m[0][3] * a.m[1][1] * a.m[2][0] +
	                      a.m[0][1] * a.m[1][0] * a.m[2][3] + a.m[0][0] * a.m[1][3] * a.m[2][1]);

	result.m[3][0] = A * (-a.m[1][0] * a.m[2][1] * a.m[3][2] - a.m[1][1] * a.m[2][2] * a.m[3][0] - a.m[1][2] * a.m[2][0] * a.m[3][1] + a.m[1][2] * a.m[2][1] * a.m[3][0] +
	                      a.m[1][1] * a.m[2][0] * a.m[3][2] + a.m[1][0] * a.m[2][2] * a.m[3][1]);
	result.m[3][1] = A * (+a.m[0][0] * a.m[2][1] * a.m[3][2] + a.m[0][1] * a.m[2][2] * a.m[3][0] + a.m[0][2] * a.m[2][0] * a.m[3][1] - a.m[0][2] * a.m[2][1] * a.m[3][0] -
	                      a.m[0][1] * a.m[2][0] * a.m[3][2] - a.m[0][0] * a.m[2][2] * a.m[3][1]);
	result.m[3][2] = A * (-a.m[0][0] * a.m[1][1] * a.m[3][2] - a.m[0][1] * a.m[1][2] * a.m[3][0] - a.m[0][2] * a.m[1][0] * a.m[3][1] + a.m[0][2] * a.m[1][1] * a.m[3][0] +
	                      a.m[0][1] * a.m[1][0] * a.m[3][2] + a.m[0][0] * a.m[1][2] * a.m[3][1]);
	result.m[3][3] = A * (+a.m[0][0] * a.m[1][1] * a.m[2][2] + a.m[0][1] * a.m[1][2] * a.m[2][0] + a.m[0][2] * a.m[1][0] * a.m[2][1] - a.m[0][2] * a.m[1][1] * a.m[2][0] -
	                      a.m[0][1] * a.m[1][0] * a.m[2][2] - a.m[0][0] * a.m[1][2] * a.m[2][1]);
	// 10ページのAをあたまにいれて今作ってるやつはA()でおけ
	return result;
}

Matrix4x4 Multiply(Matrix4x4 a, Matrix4x4 b) {
	Matrix4x4 result{};
	result.m[0][0] = a.m[0][0] * b.m[0][0] + a.m[0][1] * b.m[1][0] + a.m[0][2] * b.m[2][0] + a.m[0][3] * b.m[3][0]; // ｍｔ資料1列
	result.m[0][1] = a.m[0][0] * b.m[0][1] + a.m[0][1] * b.m[1][1] + a.m[0][2] * b.m[2][1] + a.m[0][3] * b.m[3][1]; // 2列
	result.m[0][2] = a.m[0][0] * b.m[0][2] + a.m[0][1] * b.m[1][2] + a.m[0][2] * b.m[2][2] + a.m[0][3] * b.m[3][2]; // 3列
	result.m[0][3] = a.m[0][0] * b.m[0][3] + a.m[0][1] * b.m[1][3] + a.m[0][2] * b.m[2][3] + a.m[0][3] * b.m[3][3]; // 4列

	result.m[1][0] = a.m[1][0] * b.m[0][0] + a.m[1][1] * b.m[1][0] + a.m[1][2] * b.m[2][0] + a.m[1][3] * b.m[3][0]; // 1
	result.m[1][1] = a.m[1][0] * b.m[0][1] + a.m[1][1] * b.m[1][1] + a.m[1][2] * b.m[2][1] + a.m[1][3] * b.m[3][1]; // 2列
	result.m[1][2] = a.m[1][0] * b.m[0][2] + a.m[1][1] * b.m[1][2] + a.m[1][2] * b.m[2][2] + a.m[1][3] * b.m[3][2]; // 3列
	result.m[1][3] = a.m[1][0] * b.m[0][3] + a.m[1][1] * b.m[1][3] + a.m[1][2] * b.m[2][3] + a.m[1][3] * b.m[3][3]; // 4列

	result.m[2][0] = a.m[2][0] * b.m[0][0] + a.m[2][1] * b.m[1][0] + a.m[2][2] * b.m[2][0] + a.m[2][3] * b.m[3][0]; // 1
	result.m[2][1] = a.m[2][0] * b.m[0][1] + a.m[2][1] * b.m[1][1] + a.m[2][2] * b.m[2][1] + a.m[2][3] * b.m[3][1]; // 2列
	result.m[2][2] = a.m[2][0] * b.m[0][2] + a.m[2][1] * b.m[1][2] + a.m[2][2] * b.m[2][2] + a.m[2][3] * b.m[3][2]; // 3列
	result.m[2][3] = a.m[2][0] * b.m[0][3] + a.m[2][1] * b.m[1][3] + a.m[2][2] * b.m[2][3] + a.m[2][3] * b.m[3][3]; // 4列

	result.m[3][0] = a.m[3][0] * b.m[0][0] + a.m[3][1] * b.m[1][0] + a.m[3][2] * b.m[2][0] + a.m[3][3] * b.m[3][0]; // 1
	result.m[3][1] = a.m[3][0] * b.m[0][1] + a.m[3][1] * b.m[1][1] + a.m[3][2] * b.m[2][1] + a.m[3][3] * b.m[3][1]; // 2列
	result.m[3][2] = a.m[3][0] * b.m[0][2] + a.m[3][1] * b.m[1][2] + a.m[3][2] * b.m[2][2] + a.m[3][3] * b.m[3][2]; // 3列
	result.m[3][3] = a.m[3][0] * b.m[0][3] + a.m[3][1] * b.m[1][3] + a.m[3][2] * b.m[2][3] + a.m[3][3] * b.m[3][3]; // 4列
	return result;
}
Matrix4x4 Scale(const Vector3& a) {
	Matrix4x4 result{};
	result.m[0][0] = a.x;
	result.m[1][1] = a.y;
	result.m[2][2] = a.z;
	result.m[3][3] = 1;
	return result;
};

/// <summary>
/// 転置行列
/// </summary>
/// <param name="a"></param>
/// <returns></returns>
Matrix4x4 Transpose(const Matrix4x4 a) { // 12コイル
	Matrix4x4 retult{};
	retult.m[1][0] = a.m[0][1];
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

	retult.m[0][0] = a.m[0][0];
	retult.m[1][1] = a.m[1][1];
	retult.m[2][2] = a.m[2][2];
	retult.m[3][3] = a.m[3][3];

	return retult;
}

Matrix4x4 MakeTranslateMatrix(const Vector3& translate) {
	Matrix4x4 result{};
	result.m[0][0] = 1;
	result.m[1][1] = 1;
	result.m[2][2] = 1;
	result.m[3][3] = 1;

	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	return result;
};
// 拡縮
Matrix4x4 MakeScaleMatrix(const Vector3& scale) {
	Matrix4x4 result{};
	result.m[0][0] = scale.x;
	result.m[1][1] = scale.y;
	result.m[2][2] = scale.z;
	result.m[3][3] = 1;
	return result;
};

Vector3 Transform(const Vector3& vector, const Matrix4x4& mattrix) {
	Vector3 result{};
	result.x = vector.x * mattrix.m[0][0] + vector.y * mattrix.m[1][0] + vector.z * mattrix.m[2][0] + 1.0f * mattrix.m[3][0];
	result.y = vector.x * mattrix.m[0][1] + vector.y * mattrix.m[1][1] + vector.z * mattrix.m[2][1] + 1.0f * mattrix.m[3][1];
	result.z = vector.x * mattrix.m[0][2] + vector.y * mattrix.m[1][2] + vector.z * mattrix.m[2][2] + 1.0f * mattrix.m[3][2];
	float w = vector.x * mattrix.m[0][3] + vector.y * mattrix.m[1][3] + vector.z * mattrix.m[2][3] + 1.0f * mattrix.m[3][3];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;
	return result;
};
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {

	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);
	Matrix4x4 rotateXYZMatrix =Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));

	return Multiply(Multiply(Scale(scale), rotateXYZMatrix), MakeTranslateMatrix(translate));
};

// 透視投影行列
Matrix4x4 MakePerspectiveMatrix(float forY, float aspectRatio, float nearClip, float farClip) {
	Matrix4x4 resurt{};
	// float s = 1; // しらんa/bってなんやねんもっと分かりやすくかけやヴぉけ
	float cot = 1 / (std::tan(forY / 2));
	resurt.m[0][0] = 1 / aspectRatio * cot;
	resurt.m[1][1] = cot;
	resurt.m[2][2] = farClip / (farClip - nearClip);
	resurt.m[2][3] = 1;
	resurt.m[3][2] = -nearClip * farClip / (farClip - nearClip);
	return resurt;
};
// 正射影行列
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip) {
	Matrix4x4 resurt{};
	resurt.m[0][0] = 2 / (right - left);
	resurt.m[1][1] = 2 / (top - bottom);
	resurt.m[2][2] = 1 / (farClip - nearClip);
	resurt.m[3][3] = 1;
	resurt.m[3][0] = (left + right) / (left - right);
	resurt.m[3][1] = (top + bottom) / (bottom - top);
	resurt.m[3][2] = nearClip / (nearClip - farClip);
	return resurt;
};
// ビューポート変換行列
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {
	Matrix4x4 resurt{};
	resurt.m[0][0] = width / 2;
	resurt.m[1][1] = -height / 2;
	resurt.m[2][2] = maxDepth - minDepth;
	resurt.m[3][0] = left + (width / 2);
	resurt.m[3][1] = top + (height / 2);
	resurt.m[3][2] = minDepth;
	resurt.m[3][3] = 1;
	return resurt;
};
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
	Novice::ScreenPrintf(x, y - 20, "%s", label);
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight, "%6.02f", matrix.m[row][column]);
		}
	}
}

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
};
