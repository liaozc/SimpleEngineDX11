#ifndef MTH_VECTOR_H
#define MTH_VECTOR_H


class Vector2
{
public:
	float x;
	float y;
	Vector2() :x(0), y(0) {}
	Vector2(float _x, float _y) : x(_x), y(_y){}

};


class Vector3 
{
public:
	float x;
	float y;
	float z;
	Vector3() :x(0), y(0), z(0) {}
	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

};

class Vector4
{
public:
	float x;
	float y;
	float z;
	float w;
	Vector4() :x(0), y(0), z(0),w(0) {}
	Vector4(float _x, float _y, float _z,float _w) : x(_x), y(_y), z(_z), w(_w){}

};

#endif
