#ifndef GraphicWrapper_h__
#define GraphicWrapper_h__

#include <memory>

#include <ClanLib/core.h>
#include <ClanLib/display.h>

namespace MA
{
class Camera;

class GraphicWrapper
{
public:
	GraphicWrapper(clan::GraphicContext &aGC,std::shared_ptr<Camera> aCamera);

    clan::GraphicContext& cl() const
    {
        return mGC;
    }

    Camera &camera()
    {
        return *mCamera;
    }
private:
    clan::GraphicContext &mGC;
    std::shared_ptr<Camera> mCamera;
};

}
#endif // GraphicWrapper_h__
