#include "sphere.h"

using namespace std;
using namespace OpenGP;

Sphere::Sphere(Vec3 position, float radius)
{
    spherePos = (position);
    sphereRad = (radius);
}

float Sphere::getRad(void) {
    return sphereRad;
}

Vec3 Sphere::getPos(void) {
    return spherePos;
}
