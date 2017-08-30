#ifndef MTH_QUATERNION_H
#define MTH_QUATERNION_H

class Quaternion
{
public:
	float x;
	float y;
	float z;
	float w;
	Quaternion() :x(0), y(0), z(0), w(1) {}
	Quaternion(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
	static Quaternion Format(const Vector3& axis, float radian) 
	{
		(axis), (radian);
		return Quaternion(0,0,0,1);
	}
};


#endif
