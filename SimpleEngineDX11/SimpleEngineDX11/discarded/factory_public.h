
#include "platform.h"
#include "engine_public.h"

extern "C" iEngine* CreateSimpleEngine(EngineOption& option);

#include "render_target_public.h"

extern "C" iRenderTarget* CreateRTWindow(iEngine* pEngine, wndHandle hwnd);

#include "scene_public.h"

extern "C" iScene* CreateScene(iEngine* pEngine);

#include "view_public.h"

extern "C" iView* CreateView(iEngine* pEngine);

#include "camera_public.h"

extern "C" iCamera* CreateSimpleCamera();
