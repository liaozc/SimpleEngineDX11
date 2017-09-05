#include "rs_buffer_dx11.h"
#include "rs_renderer_dx11.h"

RS_BufferDX11::RS_BufferDX11(RS_RendererDX11 * pRenderer)
{
	m_eType = eRS_BT_None;
	m_pBuffer = nullptr;
	m_pRenderer = pRenderer;
	m_nSize = 0;
	m_bStatic = false;
	//SAFE_ADDREF(m_pRenderer);
}

RS_BufferDX11::~RS_BufferDX11()
{
	unInit();
}

HRESULT RS_BufferDX11::Create(int dataSize, void * data)
{
	if (!m_pRenderer) return E_FAIL;
	if (dataSize == 0) return E_FAIL;

	RS_RendererDX11* pRendererDX11 = dynamic_cast<RS_RendererDX11*>(m_pRenderer);
	if (!pRendererDX11) return E_FAIL;
	ID3D11Device* pD3DDevice = pRendererDX11->GetDevice();
	if (!pD3DDevice) return E_FAIL;
	SAFE_RELEASE(m_pBuffer);
	D3D11_BUFFER_DESC descBuffer;
	descBuffer.ByteWidth = dataSize;
	descBuffer.MiscFlags = 0;
	descBuffer.StructureByteStride = 0;
	descBuffer.BindFlags = getFlag();
	descBuffer.CPUAccessFlags = 0;
	descBuffer.Usage = D3D11_USAGE_DEFAULT;
	D3D11_SUBRESOURCE_DATA subResData;
	subResData.pSysMem = data;
	subResData.SysMemPitch = 0;
	subResData.SysMemSlicePitch = 0;
	if (FAILED(pD3DDevice->CreateBuffer(&descBuffer, data ? &subResData : 0, &m_pBuffer))) {
		printf("can't create buffer\n");
		return E_FAIL;
	}
	m_nSize = dataSize;
	return S_OK;
}

void RS_BufferDX11::unInit()
{
	m_eType = eRS_BT_None;
	m_nSize = 0;
	m_bStatic = false;
	//SAFE_RELEASE(m_pRenderer);
	SAFE_RELEASE(m_pBuffer);
}

D3D11_BIND_FLAG RS_BufferDX11::getFlag() const
{
	switch (m_eType)
	{
	case eRS_BT_Vertex:
		return D3D11_BIND_VERTEX_BUFFER;
	case eRS_BT_Index:
		return D3D11_BIND_INDEX_BUFFER;
	case eRS_BT_Constant:
		return D3D11_BIND_CONSTANT_BUFFER;
	}

	return D3D11_BIND_VERTEX_BUFFER;
}

RS_VertBufferDX11::RS_VertBufferDX11(RS_RendererDX11 * pRenderer)
	:RS_BufferDX11(pRenderer)
{
	m_eType = eRS_BT_Vertex;
}

RS_IndexBufferDX11::RS_IndexBufferDX11(RS_RendererDX11 * pRenderer)
	: RS_BufferDX11(pRenderer)
{
	m_eType = eRS_BT_Index;
}

RS_ConstantBufferDX11::RS_ConstantBufferDX11(RS_RendererDX11 * pRenderer)
	: RS_BufferDX11(pRenderer)
{
	m_eType = eRS_BT_Constant;
	m_bDirty = true;
	m_pConstantMem = nullptr;
}

RS_ConstantBufferDX11::~RS_ConstantBufferDX11()
{
	unInit();
}

HRESULT RS_ConstantBufferDX11::CreateFromShader(ID3D11ShaderReflectionConstantBuffer * pRefl)
{
	if (!pRefl) return E_FAIL;
	D3D11_SHADER_BUFFER_DESC desc;
	pRefl->GetDesc(&desc);
	if (FAILED(Create(desc.Size, 0)))  return E_FAIL;
	m_pConstantMem = new byte[desc.Size];
	for (UINT i = 0; i < desc.Variables; ++i) {
		D3D11_SHADER_VARIABLE_DESC varDesc;
		pRefl->GetVariableByIndex(i)->GetDesc(&varDesc);
		RS_ShaderConstantVar scv;
		scv.szName = new char[strlen(varDesc.Name) + 1];
		strcpy((char*)scv.szName, varDesc.Name);
		scv.data = m_pConstantMem + varDesc.StartOffset;
		scv.nSize = varDesc.Size;
		m_vConstants.push_back(scv);
	}
	return S_OK;
	
}

bool RS_ConstantBufferDX11::SetValue(LPCSTR name, void * data, short size)
{
	if (!data || size == 0) return false;
	size_t csize = m_vConstants.size();
	size_t i = 0;
	for (; i < csize; ++i) {
		if (strcmp(m_vConstants[i].szName, name) == 0) break;
	}
	if (i == csize) return false;
	if (m_vConstants[i].nSize != size) { printf("costant size not consistent name>: %s\n",(char*)name); return false; }
	memcpy(m_vConstants[i].data, data, size);
	m_bDirty = true;
	return true;
}

void RS_ConstantBufferDX11::Apply()
{
	if (!m_pRenderer || !m_pBuffer || !m_pConstantMem || !m_bDirty) return;
	ID3D11DeviceContext* pContext = m_pRenderer->GetContext();
	if (!pContext) return;
	pContext->UpdateSubresource(m_pBuffer, 0, 0, m_pConstantMem, 0, 0);
	m_bDirty = false;
}

void RS_ConstantBufferDX11::unInit()
{
	SAFE_DELETE_ARRAY(m_pConstantMem);
	for (size_t i = 0; i < m_vConstants.size(); ++ i) {
		m_vConstants[i].clear();
	}
	m_eType = eRS_BT_Constant;
}

