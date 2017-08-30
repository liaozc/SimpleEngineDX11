#include "rs_buffer_dx11.h"
#include "rs_renderer_dx11.h"

RS_BufferDX11::RS_BufferDX11(eRS_BufferType bufferType, int dataSize, void * data,bool bStatic, iRS_Renderer * pRenderer)
{
	m_eType = bufferType;
	m_nSize = dataSize;
	m_pRenderer = pRenderer;
	m_bStatic = bStatic;
	m_pBuffer = nullptr;
	Create(dataSize, data);
}

void * RS_BufferDX11::Map2Memory(int& width, int& height)
{
	width = height = 0;
	if (!m_pBuffer || ! m_pRenderer) return nullptr;
	RS_RendererDX11* pRendererDX11 = dynamic_cast<RS_RendererDX11*>(m_pRenderer);
	if (!pRendererDX11) return nullptr;
	ID3D11DeviceContext* pContext = pRendererDX11->GetContext();
	if (!pContext) return nullptr;
	D3D11_MAPPED_SUBRESOURCE dataMap;
	if (FAILED(pContext->Map(m_pBuffer, 0, D3D11_MAP_WRITE, 0, &dataMap))) {
		printf("can't map the buffer to memory\n");
		return nullptr;
	}
	width = dataMap.RowPitch;
	height = dataMap.DepthPitch;
	return dataMap.pData;
}

void RS_BufferDX11::Map2GPU()
{
	if (!m_pBuffer || !m_pRenderer) return;
	RS_RendererDX11* pRendererDX11 = dynamic_cast<RS_RendererDX11*>(m_pRenderer);
	if (!pRendererDX11) return;
	ID3D11DeviceContext* pContext = pRendererDX11->GetContext();
	if (!pContext) return;
	pContext->Unmap(m_pBuffer, 0);
}

HRESULT RS_BufferDX11::Create(int dataSize, void * data)
{
	if (!m_pRenderer) return E_FAIL;
	if (!data && dataSize == 0) return E_FAIL;
	if (!data && dataSize != 0) return E_FAIL;
	if (data && dataSize == 0) return E_FAIL;

	RS_RendererDX11* pRendererDX11 = dynamic_cast<RS_RendererDX11*>(m_pRenderer);
	if (!pRendererDX11) return E_FAIL;
	ID3D11Device* pD3DDevice = pRendererDX11->GetDevice();
	if (!pD3DDevice) return E_FAIL;
	if (m_pBuffer) {
		m_pBuffer->Release();
		m_pBuffer = nullptr;
	}
	D3D11_BUFFER_DESC descBuffer;
	descBuffer.ByteWidth = dataSize;
	descBuffer.MiscFlags = 0;
	descBuffer.StructureByteStride = 0;
	descBuffer.BindFlags = getFlag();
	descBuffer.CPUAccessFlags = m_bStatic ? 0 :D3D11_CPU_ACCESS_WRITE;
	descBuffer.Usage = m_bStatic ? D3D11_USAGE_IMMUTABLE : D3D11_USAGE_DYNAMIC;
	D3D11_SUBRESOURCE_DATA subResData;
	subResData.pSysMem = data;
	subResData.SysMemPitch = 0;
	subResData.SysMemSlicePitch = 0;
	if (FAILED(pD3DDevice->CreateBuffer(&descBuffer, &subResData, &m_pBuffer))) {
		printf("can't create buffer");
		return E_FAIL;
	}
	return S_OK;
}

D3D11_BIND_FLAG RS_BufferDX11::getFlag() const
{
	switch (m_eType)
	{
	case eRSBT_Vertex:
		return D3D11_BIND_VERTEX_BUFFER;
	case eRSBT_Index:
		return D3D11_BIND_INDEX_BUFFER;
	}

	return D3D11_BIND_VERTEX_BUFFER;
}


