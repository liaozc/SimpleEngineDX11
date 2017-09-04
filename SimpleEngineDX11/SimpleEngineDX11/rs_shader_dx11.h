#ifndef RS_SHADER_DX11_H
#define RS_SHADER_DX11_H

#include <d3d11.h>
#include "rs_shader_public.h"
#include "stl_containers.h"
#include "rs_buffer_dx11.h"
#include <string>
#include "rs_buffer_dx11.h"


class RS_RendererDX11;

class RS_ShaderDX11 : public iRS_Shader
{
public:
	RS_ShaderDX11(RS_RendererDX11* pRenderer);
	virtual eRS_ShaderType GetType() const { return m_eType; }
	virtual HRESULT CompilerFromMemory(const char* pSource, unsigned uSize, eRS_ShaderType type);
	ID3DBlob* GetInputSignature() const { return m_pInputSignature; }
	virtual void SetConstant1f(LPCSTR szName, float fVal);
	virtual void SetConstant2f(LPCSTR szName, const Vector2& v2Val);
	virtual void SetConstant3f(LPCSTR szName, const Vector3& v3Val);
	virtual void SetConstant4f(LPCSTR szName, const Vector4& v4Val);
	virtual void SetConstant4x4f(LPCSTR szName, const Matrix& m4Val);
	virtual HRESULT DoShade();
	virtual void UnInit();
protected:
	eRS_ShaderType m_eType;
	union {
		ID3D11VertexShader *m_pVShader;
		ID3D11PixelShader *m_pPShader;
		ID3D11GeometryShader *m_pGShader;
		ID3D11ComputeShader *m_pCShader;
	};
	ID3DBlob * m_pInputSignature;
	//for constant buffer
	RS_ConstantBufferDX11** m_pConstants;
	int m_nConstantSize;
	
	RS_RendererDX11* m_pRenderer;
};



#endif
