#include "OpenGP/Image/Image.h"
#include "bmpwrite.h"
#include "Sphere.h"
#include "Plane.h"
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

/*
Vec3 sphereIntersect(Sphere s, Vec3 ray, Vec3 camPos) {
    Vec3 intersection = NULL;
    return intersection;
}
*/

float get_t_value(Plane s, Vec3 rayDirection, Vec3 camPos) {
    float denom = rayDirection.dot(s.getNormal());
    Vec3 PmE = s.getPoint() - camPos;
    float t = s.getNormal().dot(PmE)/denom;
    return t;
}

Vec3 planeIntersect(Plane s, Vec3 rayDirection, Vec3 camPos) {
    Vec3 intersection;
    float denom = rayDirection.dot(s.getNormal());
    Vec3 PmE = s.getPoint() - camPos;
    float t = s.getNormal().dot(PmE)/denom;
    intersection = t*rayDirection + camPos;
    return intersection;
}


int main(int, char**){

    int wResolution = 780;
    int hResolution = 600;
    //int wResolution = 640;
    //int hResolution = 480;
    float aspectRatio = float(wResolution) / float(hResolution);
    // #rows = hResolution, #cols = wResolution
    Image<Colour> image(hResolution, wResolution);

    //CAMERA
    Vec3 w = Vec3(0.0f, 0.0f, -1.0f);   //x (left right)
    Vec3 v = Vec3(0.0f, 1.0f, 0.0f);    //y (up down)
    Vec3 u = Vec3(1.0f, 0.0f, 0.0f);    //z (forward, backward)
    float d = 1.0f;                     //focal length
    Vec3 e = -d*w;                      //camera position

    //BOUNDARIES
    float left = -1.0f*aspectRatio;
    float right = 1.0f*aspectRatio;
    float bottom = -1.0;
    float top = 1.0;

    //SPHERE
    Sphere ball (Vec3(0.0f, 1.0f, -5.0f), 2.0f);

    //LIGHT POSITION
    Vec3 lightPos = Vec3(1.0f, 5.0f, 0.0f);
    float lightInt = 1.0f;

    //PLANE
    Plane floor (Vec3(0.0f, 1.0f, 0.0f), Vec3(0.0f, -2.0f, 0.0f));
    Plane ceiling (Vec3(0.0f, -1.0f, 0.0f), Vec3(0.0f, 3.0f, 0.0f));
    Plane leftWall (Vec3(1.0f, 0.0f, 0.0f), Vec3(-2.0f, -20.0f, 0.0f));
    Plane rightWall (Vec3(-1.0f, 0.0f, 0.0f), Vec3(2.0f, 3.0f, 0.0f));
    Plane backWall (Vec3(0.0f, 0.0f, 1.0f), Vec3(0.0f, 0.0f, -4.0f));

    for (int row = 0; row < image.rows(); ++row) {
        for (int col = 0; col < image.cols(); ++col) {

            //image(row, col) = white();

            /// TODO: build primary rays
            Vec3 pixel = left*u + (col*(right-left)/image.cols())*u;
            pixel += bottom*v + (row*(top-bottom)/image.rows())*v;

            Vec3 rayDirection = pixel - e;
            rayDirection = rayDirection.normalized();

            float lowest_t;



            //PLANE INTERSECTION
            float denom = rayDirection.dot(floor.getNormal());
            if(denom != 0 && denom < 0) {

                Vec3 EmP = floor.getPoint() - e;

                //CALCULATE INTERSECT
                Vec3 intersect = planeIntersect(floor, rayDirection, e);
                Vec3 lightDir = lightPos - intersect;
                lightDir = lightDir.normalized();

                //DOES SPHERE HIT?
                bool hit = false;
                //float hitVal = std::powf(lightDir.dot(lightPos - ball.getPos()), 2) - (lightPos - ball.getPos()).dot(lightPos - ball.getPos()) + ball.getRad()*ball.getRad();
                float hitVal = std::powf(lightDir.dot(ball.getPos() - lightPos), 2) - (ball.getPos() - lightPos).dot(ball.getPos() - lightPos) + ball.getRad()*ball.getRad();
                //cout << hitVal << endl;

                if(hitVal >= 0){
                    hit = true;
                }

                float floor_t_value = get_t_value(floor, rayDirection, e);
                float normaldotlight = floor.getNormal().dot(lightDir);

                if(hit == true) {
                   //image(row, col) = black();
                   image(row, col) = std::abs(normaldotlight)*lightInt*grey()*std::fmaxf(normaldotlight, 0.0f);
                } else {
                   image(row, col) = std::abs(normaldotlight)*lightInt*grey();
                }
                /*
                if(floor_t_value < lowest_t) {
                    lowest_t = floor_t_value;
                    image(row, col) = std::abs(normaldotlight)*lightInt*grey();

                    if(hit == true) {
                       //image(row, col) = black();
                       image(row, col) = std::abs(normaldotlight)*lightInt*grey()*std::fmaxf(normaldotlight, 0.0f);
                    } else {
                       image(row, col) = std::abs(normaldotlight)*lightInt*grey();
                    }

                }*/

            }


            //CEILING INTERSECTION
            float ceilDenom = rayDirection.dot(ceiling.getNormal());
            if(ceilDenom != 0 && ceilDenom < 0) {
            //if(ceilDenom != 0) {

                Vec3 EmP = ceiling.getPoint() - e;

                //CALCULATE INTERSECT
                Vec3 intersect = planeIntersect(ceiling, rayDirection, e);
                Vec3 lightDir = lightPos - intersect;
                lightDir = lightDir.normalized();

                float ceil_t_value = get_t_value(ceiling, rayDirection, e);
                lowest_t = ceil_t_value;

                float normaldotlight = ceiling.getNormal().dot(lightDir);

                image(row, col) = std::abs(normaldotlight)*lightInt*grey();

            }

            //LEFT WALL INTERSECTION
            float leftDenom = rayDirection.dot(leftWall.getNormal());
            if(leftDenom != 0 && leftDenom < 0) {
            //if(leftDenom != 0) {
                Vec3 EmP = leftWall.getPoint() - e;

                //CALCULATE INTERSECT
                Vec3 intersect = planeIntersect(leftWall, rayDirection, e);
                Vec3 lightDir = lightPos - intersect;
                lightDir = lightDir.normalized();

                float left_t_value = get_t_value(leftWall, rayDirection, e);
                float normaldotlight = leftWall.getNormal().dot(lightDir);
                if(left_t_value < lowest_t) {
                    lowest_t = left_t_value;
                    image(row, col) = std::abs(normaldotlight)*lightInt*grey();
                }


            }

            //RIGHT WALL INTERSECTION
            float rightDenom = rayDirection.dot(rightWall.getNormal());
            if(rightDenom != 0 && rightDenom < 0) {
            //if(rightDenom != 0) {
                Vec3 EmP = rightWall.getPoint() - e;

                //CALCULATE INTERSECT
                Vec3 intersect = planeIntersect(rightWall, rayDirection, e);
                Vec3 lightDir = lightPos - intersect;
                lightDir = lightDir.normalized();

                float right_t_value = get_t_value(rightWall, rayDirection, e);
                float normaldotlight = rightWall.getNormal().dot(lightDir);
                if(right_t_value < lowest_t) {
                    lowest_t = right_t_value;
                    image(row, col) = std::abs(normaldotlight)*lightInt*grey();
                }

            }

            //BACK WALL INTERSECTION
            float backDenom = rayDirection.dot(backWall.getNormal());
            if(backDenom != 0 && backDenom < 0) {
            //if(backDenom != 0) {

                Vec3 EmP = backWall.getPoint() - e;

                //CALCULATE INTERSECT
                Vec3 intersect = planeIntersect(backWall, rayDirection, e);
                Vec3 lightDir = lightPos - intersect;
                lightDir = lightDir.normalized();



                float back_t_value = get_t_value(backWall, rayDirection, e);
                float normaldotlight = backWall.getNormal().dot(lightDir);
                if(back_t_value < lowest_t) {
                   lowest_t = back_t_value;
                   image(row, col) = std::abs(normaldotlight)*lightInt*grey();
                }

            }

            //SPHERE INTERSECTION
            Vec3 EsubC = e - ball.getPos();
            float disc = std::powf(rayDirection.dot(EsubC), 2) - EsubC.dot(EsubC) + ball.getRad()*ball.getRad();

            if(disc >= 0) {
                //calculate shading and then colour ball
                float t = -rayDirection.dot(EsubC) - std::sqrtf(disc);
                Vec3 pos = e + t*rayDirection;
                Vec3 normal = (pos - ball.getPos()) / ball.getRad();
                Vec3 lightDir = lightPos - pos;
                lightDir = lightDir.normalized();

                //SPECULAR
                float lightMag = lightDir(0)*lightDir(0) + lightDir(1)*lightDir(1) + lightDir(2)*lightDir(2);
                lightMag = std::sqrt(lightMag);
                float rayMag = std::sqrt(EsubC(0)*EsubC(0) + EsubC(1)*EsubC(1) +  EsubC(2)*EsubC(2));
                Vec3 h = (lightDir + EsubC)/(lightMag + rayMag);

                image(row, col) = std::fmaxf(normal.dot(lightDir), 0.0f)*lightInt*red() + std::pow(std::fmaxf(normal.dot(h), 0.0f), 15)*red();
            }

       }
    }

    bmpwrite("../../out.bmp", image);
    imshow(image);

    return EXIT_SUCCESS;
}
