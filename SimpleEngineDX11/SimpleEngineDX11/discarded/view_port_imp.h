#ifndef VIEW_IMP_H
#define VIEW_IMP_H

#include "view_port_public.h"
#include "camera_public.h"

class ViewPort : public iViewPort
{
public:
	ViewPort();
	virtual void Init(iEngine* pEngine);
	virtual void OnAttached();
	virtual void OnDetached();
	virtual iCamera* GetCamera() const { return m_pCamera; }
protected:
	iCamera*	m_pCamera;
};

#endif
