
#include "rsolidcube.h"

namespace chikkooos
{

    void RSolidCube::create(float w, float h, float l)
    {
        mWidth = w;
        mHeight = h;
        mLength = l;

        float x2 = w/2.0;
        float y2 = h/2.0;
        float z2 = l/2.0;

        float v[] = {-x2, y2, z2, -x2, -y2, z2, x2, -y2, z2, x2, -y2, z2,
                         x2, y2, z2, -x2, y2, z2, x2, y2, z2, x2, -y2, z2, x2, -y2, -z2, x2, -y2, -z2,
                         x2, y2, -z2, x2, y2, z2, x2, y2, -z2, x2, -y2, -z2, -x2, -y2, -z2, -x2, -y2, -
                         z2, -x2, y2, -z2, x2, y2, -z2, -x2, y2, -z2, -x2, -y2, -z2, -x2, -y2, z2, -x2,
                        -y2, z2, -x2, y2, z2, -x2, y2, -z2, -x2, y2, -z2, -x2, y2, z2, x2, y2, z2, x2,
                         y2, z2, x2, y2, -z2, -x2, y2, -z2, -x2, -y2, z2, -x2, -y2, -z2, x2, -y2, -z2,
                         x2, -y2, -z2, x2, -y2, z2, -x2, -y2, z2};

        float n[] = {0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0,
                        1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0,
                        1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0,
                        0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, -1.0, 0.0, 0.0,
                       -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0,
                        0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0,
                        1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0, -1.0, 0.0, 0.0,
                       -1.0, 0.0, 0.0, -1.0, 0.0};

        float t[] = {1.0-1.0/4.0, 3.0/4.0, 1.0-1.0/4.0, 1.0/4.0, 1.0, 1.0/4.0, 1.0, 1.0/4.0, 1.0,
                        3.0/4.0, 1.0-1.0/4.0, 3.0/4.0, 0.0, 3.0/4.0, 0.0, 1.0/4.0, 1.0/4.0, 1.0/4.0,
                        1.0/4.0, 1.0/4.0, 1.0/4.0, 3.0/4.0, 0.0, 3.0/4.0, 1.0/4.0, 3.0/4.0, 1.0/4.0,
                        1.0/4.0, 2.0/4.0, 1.0/4.0, 2.0/4.0, 1.0/4.0, 2.0/4.0, 3.0/4.0, 1.0/4.0,
                        3.0/4.0, 2.0/4.0, 3.0/4.0, 2.0/4.0, 1.0/4.0, 3.0/4.0, 1.0/4.0, 3.0/4.0,
                        1.0/4.0, 3.0/4.0, 3.0/4.0, 2.0/4.0, 3.0/4.0, 1.0, 1.0, 0.0, 1.0, 0.0, 0.0,
                        0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0,
                        0.0, 1.0, 1.0};

        data_p().mVertices.clear();
        data_p().mNormals.clear();
        data_p().mTexCoords.clear();

        data_p().mVertices.insert(data_p().mVertices.begin(), v, v + sizeof(v)/sizeof(v[0]));
        data_p().mNormals.insert(data_p().mNormals.begin(), n, n + sizeof(n)/sizeof(n[0]));
        data_p().mTexCoords.insert(data_p().mTexCoords.begin(), t, t + sizeof(t)/sizeof(t[0]));
    }
}
