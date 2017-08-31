#ifndef RS_SHADER_DX11_H
#define RS_SHADER_DX11_H

#include <d3d11.h>
#include "rs_shader_dx11.h"
#include "stl_containers.h"
#include <string>

class RS_ShaderDX11 : public iRS_Shader
{
public:
	virtual eRS_ShaderType* GetType() const { return m_eType; }
	virtual HRESULT DoShade(iRS_Renderer* pRenderer);

protected:
	eRS_ShaderType m_eType;
	union {
		ID3D11VertexShader *m_pVShader;
		ID3D11PixelShader *m_pPShader;
		ID3D11GeometryShader *m_pGShader;
		ID3D11ComputeShader *m_pGShader;
	};
	ID3DBlob * m_pInputSignature;
	ID3D11Buffer ** m_pConstants;
	int m_nConstantSize;

};



#endif
