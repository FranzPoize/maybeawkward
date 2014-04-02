#include <ClanLib/core.h>
#include <ClanLib/display.h>

#include "GraphicWrapper.h"
#include "Camera.h"

using namespace MA;

GraphicWrapper::GraphicWrapper(clan::GraphicContext &aGC,std::shared_ptr<Camera> aCamera):
	mGC(aGC),
	mCamera(aCamera)
{
}