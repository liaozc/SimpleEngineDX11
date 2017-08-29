#ifndef CAMERA_SIMPLE_H
#define CAMERA_SIMPLE_H

#include "camera_public.h"

class CameraSimple : public iCamera
{
public:
	virtual Vector3 GetPosition() const;
	virtual void  SetPosition(const Vector3& pos);
	virtual Quat	GetOrientation() const ;
	virtual void SetOrientation(const Quat& quat);
	virtual void LookAt(const Vector3& target);
	virtual const Matrix4& GetTransform() const;
protected:
	void updateTransform();
protected:
	Vector3 m_vPosition;
	Quat	m_qOri;
	Matrix4 m_mCached;
};

#endif
