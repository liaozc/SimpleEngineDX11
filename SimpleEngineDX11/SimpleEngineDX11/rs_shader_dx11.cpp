#include "rs_shader_dx11.h"
#include "rs_renderer_dx11.h"
#include <d3dcompiler.h>


RS_ShaderDX11::RS_ShaderDX11(RS_RendererDX11* pRenderer)
{
	m_pRenderer = pRenderer;
	m_pVShader = nullptr;
	m_pInputSignature = nullptr;
	m_pConstants = nullptr;
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
	ID3DBlob* pShaderBuff = nullptr;
	ID3DBlob* pError = nullptr;
	bool success = false;
	if (SUCCEEDED(D3DCompile(pSource, uSize, "shader", nullptr, nullptr, "main", target, complierFlag, 0, &pShaderBuff, &pError))) {
		if (type == eRS_VertShader) {
			if (SUCCEEDED(pDevice->CreateVertexShader(pShaderBuff->GetBufferPointer(), pShaderBuff->GetBufferSize(), NULL, &m_pVShader))) {
				if (SUCCEEDED(D3DGetInputSignatureBlob(pShaderBuff->GetBufferPointer(), pShaderBuff->GetBufferSize(), &m_pInputSignature))) {
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
		printf("error complier :%s \n",pError->GetBufferPointer());
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

HRESULT RS_ShaderDX11::DoShade()
{
	if (!m_pRenderer) return E_FAIL;
	ID3D11DeviceContext* pContext = m_pRenderer->GetContext();
	if (!pContext) return E_FAIL;
	if (m_eType == eRS_VertShader) {
		pContext->VSSetShader(m_pVShader, nullptr, 0);
		return S_OK;
	}
	return E_FAIL;
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
	

		
}


