#ifndef VIEW_PUBLIC_H
#define VIEW_PUBLIC_H

#include "pipeline_component_public.h"

class iCamera;

class iViewPort : public iPipelineComponent
{
public:
	virtual iCamera* GetCamera() const = 0;
};

#endif
