#ifndef RS_SHADER_MANAGER_H
#define RS_SHADER_MANAGER_H

#include "rs_shader_dx11.h"
#include "stl_containers.h"
class RS_RendererDX11;

typedef std::vector<iRS_Shader*> t_ShaderArray;

class RS_ShaderManagerDX11
{
public:
	RS_ShaderManagerDX11(RS_RendererDX11* pRenderer);
	HRESULT CreateShadersFromFile(const char* pFilePath,iRS_Shader**& pShaders,int& nSize,bool bManagered = true);
	int CreateShadersFromMemory(char* const pSource, unsigned uSize,iRS_Shader**& pShaders, bool bManagered = true);
	int UnInit();
protected:
	RS_RendererDX11* m_pRenderer;
	t_ShaderArray m_vShaders;
};

#endif
