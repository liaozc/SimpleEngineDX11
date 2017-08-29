#ifndef CAMERA_H
#define CAMERA_H

#include "dx_wrapper.h"

class iCamera
{
public:
	virtual Vector3 GetPosition() const = 0;
	virtual void  SetPosition(const Vector3& pos) = 0;
	virtual Quat	GetOrientation() const = 0;
	virtual void SetOrientation(const Quat& quat) = 0;
	virtual void LookAt(const Vector3& target) = 0;
	virtual const Matrix4& GetTransform() const = 0;
};

#endif
