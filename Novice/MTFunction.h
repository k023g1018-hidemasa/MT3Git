#pragma once
#define _USE_MATH_DEFINES
#include "DebugCamera.h"
#include "Matrix4x4.h"
#include "Vector3.h"
#include <Novice.h>
#include <ViewProjection.h>
#include <assert.h>
#include <cmath>
#include <math.h>
#include <iostream>
#include <algorithm>


static const int kRowHeight = 20;
static const int kColumnWidth = 60;
static const int kWindowWidth = 1280;
static const int kWindoweHeight = 720;
DebugCamera* debugCamera_ = nullptr;

// struct Matrix4x4 {
//	float m[4][4];
// };
// struct Vector3  {
//	float x;
//	float y;
//	float z; // 認識できない退寮に出たら多分コンストの影響
//  なんでこいつらじゃなくてヘッダファイルならエラー出ないの？
//
// };
struct Sphere {
	Vector3 center; // 中心点ではない？
	float radius;   // 半径より大きくない？
};

struct Segment {
	Vector3 origin; // 視点
	Vector3 diff;   // 終点への差分ベクトル
};

struct Plane {
	Vector3 normal;
	float distance;
};

struct Triangle {
	Vector3 vertices[3];
};

struct AABB {
	Vector3 min;
	Vector3 max;
};

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
};

float Length(const Vector3& v) {
	float result;
	result = sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	return result;
};

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
};

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
};
Vector3 Scale(float k, const Vector3& a) {
	Vector3 result{};
	result.x = a.x * k;
	result.y = a.y * k;
	result.z = a.z * k;
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
};

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
	Matrix4x4 rotateXYZMatrix = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));
	Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);

	return Multiply(Multiply(scaleMatrix, rotateXYZMatrix), MakeTranslateMatrix(translate));
};

// 透視投影行列
Matrix4x4 MakePerspectiveMatrix(float forY, float aspectRatio, float nearClip, float farClip) {
	Matrix4x4 resurt{};
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
Vector3 Project(const Vector3& v1, const Vector3& v2) {
	// 正射影ベクトル
	Vector3 result;
	float a = Dot(v1, v2);
	float b = Dot(v2, v2);
	result.x = a / b * v2.x;
	result.y = a / b * v2.y;
	result.z = a / b * v2.z;

	return result;
};
// 最近接点
Vector3 ClosestPoint(const Vector3& point, const Segment& segment) {

	Vector3 project = Project(Subtract(point, segment.origin), segment.diff);

	project = Add(segment.origin, project);
	return project;
};

Vector3 Perpendicular(const Vector3& vector) {
	if (vector.x != 0.0f || vector.y != 0.0f) {
		return {-vector.y, vector.x, 0.0f};
	}
	return {0.0f, -vector.z, vector.y};
}
bool LineIsCollision(const Segment& segment, const Plane& plane) {
	float dot = Dot(plane.normal, segment.diff);
	if (dot != 0.0f) {
		float t = (plane.distance - Dot(segment.origin, plane.normal)) / dot;
		return (0 <= t) && (t <= 1);
	}
	return false;
}
bool ToriangleIsCollision(const Triangle& triangle, const Segment& segment) {
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
bool AABBIsCollision(const AABB& aabb1, const AABB& aabb2) {
	return(aabb1.min.x<=aabb2.max.x&&aabb1.max.x>=aabb2.min.x)&&
		(aabb1.min.y<=aabb2.max.y&&aabb1.max.y>=aabb2.min.y)&&
		(aabb1.min.z<=aabb2.max.z&&aabb1.max.z>=aabb2.min.z);
}
bool AABBAndSphereIsCollision(const AABB& aabb, const Sphere& sphere) {

	Vector3 closestPoint{
		std::clamp(sphere.center.x,aabb.min.x,aabb.max.x),
		std::clamp(sphere.center.y,aabb.min.y,aabb.max.y),
	    std::clamp(sphere.center.z,aabb.min.z,aabb.max.z)
	};
	float distance = Length(Subtract(closestPoint, sphere.center));

	return distance <= sphere.radius;
}
    // グリッドの表示
void DrawSegment(const Segment& segment, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewProtMatrix, uint32_t color) {
	Vector3 start = Transform(Transform(segment.origin, viewProtMatrix), viewProtMatrix);
	Vector3 end = Transform(Transform(Add(segment.origin, segment.diff), viewProjectionMatrix), viewProtMatrix);
	Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), color);
}
void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) { //,Matrix4x4& WorldMatrix
	const float kGridHalfwidth = 2.0f;                                                  // グリッドの半分の幅
	const uint32_t kSubdivision = 10;                                                   // 分割数
	const float kGridEvery = (kGridHalfwidth * 2.0f) / float(kSubdivision);             // 一つ分の長さ
	// 奥から手前への線を順に引いていく
	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {

		float x = -kGridHalfwidth + (xIndex * kGridEvery); // コレで均等に幅が取れる？

		Vector3 start = {x, 0.0f, -kGridHalfwidth};
		Vector3 end = {x, 0.0f, kGridHalfwidth};

		Vector3 screenStart = Transform(Transform(start, viewProjectionMatrix), viewportMatrix);
		Vector3 screenEnd = Transform(Transform(end, viewProjectionMatrix), viewportMatrix);

		Novice::DrawLine(int(screenStart.x), int(screenStart.y), int(screenEnd.x), int(screenEnd.y), 0xAAAAAAFF);
		// ビュープロジェクションマトリクス手なに？どこにいあいあ
		// 関数どう当てはめるんか分からん
		// 多分ビューポートで数字取ってきてラインの視点終点見つけるんやけど数字のあてはめ方知らん
	}
	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {

		float z = -kGridHalfwidth + (zIndex * kGridEvery); // コレで均等に幅が取れる？

		Vector3 start = {-kGridHalfwidth, 0.0f, z};
		Vector3 end = {kGridHalfwidth, 0.0f, z};

		Vector3 screenStart = Transform(Transform(start, viewProjectionMatrix), viewportMatrix);
		Vector3 screenEnd = Transform(Transform(end, viewProjectionMatrix), viewportMatrix);

		Novice::DrawLine(int(screenStart.x), int(screenStart.y), int(screenEnd.x), int(screenEnd.y), 0xAAAAAAFF);
		// ビュープロジェクションマトリクス手なに？どこにいあいあ
		// 関数どう当てはめるんか分からん
		// 多分ビューポートで数字取ってきてラインの視点終点見つけるんやけど数字のあてはめ方知らん
	}
};
void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	const uint32_t kSubdivision = 12;                          // 分割数
	const float kLonEvery = 2.0f * float(M_PI) / kSubdivision; // 軽度分割一つ分の角度 φd
	const float kLatEvery = float(M_PI) / kSubdivision;        // 緯度文の角度//この辺はまだ知らん Θd

	// 緯度は横でｘでシータ、経度は縦でｙでファイ、＆みたいな形しやがって、、、
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = float(M_PI) / 2.0f + kLatEvery * latIndex; // 今のイドマーフのπってどう出すん化？　Θ
		// 軽度の方向に分割0～2PI
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			// 級は上から見たら縁になってるからファイっての使ったら中心の座標が出てくる？
			// んでｘｙの縁を合わせたら+みたいに見えるのでそれをずらしたら急になる？差分は多分縁のずれ
			float lon = lonIndex * kLonEvery; // これは今のイド φ
			// world座標系でのabcを求めるこれは9ｐ？
			Vector3 a, b, c;
			a = {std::cos(lat) * std::cos(lon) * sphere.radius + sphere.center.x, std::sin(lat) * sphere.radius + sphere.center.y, std::cos(lat) * std::sin(lon) * sphere.radius + sphere.center.z};
			b = {
			    std::cos(lat + kLatEvery) * std::cos(lon) * sphere.radius + sphere.center.x, std::sin(lat + kLatEvery) * sphere.radius + sphere.center.y,
			    std::cos(lat + kLatEvery) * std::sin(lon) * sphere.radius + sphere.center.z};
			c = {
			    std::cos(lat) * std::cos(lon + kLonEvery) * sphere.radius + sphere.center.x, std::sin(lat) * sphere.radius + sphere.center.y,
			    std::cos(lat) * std::sin(lon + kLonEvery) * sphere.radius + sphere.center.z};

			// abcをスクリーンまで返還
			// ab,bcで線を引く線を引くのは分かった、変換が分からん

			Vector3 screenA = Transform(Transform(a, viewProjectionMatrix), viewportMatrix);
			Vector3 screenB = Transform(Transform(b, viewProjectionMatrix), viewportMatrix);
			Vector3 screenC = Transform(Transform(c, viewProjectionMatrix), viewportMatrix);

			Novice::DrawLine(int(screenA.x), int(screenA.y), int(screenB.x), int(screenB.y), color);
			Novice::DrawLine(int(screenA.x), int(screenA.y), int(screenC.x), int(screenC.y), color);
		}
	}
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
}
void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	Vector3 screenVertices[3] = {
	    Transform(Transform(triangle.vertices[0], viewProjectionMatrix), viewportMatrix),
	    Transform(Transform(triangle.vertices[1], viewProjectionMatrix), viewportMatrix),
	    Transform(Transform(triangle.vertices[2], viewProjectionMatrix), viewportMatrix),
	};
	// この中で変換させる？
	Novice::DrawTriangle(
	    int(screenVertices[0].x), int(screenVertices[0].y), int(screenVertices[1].x), int(screenVertices[1].y), int(screenVertices[2].x), int(screenVertices[2].y), color, kFillModeWireFrame);
};
void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	Vector3 vertices[8] = {
	    {aabb.min.x, aabb.min.y, aabb.min.z},
        {aabb.min.x, aabb.max.y, aabb.min.z},
        {aabb.min.x, aabb.max.y, aabb.max.z},
        {aabb.min.x, aabb.min.y, aabb.max.z},
	    {aabb.max.x, aabb.min.y, aabb.min.z},
        {aabb.max.x, aabb.max.y, aabb.min.z},
        {aabb.max.x, aabb.max.y, aabb.max.z},
        {aabb.max.x, aabb.min.y, aabb.max.z},
	};

	Vector3 screenVertices[8];
	for (uint32_t index = 0; index < 8; ++index) {
		screenVertices[index] = Transform(Transform(vertices[index], viewProjectionMatrix), viewportMatrix);
	}

	std::pair<uint32_t, uint32_t> indices[12] = {
	    {0, 1},
        {1, 2},
        {2, 3},
        {3, 0},
        {4, 5},
        {5, 6},
        {6, 7},
        {7, 4},
        {0, 4},
        {1, 5},
        {2, 6},
        {3, 7},
	};
	for (auto& index : indices) {
		Novice::DrawLine(int(screenVertices[index.first].x), int(screenVertices[index.first].y),
	    int(screenVertices[index.second].x), int(screenVertices[index.second].y),color);

	}



}

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
	Novice::ScreenPrintf(x, y - 20, "%s", label);
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight, "%6.02f", matrix.m[row][column]);
		}
	}
};
void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
};