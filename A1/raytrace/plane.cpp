#include "plane.h"

using namespace std;
using namespace OpenGP;

Plane::Plane(Vec3 normal, Vec3 point)
{
    planeNormal = (normal);
    planePoint = (point);
}

Vec3 Plane::getNormal(void) {
    return planeNormal;
}

Vec3 Plane::getPoint(void) {
    return planePoint;
}
