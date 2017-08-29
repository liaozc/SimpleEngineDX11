#include "camera_simple.h"

extern "C" 
iCamera* CreateSimpleCamera()
{
	CameraSimple* pCameraSimple = new CameraSimple();
	return pCameraSimple;
}

Vector3 CameraSimple::GetPosition() const
{
	return m_vPosition;
}

void CameraSimple::SetPosition(const Vector3 & pos)
{
	m_vPosition = pos;
	updateTransform();
}

Quat CameraSimple::GetOrientation() const
{
	return m_qOri;
}

void CameraSimple::SetOrientation(const Quat & quat)
{
	m_qOri = quat;
	updateTransform();
}

void CameraSimple::LookAt(const Vector3 & target)
{
	//
}

const Matrix4& CameraSimple::GetTransform() const
{
	return m_mCached;
}

void CameraSimple::updateTransform()
{
}
