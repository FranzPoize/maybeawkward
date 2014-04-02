
#ifndef GDP4_COLLISIONS_H
#define GDP4_COLLISIONS_H

#include <ClanLib/core.h>

namespace MA {

struct Rect {
    float x, y, width, height;

    Rect(float aX = 0, float aY = 0, float aW = 0, float aH = 0)
    : x(aX), y(aY), width(aW), height(aH) {}


    operator clan::Rectf() 
    {
        return clan::Rectf(x, y-height, clan::Sizef(width, height));
    }


};

bool rectCollision(const Rect& r1, const Rect& r2);


void test_rectCollision();

} // namespace

#endif
