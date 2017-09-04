#ifndef DATA_TYPE_H
#define DATA_TYPE_H

enum eRS_VertDataFormat
{
	eRS_VertDataFormat_Position,
	eRS_VertDataFormat_Normal,
	eRS_VertDataFormat_Color,
	eRS_VertDataFormat_TextureCoord,
	eRS_VertDataFormat_Count,
};


enum eRS_ResourceFormat
{
	eRS_ResourceFormat_R8B8G8A8,
	eRS_ResourceFormat_R8B8G8,
	eRS_ResourceFormat_R8,
	eRS_ResourceFormat_Count,
};


enum eRS_StateType
{
	eRS_StateType_Sampler,
	eRS_StateType_Blend,
	eRS_StateType_Depth,
	eRS_StateType_Rasterizer,
	eRS_StateType_Count,
};

enum eRS_ComparisonFunction
{
	eRS_Never,
	eRS_Less,
	eRS_Equal,
	eRS_LEqual,
	eRS_Greater,
	eRS_NotEqual,
	eRS_GEqual,
	eRS_Always,
	eRS_DepthStencilFunction_Count,
};

#ifdef _WIN32

typedef LPCSTR  LPCSTR;
typedef byte	byte;
typedef HRESULT HRESULT;

typedef UINT16 UINT16;
typedef UINT32 UINT32;

#endif

#endif