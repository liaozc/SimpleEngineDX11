#ifndef RS_MESHRENDERER_DX11_H
#define RS_MESHRENDERER_DX11_H

#include "rs_meshrenderer_public.h"
#include "rs_buffer_dx11.h"
#include "rs_material_dx11.h"
#include "rs_renderer_dx11.h"

class RS_MeshRendererDX11 :public iRS_MeshRenderer
{
public:
	RS_MeshRendererDX11(RS_RendererDX11* pRenderer);
	virtual ~RS_MeshRendererDX11();
	virtual void SetMesh(Mesh* mesh);
	virtual Mesh* GetMesh() const { return m_pMesh; }
	virtual iRS_Material* GetMaterial() const {	return m_pMaterial;}
	virtual void SetMaterial(iRS_Material* pMat);
	virtual iRS_Buffer* GetVertBuffer() const { return m_pVertBuffer; }
	virtual iRS_Buffer* GetIndexBuffer() const { return m_pIndexBuffer; }
	virtual void DoRender();
protected:
	void updateMesh();
	LPCSTR getSemanticName(eRS_VertDataFormat vertDataFormat);
	DXGI_FORMAT	getDatatFormat(eRS_VertDataFormat vertDataFormat);
	int	getDataSize(eRS_VertDataFormat vertDataFormat);
protected:
	RS_VertBufferDX11* m_pVertBuffer;
	RS_IndexBufferDX11* m_pIndexBuffer;
	RS_MaterialDX11* m_pMaterial;
	Mesh* m_pMesh;
	RS_RendererDX11* m_pRenderer;
	ID3D11InputLayout* m_pInputLayout;
	
};

#endif
