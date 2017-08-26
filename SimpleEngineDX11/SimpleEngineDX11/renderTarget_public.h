#ifndef WINDOW_PUBLIC_H
#define WINDOW_PUBLIC_H

#include "platform.h"

class iEngine;

class iRenderTarget
{
public:
	virtual void init(iEngine* pEngine) = 0;
	virtual void doRender() = 0;
};

#endif
