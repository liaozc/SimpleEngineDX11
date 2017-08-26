
#include "platform.h"
#include "engine_public.h"

extern "C" iEngine* CreateSimpleEngine(EngineOption& option);

#include "renderTarget_public.h"

iRenderTarget* CreateRTWindow(wndHandle hwnd);
