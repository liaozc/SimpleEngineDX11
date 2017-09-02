#ifndef RS_SHADER_PUBLIC_H
#define RS_SHADER_PUBLIC_H

#include "data_type.h"

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

class iRS_Shader
{
public:
	virtual eRS_ShaderType GetType() const = 0;
	virtual HRESULT DoShade() = 0;
	virtual HRESULT CompilerFromMemory(const char* pSource, unsigned uSize, eRS_ShaderType type) = 0;
	virtual void UnInit() = 0;
};

#endif
