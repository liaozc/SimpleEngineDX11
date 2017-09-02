#include "rs_shader_manager.h"

RS_ShaderManagerDX11::RS_ShaderManagerDX11(RS_RendererDX11 * pRenderer)
{
	m_pRenderer = pRenderer;
}

HRESULT RS_ShaderManagerDX11::CreateShadersFromFile(const char * pFilePath, iRS_Shader **& pShaders, int & nSize, bool bManagered)
{
	if (!pFilePath) return E_FAIL;
	FILE *file = fopen(pFilePath, "rb");
	if (!file) return E_FAIL;
	fseek(file, 0, SEEK_END);
	int length = ftell(file);
	fseek(file, 0, SEEK_SET);
	if (length <= 0) {
		pShaders = nullptr;
		nSize = 0;
		fclose(file);
		return E_FAIL;
	}
	char* pSource = new char[length + 1];
	fread(pSource, length, 1, file);
	fclose(file);
	pSource[length] = '\0';
	nSize = CreateShadersFromMemory(pSource, length, pShaders, bManagered);
	if (nSize == 0) return E_FAIL;
	return S_OK;
}

int RS_ShaderManagerDX11::CreateShadersFromMemory(char * const pSource, unsigned uSize, iRS_Shader **& pShaders, bool bManagered)
{
	if (!m_pRenderer) {
		pShaders = nullptr;
		return 0;
	}

	static LPCSTR shader_headers[] = {
		"[Vertex Shader]",
		"[Geometry Shader]",
		"[Fragment Shader]",
		"[Compute Shader]",
	};
	static size_t header_lens[] = {
		strlen(shader_headers[0]),
		strlen(shader_headers[1]),
		strlen(shader_headers[2]),
		strlen(shader_headers[3]),
	};

	if (pSource == nullptr || uSize == 0) {
		printf("error source");
		pShaders = nullptr;
		return 0;
	}

	char* pVS = strstr(pSource, shader_headers[0]);
	char* pGS = strstr(pSource, shader_headers[1]);
	char* pFS = strstr(pSource, shader_headers[2]);
	char* pCS = strstr(pSource, shader_headers[3]);
	char* pHeader = pSource;
	int shaderSize = (pVS?1:0) + (pGS ? 1 : 0) + (pFS ? 1 : 0) + (pCS ? 1 : 0);
	if (shaderSize == 0) {
		printf("error source");
		pShaders = nullptr;
		return 0;
	}
	pShaders = new iRS_Shader*[shaderSize];
	memset(pShaders, 0, shaderSize * sizeof(iRS_Renderer*));
	int index = 0;
	bool bFail = false;
	if (pVS) {//Vert Shader
		*pVS = '\0';
		pVS += header_lens[0];
	}
	if (pGS) {//Geometry Shader
		*pGS = '\0';
		pGS += header_lens[1];
	}
	if (pFS) {//Fragment Shader
		*pFS = '\0';
		pFS += header_lens[2];
	}
	if (pCS) {//Compute Shader
		*pCS = '\0';
		pCS += header_lens[3];
	}
	int headerOffset = strlen(pHeader);
	char * const pDest = new char[uSize];
	memcpy(pDest, pHeader, headerOffset);
	if (pVS) {
		int contentOffset = strlen(pVS);
		memcpy(pDest + headerOffset, pVS, contentOffset);
		pDest[headerOffset + contentOffset] = '\0';
		pShaders[index] = new RS_ShaderDX11(m_pRenderer);
		if (FAILED(pShaders[index]->CompilerFromMemory(pDest, contentOffset + headerOffset, eRS_VertShader))) {
			bFail = true;
		}
		index++;
	}
	if (pGS && !bFail) {
		int contentOffset = strlen(pGS);
		memcpy(pDest + headerOffset, pGS, contentOffset);
		pDest[headerOffset + contentOffset] = '\0';
		pShaders[index] = new RS_ShaderDX11(m_pRenderer);
		if (FAILED(pShaders[index]->CompilerFromMemory(pDest, headerOffset + contentOffset, eRS_GeometryShader))) {
			bFail = true;
		}
		index++;
	}
	if (pFS && !bFail) {
		int contentOffset = strlen(pFS);
		memcpy(pDest + headerOffset, pFS, contentOffset);
		pDest[headerOffset + contentOffset] = '\0';
		pShaders[index] = new RS_ShaderDX11(m_pRenderer);
		if (FAILED(pShaders[index]->CompilerFromMemory(pDest, headerOffset + contentOffset, eRS_FragmentShader))) {
			bFail = true;
		}
		index++;
	}
	if (pCS && !bFail) {
		int contentOffset = strlen(pCS);
		memcpy(pDest + headerOffset, pCS, contentOffset);
		pDest[headerOffset + contentOffset] = '\0';
		pShaders[index] = new RS_ShaderDX11(m_pRenderer);
		if (FAILED(pShaders[index]->CompilerFromMemory(pDest, headerOffset + contentOffset, eRS_ComputeShader))) {
			bFail = true;
		}
		index++;
	}

	if (bFail) {
		for (int i = 0; i < 4; ++i) {
			if (pShaders[i])
				delete pShaders[i];
		}
		memset(pShaders, 0, 4 * sizeof(iRS_Renderer*));
		delete[] pShaders;
		pShaders = nullptr;
		shaderSize = 0;
	}
	if (bManagered && pShaders) {
		for (int i = 0; i < shaderSize; ++i) {
			if (pShaders[i]) m_vShaders.push_back(pShaders[i]);
		}
	}
	return shaderSize;
}

int RS_ShaderManagerDX11::UnInit()
{
	size_t uSize = m_vShaders.size();
	for (size_t i = 0; i < uSize; ++i) {
		if (m_vShaders[i]) {
			m_vShaders[i]->UnInit();
			delete m_vShaders[i];
			m_vShaders[i] = nullptr;
		}
	}
	return 0;
}

