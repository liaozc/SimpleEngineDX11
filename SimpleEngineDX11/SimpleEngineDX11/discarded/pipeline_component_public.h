#ifndef PIPELINE_H
#define PIPELINE_H

class iEngine;

class iPipelineComponent
{
public:
	virtual void Init(iEngine* pEngine) = 0;
	virtual void OnAttached() = 0;
	virtual void OnDetached() = 0;
};

#endif
