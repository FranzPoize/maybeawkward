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
    CL_GraphicContext cl() const
    {
        return mGC;
    }

    Camera &camera()
    {
        return *mCamera;
    }
private:
    CL_GraphicContext &mGC;
    std::shared_ptr<Camera> mCamera;
};

}
#endif // GraphicWrapper_h__
