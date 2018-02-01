#include "OpenGP/Image/Image.h"
#include "bmpwrite.h"
#include <iostream>

//look at scratchpixel.com for tutorials and stuff

using namespace std;
using namespace OpenGP;

using Colour = Vec3; // RGB Value
Colour red() { return Colour(1.0f, 0.0f, 0.0f); }
Colour white() { return Colour(1.0f, 1.0f, 1.0f); }
Colour black() { return Colour(0.0f, 0.0f, 0.0f); }
Colour green() { return Colour(0.0f, 1.0f, 0.0f); }
Colour grey() { return Colour(0.8f, 0.8f, 0.8f); }

int main(int, char**){

    int wResolution = 640;
    int hResolution = 480;
    float aspectRatio = float(wResolution) / float(hResolution);
    // #rows = hResolution, #cols = wResolution
    Image<Colour> image(hResolution, wResolution);

    /// TODO: define camera position and sphere position here
    // example: Vec3 spherePos = Vec3(0, 5, 0);

    //CAMERA
    Vec3 w = Vec3(0.0f, 0.0f, -1.0f);   //x-aix (left right)
    Vec3 v = Vec3(0.0f, 1.0f, 0.0f);    //y (up down)
    Vec3 u = Vec3(1.0f, 0.0f, 0.0f);    //z(forward, backward)
    float d = 1.0f;                     //focal length
    Vec3 e = -d*w;                      //camera position

    //BOUNDARIES
    float left = -1.0f*aspectRatio;
    float right = 1.0f*aspectRatio;
    float bottom = -1.0;
    float top = 1.0;

    //SPHERE
    Vec3 spherePos = Vec3(0.0f, 1.0f, -6.0f);
    float sphereRadius = 3.0f;

    //LIGHT POSITION
    Vec3 lightPos = Vec3(0.0f, 4.0f, 2.0f);
    float lightInt = 1.0f;

    //PLANE
    Vec3 planeNormal = Vec3(0.0f, 1.0f, 0.0f);
    Vec3 p = Vec3(0.0f, -1.0f, 0.0f);

    for (int row = 0; row < image.rows(); ++row) {
        for (int col = 0; col < image.cols(); ++col) {

            /// TODO: build primary rays
            Vec3 pixel = left*u + (col*(right-left)/image.cols())*u;
            pixel += bottom*v + (row*(top-bottom)/image.rows())*v;

            Vec3 rayDirection = pixel - e;
            rayDirection = rayDirection.normalized();

            //PLANE INTERSECTION
            float denom = rayDirection.dot(planeNormal);
            if(denom != 0 && denom < 0) {

                //TODO: PHONG SHADING
                Vec3 EmP = p - e;
                float length = planeNormal.dot(EmP)/denom;
                Vec3 intersect = length*rayDirection + e;
                Vec3 lightDir = lightPos - intersect;
                lightDir = lightDir.normalized();
                float normaldotlight = planeNormal.dot(lightDir);
                image(row, col) = std::abs(normaldotlight)*lightInt*grey();
            }

            /// TODO: ray sphere intersection and shading
            //SPHERE INTERSECTION
            Vec3 EsubC = e - spherePos;
            float disc = std::powf(rayDirection.dot(EsubC), 2) - EsubC.dot(EsubC) + sphereRadius*sphereRadius;

            if(disc >= 0) {
                //calculate shading and then colour ball
                float t = -rayDirection.dot(EsubC) - std::sqrtf(disc);
                Vec3 pos = e + t*rayDirection;
                Vec3 normal = (pos - spherePos) / sphereRadius;
                Vec3 lightDir = lightPos - pos;
                lightDir = lightDir.normalized();
                image(row, col) = std::fmaxf(normal.dot(lightDir), 0.0f)*lightInt*red();

                //image(row, col) = red();
            } else {
                //image(row, col) = black();
            }

            /// EXAMPLE: using "image(row,col) = colour;" to set pixel values
            /*
            if (row > 0 && row < 200 && col > 0 && col < 200)  {
                image(row,col) = red();
            } else {
                image(row,col) = white();
            }
            */

       }
    }

    bmpwrite("../../out.bmp", image);
    imshow(image);

    return EXIT_SUCCESS;
}
