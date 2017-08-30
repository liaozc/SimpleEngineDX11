#ifndef MTH_MATRIX_H
#define MTH_MATRIX_H

class Matrix
{
public:
	float m00, m01, m02, m03;
	float m10, m11, m12, m13;
	float m20, m21, m22, m23;
	float m30, m31, m32, m33;
	Matrix(float _m00, float _m01, float _m02, float _m03,
		float _m10, float _m11, float _m12, float _m13,
		float _m20, float _m21, float _m22, float _m23,
		float _m30, float _m31, float _m32, float _m33) :
		m00(_m00), m01(_m01), m02(_m02), m03(_m03),
		m10(_m10), m11(_m11), m12(_m12), m13(_m13),
		m20(_m20), m21(_m21), m22(_m22), m23(_m23),
		m30(_m30), m31(_m31), m32(_m32), m33(_m33)
	{}
	Matrix() :
		m00(1), m01(0), m02(0), m03(0),
		m10(0), m11(1), m12(0), m13(0),
		m20(0), m21(0), m22(1), m23(0),
		m30(0), m31(0), m32(0), m33(1)
	{}
};

#endif
