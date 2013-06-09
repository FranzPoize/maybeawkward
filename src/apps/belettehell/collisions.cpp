
#include "collisions.h"
#include <assert.h>
#include <stdio.h>

namespace MA {

bool rectCollision(const Rect& r1, const Rect& r2)
{
    float ax1 = r1.x;
    float ax2 = r1.x + r1.width;
    float bx1 = r2.x;
    float bx2 = r2.x + r2.width;
    float ay1 = r1.y;
    float ay2 = r1.y - r1.height;
    float by1 = r2.y;
    float by2 = r2.y - r2.height;
    return (
        (ax2 > bx1) && (bx2 > ax1)
        &&(ay2 < by1) && (by2 < ay1)
    );
}

void test_rectCollision() {
    Rect r1(0.0, 0.0, 1.0, 1.0);
    Rect r2(2.0, 2.0, 1.0, 1.0);
    assert(!rectCollision(r1, r2));
    assert(!rectCollision(r2, r1));
    Rect r3(0.5, 0.0, 1.0, 1.0);
    assert(rectCollision(r1, r3));
    assert(rectCollision(r3, r1));
    Rect r4(-0.5, 0.2, 3.0, 0.1);
    assert(rectCollision(r1, r4));
    assert(rectCollision(r4, r1));
    Rect r5(0.5, -0.2, 0.2, 3.0);
    assert(rectCollision(r1, r5));
    assert(rectCollision(r5, r1));

    assert(rectCollision(r4, r5));
    assert(rectCollision(r5, r4));

    Rect r6(-0.5, -0.5, 0.9, 0.9);
    assert(rectCollision(r1, r6));
    assert(rectCollision(r6, r1));


    Rect r7(-0.5, -0.5, 0.1, 0.1);
    assert(!rectCollision(r1, r7));
    assert(!rectCollision(r7, r1));
    Rect r8(1.1, 1.0, 0.1, 0.1);
    assert(!rectCollision(r1, r8));
    assert(!rectCollision(r8, r1));
    Rect r9(0.1, 2.0, 0.1, 0.1);
    assert(!rectCollision(r1, r9));
    assert(!rectCollision(r9, r1));
};

} // namespace

#ifdef COLLISIONS_TEST_MAIN
// g++ src/collisions.cpp -g -o test_collisions -DCOLLISIONS_TEST_MAIN
int main(int argc, const char** argv) {
    MA::test_rectCollision();
    return 0;
}

#endif

