#ifndef RS_SHADER_PUBLIC_H
#define RS_SHADER_PUBLIC_H

#include "data_type.h"

enum eRS_ShaderType
{
	eRS_VertShader,
	eRS_FragmentShader,
	eRS_GeometryShader,
	eRS_ComputeShader,
	eRS_ShaderType_Count,
};

class iRS_Renderer;

class iRS_Shader
{
public:
	virtual eRS_ShaderType* GetType() const = 0;
	virtual HRESULT DoShade(iRS_Renderer* pRenderer) = 0;
};

#endif
