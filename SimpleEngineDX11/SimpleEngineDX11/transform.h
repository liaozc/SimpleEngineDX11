#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "mth_math.h"
#include "stl_containers.h"

class Transform
{
public:
	Transform() : m_scale(Vector3(1, 1, 1)), m_bDirty(true), m_Parent(nullptr)
	{}
	void SetPosition(const Vector3& pos) { m_position = pos; m_bDirty = true; }
	Vector3 GetPosition()  const { return m_position; }
	void SetRotation(const Vector3& axis, float radian) { m_rotation = Quaternion::Format(axis, radian); m_bDirty = true; }
	const Quaternion& GetRatation() const { return m_rotation; }
	void SetScale(const Vector3& scale) { m_scale = scale; m_bDirty = true; }
	const Vector3& GetScale() const { return m_scale; }
	const Matrix& GetMatrix();
	void AddChild(Transform* child);
	void RemoveChild(Transform* child);
	void SetParent(Transform* parent);
	Transform* GetParent() const ;
protected:
	void updateMatrix();
protected:
	bool m_bDirty;
	Vector3 m_position;
	Vector3 m_scale;
	Quaternion m_rotation;
	Matrix m_cachedM;
	std::vector<Transform*> m_vChildren;
	Transform* m_Parent;
};


#endif
