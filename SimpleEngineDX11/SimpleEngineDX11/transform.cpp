#include "transform.h"

const Matrix & Transform::GetMatrix()
{
	if (m_bDirty)
		updateMatrix();
	return m_cachedM;
}

void Transform::AddChild(Transform * child)
{
	m_vChildren.push_back(child);
}

void Transform::RemoveChild(Transform * child)
{
	std::vector<Transform*>::iterator it = m_vChildren.begin();
	for (; it != m_vChildren.end(); ++it)
		if (*it == child) break;
	if (it != m_vChildren.end()) m_vChildren.erase(it);
}

void Transform::SetParent(Transform * parent)
{
	m_Parent = parent;
}

Transform * Transform::GetParent() const
{
	return m_Parent;
}

void Transform::updateMatrix()
{
}
