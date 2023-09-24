//#include "matrixCalc.h"
//#pragma once
//Matrix4x4 MakeRotateXMatrix(float theta) {
//	Matrix4x4 result;
//	result.m[0][0] = 1;
//	result.m[0][1] = 0;
//	result.m[0][2] = 0;
//	result.m[0][3] = 0;
//	result.m[1][0] = 0;
//	result.m[1][1] = cosf(theta);
//	result.m[1][2] = sinf(theta);
//	result.m[1][3] = 0;
//	result.m[2][0] = 0;
//	result.m[2][1] = -sinf(theta);
//	result.m[2][2] = cosf(theta);
//	result.m[2][3] = 0;
//	result.m[3][0] = 0;
//	result.m[3][1] = 0;
//	result.m[3][2] = 0;
//	result.m[3][3] = 1;
//	return result;
//}
//Matrix4x4 MakeRotateYMatrix(float theta) {
//	Matrix4x4 result;
//	result.m[0][0] = cosf(theta);
//	result.m[0][1] = 0;
//	result.m[0][2] = -sinf(theta);
//	result.m[0][3] = 0;
//	result.m[1][0] = 0;
//	result.m[1][1] = 1;
//	result.m[1][2] = 0;
//	result.m[1][3] = 0;
//	result.m[2][0] = sinf(theta);
//	result.m[2][1] = 0;
//	result.m[2][2] = cosf(theta);
//	result.m[2][3] = 0;
//	result.m[3][0] = 0;
//	result.m[3][1] = 0;
//	result.m[3][2] = 0;
//	result.m[3][3] = 1;
//	return result;
//}
//Matrix4x4 MakeRotateZMatrix(float theta) {
//	Matrix4x4 result;
//	result.m[0][0] = cosf(theta);
//	result.m[0][1] = sinf(theta);
//	result.m[0][2] = 0;
//	result.m[0][3] = 0;
//	result.m[1][0] = -sinf(theta);
//	result.m[1][1] = cosf(theta);
//	result.m[1][2] = 0;
//	result.m[1][3] = 0;
//	result.m[2][0] = 0;
//	result.m[2][1] = 0;
//	result.m[2][2] = 1;
//	result.m[2][3] = 0;
//	result.m[3][0] = 0;
//	result.m[3][1] = 0;
//	result.m[3][2] = 0;
//	result.m[3][3] = 1;
//	return result;
//}
//
//Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
//	Matrix4x4 result;
//	float term = 0.0f;
//	for (int i = 0; i < 4; i++) {
//		for (int j = 0; j < 4; j++) {
//			term = 0;
//			for (int k = 0; k < 4; k++) {
//				term = term + m1.m[i][k] * m2.m[k][j];
//				result.m[i][j] = term;
//			}
//		}
//	}
//	return result;
//}
//
//Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
//	Matrix4x4 result;
//	Matrix4x4 RotateX = MakeRotateXMatrix(rotate.x);
//	Matrix4x4 RotateY = MakeRotateYMatrix(rotate.y);
//	Matrix4x4 RotateZ = MakeRotateZMatrix(rotate.z);
//	Matrix4x4 RotateXYZ = Multiply(RotateX, Multiply(RotateY, RotateZ));
//	result.m[0][0] = scale.x * RotateXYZ.m[0][0];
//	result.m[0][1] = scale.x * RotateXYZ.m[0][1];
//	result.m[0][2] = scale.x * RotateXYZ.m[0][2];
//	result.m[0][3] = 0;
//	result.m[1][0] = scale.y * RotateXYZ.m[1][0];
//	result.m[1][1] = scale.y * RotateXYZ.m[1][1];
//	result.m[1][2] = scale.y * RotateXYZ.m[1][2];
//	result.m[1][3] = 0;
//	result.m[2][0] = scale.z * RotateXYZ.m[2][0];
//	result.m[2][1] = scale.z * RotateXYZ.m[2][1];
//	result.m[2][2] = scale.z * RotateXYZ.m[2][2];
//	result.m[2][3] = 0;
//	result.m[3][0] = translate.x;
//	result.m[3][1] = translate.y;
//	result.m[3][2] = translate.z;
//	result.m[3][3] = 1;
//	return result;
//}