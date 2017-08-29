#ifndef WINDOW_PUBLIC_H
#define WINDOW_PUBLIC_H

#include "platform.h"
#include "pipeline_component_public.h"

class iEngine;

enum eRenderTargetType {
	eRT_Type_Color,
	eRT_Type_DepthStencil,
	eRT_Type_Window,
	eRT_Type_Count
};

class iRenderTarget : public iPipelineComponent
{
public:
	virtual eRenderTargetType GetType() const = 0;
};

#endif
