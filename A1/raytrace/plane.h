#ifndef PLANE_H
#define PLANE_H

#include "OpenGP/Image/Image.h"
//#include "light.h"
//#include "camera.h"

using namespace std;
using namespace OpenGP;

class Plane
{
    Vec3 planeNormal;
    Vec3 planePoint;

public:
    Plane(Vec3 normal, Vec3 point);
    Vec3 getNormal(void);
    Vec3 getPoint(void);
};

#endif // PLANE_H
