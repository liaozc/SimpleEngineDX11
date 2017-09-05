#ifndef RS_SHADER_PUBLIC_H
#define RS_SHADER_PUBLIC_H

#include "ref_public.h"
#include "data_type.h"
#include "mth_math.h"

enum eRS_ShaderType
{
	eRS_STNone,
	eRS_VertShader,
	eRS_GeometryShader,
	eRS_FragmentShader,
	eRS_ComputeShader,
	eRS_ShaderType_Count,
};

class iRS_Renderer;

class iRS_Shader : public iRef
{
public:
	virtual ~iRS_Shader() {}
	virtual eRS_ShaderType GetType() const = 0;
	virtual HRESULT CompilerFromMemory(const char* pSource, unsigned uSize, eRS_ShaderType type) = 0;
	virtual void SetConstant1f(LPCSTR szName, float fVal) = 0;
	virtual void SetConstant2f(LPCSTR szName, const Vector2& v2Val) = 0;
	virtual void SetConstant3f(LPCSTR szName, const Vector3& v3Val) = 0;
	virtual void SetConstant4f(LPCSTR szName, const Vector4& v4Val) = 0;
	virtual void SetConstant4x4f(LPCSTR szName, const Matrix& m4Val) = 0;
	virtual HRESULT DoShade() = 0;
};

#endif
