#include "rs_meshrenderer_dx11.h"
#include "geo_mesh.h"
#include "rs_shader_dx11.h"

RS_MeshRendererDX11::RS_MeshRendererDX11(RS_RendererDX11 * pRenderer)
{
	m_pRenderer = pRenderer;
	m_pIndexBuffer = nullptr;
	m_pVertBuffer = nullptr;
	m_pMesh = nullptr;
	m_pMaterial = nullptr;
	m_pInputLayout = nullptr;
	//SAFE_ADDREF(pRenderer);
}

RS_MeshRendererDX11::~RS_MeshRendererDX11()
{
	SAFE_RELEASE(m_pVertBuffer);
	SAFE_RELEASE(m_pIndexBuffer);
	SAFE_RELEASE(m_pMaterial);
	SAFE_RELEASE(m_pInputLayout);
	SAFE_DELETE(m_pMesh);
//	SAFE_RELEASE(m_pRenderer);

}

void RS_MeshRendererDX11::SetMesh(Mesh * mesh)
{
	if (m_pMesh == mesh) return;
	m_pMesh = mesh;
	updateMesh();
}

void RS_MeshRendererDX11::SetMaterial(iRS_Material * pMat)
{
	SAFE_RELEASE(m_pMaterial);
	m_pMaterial = dynamic_cast<RS_MaterialDX11*>(pMat);
	SAFE_ADDREF(m_pMaterial);
}

void RS_MeshRendererDX11::DoRender()
{
	if (!m_pRenderer) return;
	if (m_pMaterial) m_pMaterial->Apply(m_pRenderer);
	ID3D11Buffer* pVb = m_pVertBuffer->GetGPUBuffer();
	ID3D11Buffer* pVBA[] = { pVb };
	const UINT pVStride[1] = { (UINT)m_pVertBuffer->GetStride() };
	ID3D11Buffer* pIb = m_pIndexBuffer->GetGPUBuffer();
	const UINT pIStride[1] = { (UINT)m_pVertBuffer->GetStride() };
	const UINT pOffset[1] = {0};
	m_pRenderer->GetContext()->IASetVertexBuffers(0,1, pVBA, pVStride, pOffset);
	m_pRenderer->GetContext()->IASetIndexBuffer(pIb, DXGI_FORMAT_R16_UINT, 0);
	m_pRenderer->GetContext()->IASetInputLayout(m_pInputLayout);
	m_pRenderer->GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pRenderer->GetContext()->Draw(3, 0);
}

void RS_MeshRendererDX11::updateMesh()
{
	//clear buffer first
	SAFE_RELEASE(m_pVertBuffer);
	SAFE_RELEASE(m_pIndexBuffer);
	SAFE_RELEASE(m_pInputLayout);
	if (!m_pVertBuffer) m_pVertBuffer = new RS_VertBufferDX11(m_pRenderer);
	if (!m_pIndexBuffer) m_pIndexBuffer = new RS_IndexBufferDX11(m_pRenderer);
	if (m_pMesh) {
		m_pVertBuffer->Create(m_pMesh->GetVertSize() * m_pMesh->GetVertStride(),m_pMesh->GetVerts());
		m_pVertBuffer->SetStride(m_pMesh->GetVertStride());
		m_pIndexBuffer->Create(m_pMesh->GetIndexSize() * m_pMesh->GetIndsStride(), m_pMesh->GetInds());
		m_pIndexBuffer->SetStride(m_pMesh->GetIndsStride());
		int formatSize = m_pMesh->GetFormatSize();
		eRS_VertDataFormat* pFormats = m_pMesh->GetFormat();
		D3D11_INPUT_ELEMENT_DESC* pDescInputEle = new D3D11_INPUT_ELEMENT_DESC[formatSize];
		for (int i = 0; i < formatSize; ++i) {
			pDescInputEle[i].SemanticName = getSemanticName(pFormats[i]);
			pDescInputEle[i].SemanticIndex = 0;
			pDescInputEle[i].Format = getDatatFormat(pFormats[i]);
			pDescInputEle[i].InputSlot = 0;
			pDescInputEle[i].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
			pDescInputEle[i].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			pDescInputEle[i].InstanceDataStepRate = 0;
		}
		ID3DBlob* pInputSignature = m_pMaterial? ((RS_ShaderDX11*)m_pMaterial->GetShader(eRS_VertShader))->GetInputSignature() : nullptr;
		if (FAILED(m_pRenderer->GetDevice()->CreateInputLayout(pDescInputEle, formatSize,
			pInputSignature ? pInputSignature->GetBufferPointer() : 0, pInputSignature ? pInputSignature->GetBufferSize() : 0, &m_pInputLayout))) {
			printf("Couldn't create vertex declaration");
		}
	}
}

LPCSTR RS_MeshRendererDX11::getSemanticName(eRS_VertDataFormat vertDataFormat)
{
	static LPCSTR names[] = { "Position","Normal","Color","Texcoord" };
	int index = vertDataFormat - eRS_VertDataFormat_Position;
	if (index < 0 || index >= eRS_VertDataFormat_Count) return "";
	return names[index];
}

DXGI_FORMAT RS_MeshRendererDX11::getDatatFormat(eRS_VertDataFormat vertDataFormat)
{
	static const DXGI_FORMAT formats[] = {
		DXGI_FORMAT_R32_FLOAT, 
		DXGI_FORMAT_R32G32_FLOAT,
		DXGI_FORMAT_R32G32B32_FLOAT, 
		DXGI_FORMAT_R32G32B32A32_FLOAT,
	};

	int dataIndex = getDataSize(vertDataFormat);
	if (dataIndex == 0) return DXGI_FORMAT_UNKNOWN;
	return formats[dataIndex - 1];
}

int RS_MeshRendererDX11::getDataSize(eRS_VertDataFormat vertDataFormat)
{
	static int sizes[] = { 3,3,4,2 };
	int index = vertDataFormat - eRS_VertDataFormat_Position;
	if (index < 0 || index >= eRS_VertDataFormat_Count) return 0;
	return sizes[index];
}
