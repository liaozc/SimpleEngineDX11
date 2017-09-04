#include "rs_shader_dx11.h"
#include "rs_renderer_dx11.h"
#include <d3dcompiler.h>
#include <d3d11shader.h>

RS_ShaderDX11::RS_ShaderDX11(RS_RendererDX11* pRenderer)
{
	m_pRenderer = pRenderer;
	m_pVShader = nullptr;
	m_pInputSignature = nullptr;
	m_pConstants = nullptr;
	m_nConstantSize = 0;
	m_eType = eRS_STNone;
}

HRESULT RS_ShaderDX11::CompilerFromMemory(const char* pSource, unsigned uSize, eRS_ShaderType type)
{
	if (!m_pRenderer) return E_FAIL;
	ID3D11Device* pDevice = m_pRenderer->GetDevice();
	if (!pDevice) return E_FAIL;
	if (m_eType != eRS_STNone) { printf("areadly has compile \n"); return E_FAIL; }
	if (!pSource || uSize == 0) { printf("error source for shader \n"); return E_FAIL; }

	static LPCSTR targets[eRS_ShaderType_Count - 1] = {
		"vs_5_0",
		"gs_5_0",
		"ps_5_0",
		"cs_5_0"
	};
	int index = type - eRS_VertShader;
	if (index < 0 || index >= eRS_ShaderType_Count - 1) { printf("erro shader type \n"); return E_FAIL; }
	LPCSTR target = targets[index];
	UINT complierFlag = D3DCOMPILE_PACK_MATRIX_ROW_MAJOR | D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
	complierFlag |= D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif 

	ID3D11ShaderReflection * pVSRefl= NULL;
	ID3D11ShaderReflection * pFSRefl = NULL;
	ID3DBlob* pShaderBuff = nullptr;
	ID3DBlob* pError = nullptr;
	bool success = false;
	if (SUCCEEDED(D3DCompile(pSource, uSize, "shader", nullptr, nullptr, "main", target, complierFlag, 0, &pShaderBuff, &pError))) {
		if (type == eRS_VertShader) {
			if (SUCCEEDED(pDevice->CreateVertexShader(pShaderBuff->GetBufferPointer(), pShaderBuff->GetBufferSize(), NULL, &m_pVShader))) {
				if (SUCCEEDED(D3DGetInputSignatureBlob(pShaderBuff->GetBufferPointer(), pShaderBuff->GetBufferSize(), &m_pInputSignature))) {
					D3DReflect(pShaderBuff->GetBufferPointer(), pShaderBuff->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&pVSRefl);
					success = true;
				}
			}
		}
		else if (type == eRS_GeometryShader) {
			if (SUCCEEDED(pDevice->CreateGeometryShader(pShaderBuff->GetBufferPointer(), pShaderBuff->GetBufferSize(), NULL, &m_pGShader))) {
				success = true;
			}
		}
		else if (type == eRS_FragmentShader) {
			if (SUCCEEDED(pDevice->CreatePixelShader(pShaderBuff->GetBufferPointer(), pShaderBuff->GetBufferSize(), NULL, &m_pPShader))) {
				D3DReflect(pShaderBuff->GetBufferPointer(), pShaderBuff->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&pFSRefl);
				success = true;
			}
		}
		else if (type == eRS_ComputeShader) {
			if (SUCCEEDED(pDevice->CreateComputeShader(pShaderBuff->GetBufferPointer(), pShaderBuff->GetBufferSize(), NULL, &m_pCShader))) {
				success = true;
			}
		}
	}
	else  if(pError) {
		printf("error complier :%s \n",(char*)pError->GetBufferPointer());
	}

	if (pVSRefl) {//gain some info from shader
		//constant buffer
		D3D11_SHADER_DESC descShader;
		pVSRefl->GetDesc(&descShader);
		m_nConstantSize = descShader.ConstantBuffers;
		if (m_nConstantSize != 0) {
			m_pConstants = new RS_ConstantBufferDX11*[m_nConstantSize];
			for (int i = 0; i < m_nConstantSize; ++i) {
				m_pConstants[i] = new RS_ConstantBufferDX11(m_pRenderer);
				m_pConstants[i]->CreateFromShader(pVSRefl->GetConstantBufferByIndex(i));
			}
		}
	}
	if (pFSRefl) {
		D3D11_SHADER_DESC descShader;
		pFSRefl->GetDesc(&descShader);
		m_nConstantSize = descShader.ConstantBuffers;
		if (m_nConstantSize != 0) {
			m_pConstants = new RS_ConstantBufferDX11*[m_nConstantSize];
			for (int i = 0; i < m_nConstantSize; ++i) {
				m_pConstants[i] = new RS_ConstantBufferDX11(m_pRenderer);
				m_pConstants[i]->CreateFromShader(pFSRefl->GetConstantBufferByIndex(i));
			}
		}
	}
	if (pShaderBuff) {
		pShaderBuff->Release();
		pShaderBuff = nullptr;
	}
	if (pError) {
		pError->Release();
		pError = nullptr;
	}



	if (success) m_eType = type;
	return success ? S_OK : E_FAIL;
}

void RS_ShaderDX11::SetConstant1f(LPCSTR szName, float fVal)
{
	for (int i = 0; i < m_nConstantSize; ++i) {
		if (m_pConstants[i]->SetValue(szName, &fVal, sizeof(fVal))) break;
	}
}

void RS_ShaderDX11::SetConstant2f(LPCSTR szName, const Vector2 & v2Val)
{
	for (int i = 0; i < m_nConstantSize; ++i) {
		if (m_pConstants[i]->SetValue(szName, (void*)&v2Val, sizeof(v2Val))) break;
	}
}

void RS_ShaderDX11::SetConstant3f(LPCSTR szName, const Vector3 & v3Val)
{
	for (int i = 0; i < m_nConstantSize; ++i) {
		if (m_pConstants[i]->SetValue(szName, (void*)&v3Val, sizeof(v3Val))) break;
	}
}

void RS_ShaderDX11::SetConstant4f(LPCSTR szName, const Vector4 & v4Val)
{
	for (int i = 0; i < m_nConstantSize; ++i) {
		if (m_pConstants[i]->SetValue(szName, (void*)&v4Val, sizeof(v4Val))) break;
	}
}

void RS_ShaderDX11::SetConstant4x4f(LPCSTR szName, const Matrix & m4Val)
{
	for (int i = 0; i < m_nConstantSize; ++i) {
		if (m_pConstants[i]->SetValue(szName, (void*)&m4Val, sizeof(m4Val))) break;
	}
}

HRESULT RS_ShaderDX11::DoShade()
{
	if (!m_pRenderer) return E_FAIL;
	ID3D11DeviceContext* pContext = m_pRenderer->GetContext();
	if (!pContext) return E_FAIL;
	if (m_eType == eRS_VertShader) {
		pContext->VSSetShader(m_pVShader, 0, 0);
		if (m_nConstantSize) {
			ID3D11Buffer** pConstantBuffer = new ID3D11Buffer*[m_nConstantSize];
			for (int i = 0; i < m_nConstantSize; ++i) {
				pConstantBuffer[i] = m_pConstants[i]->GetGPUBuffer();
			}
			pContext->VSSetConstantBuffers(0, m_nConstantSize, pConstantBuffer);
		}
	}
	else if (m_eType == eRS_GeometryShader) {
		pContext->GSSetShader(m_pGShader, 0, 0);
	}
	else if (m_eType == eRS_FragmentShader) {
		pContext->PSSetShader(m_pPShader, 0, 0);
		if (m_nConstantSize) {
			ID3D11Buffer** pConstantBuffer = new ID3D11Buffer*[m_nConstantSize];
			for (int i = 0; i < m_nConstantSize; ++i) {
				pConstantBuffer[i] = m_pConstants[i]->GetGPUBuffer();
			}
			pContext->PSSetConstantBuffers(0, m_nConstantSize, pConstantBuffer);
		}
	}
	else if (m_eType == eRS_ComputeShader) {
		pContext->CSSetShader(m_pCShader, 0, 0);
	}
	//apply constant
	for (int i = 0; i < m_nConstantSize; ++i)
		m_pConstants[i]->Apply();

	return S_OK;
}

void RS_ShaderDX11::UnInit()
{
	if (m_eType == eRS_VertShader) {
		m_pVShader->Release();
		m_pVShader = nullptr;
	} else if (m_eType == eRS_FragmentShader) {
		m_pPShader->Release();
		m_pPShader = nullptr;
	} else if (m_eType == eRS_GeometryShader) {
		m_pGShader->Release();
		m_pGShader = nullptr;
	} else if (m_eType == eRS_ComputeShader) {
		m_pCShader->Release();
		m_pCShader = nullptr;
	}
	if (m_pInputSignature) {
		m_pInputSignature->Release();
		m_pInputSignature = nullptr;
	}
	if (m_pConstants) {
		for (int i = 0; i < m_nConstantSize; ++i) {
			m_pConstants[i]->UnInit();
			delete m_pConstants[i];
		}
		delete[] m_pConstants;
	}
	
	

		
}


