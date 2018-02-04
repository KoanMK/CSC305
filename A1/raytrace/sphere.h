#ifndef SPHERE_H
#define SPHERE_H

#include "OpenGP/Image/Image.h"
//#include "light.h"
//#include "camera.h"

using namespace std;
using namespace OpenGP;

class Sphere
{
    Vec3 spherePos;
    float sphereRad;

public:
    Sphere(Vec3 position, float radius);
    float getRad(void);
    Vec3 getPos(void);
};

#endif // SPHERE_H
