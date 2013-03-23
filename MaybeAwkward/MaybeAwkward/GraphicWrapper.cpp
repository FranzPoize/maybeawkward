#include <ClanLib/core.h>
#include <ClanLib/display.h>

#include "GraphicWrapper.h"
#include "Camera.h"

using namespace MA;

GraphicWrapper::GraphicWrapper(CL_GraphicContext &aGC,std::shared_ptr<Camera> aCamera):
	mGC(aGC),
	mCamera(aCamera)
{
}