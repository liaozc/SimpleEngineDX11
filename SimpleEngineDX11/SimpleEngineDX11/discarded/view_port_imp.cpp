#include "view_port_imp.h"
#include "factory_public.h"

extern "C"
ViewPort* CreateView(iEngine* pEngine)
{
	ViewPort* pView = new ViewPort();
	pView->Init(pEngine);
	return pView;
}


ViewPort::ViewPort():
	m_pCamera(nullptr)
{
	m_pCamera = CreateSimpleCamera();
}

void ViewPort::Init(iEngine * pEngine)
{
}

void ViewPort::OnAttached()
{
}

void ViewPort::OnDetached()
{
}
