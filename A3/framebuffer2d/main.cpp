#include <OpenGP/GL/Application.h>
#include <OpenGP/external/LodePNG/lodepng.cpp>
#include <math.h>

using namespace OpenGP;

const int width=720, height=720;
typedef Eigen::Transform<float,3,Eigen::Affine> Transform;
#define POINTSIZE 10.0f

const char* fb_vshader =
#include "fb_vshader.glsl"
;
const char* fb_fshader =
#include "fb_fshader.glsl"
;
const char* quad_vshader =
#include "quad_vshader.glsl"
;
const char* quad_fshader =
#include "quad_fshader.glsl"
;

const char* line_vshader =
#include "line_vshader.glsl"
;
const char* line_fshader =
#include "line_fshader.glsl"
;

const char* selection_vshader =
#include "selection_vshader.glsl"
;
const char* selection_fshader =
#include "selection_fshader.glsl"
;


const float SpeedFactor = 0.2;
void init();
void quadInit(std::unique_ptr<GPUMesh> &quad);
void loadTexture(std::unique_ptr<RGBA8Texture> &texture, const char* filename);
void drawScene(float timeCount);

std::unique_ptr<GPUMesh> quad;

std::unique_ptr<Shader> quadShader;
std::unique_ptr<Shader> fbShader;

std::unique_ptr<RGBA8Texture> ship;
std::unique_ptr<RGBA8Texture> stars;
std::unique_ptr<RGBA8Texture> moon;
std::unique_ptr<RGBA8Texture> bender;

std::unique_ptr<Shader> lineShader;
std::unique_ptr<GPUMesh> line;
std::vector<Vec2> controlPoints;

/// Selection with framebuffer pointers
std::unique_ptr<Shader> selectionShader;
std::unique_ptr<Framebuffer> selectionFB;
std::unique_ptr<RGBA8Texture> selectionColor;
std::unique_ptr<D16Texture> selectionDepth;


int main(int, char**){

    Application app;
    init();

    /// Selection shader
    selectionShader = std::unique_ptr<Shader>(new Shader());
    selectionShader->verbose = true;
    selectionShader->add_vshader_from_source(selection_vshader);
    selectionShader->add_fshader_from_source(selection_fshader);
    selectionShader->link();
    /// Framebuffer for selection shader
    selectionFB = std::unique_ptr<Framebuffer>(new Framebuffer());
    selectionColor = std::unique_ptr<RGBA8Texture>(new RGBA8Texture());
    selectionColor->allocate(width,height);
    selectionDepth = std::unique_ptr<D16Texture>(new D16Texture());
    selectionDepth->allocate(width,height);
    selectionFB->attach_color_texture(*selectionColor);
    selectionFB->attach_depth_texture(*selectionDepth);

    // Mouse position and selected point
    Vec2 pixelPosition = Vec2(0,0);
    Vec2 position = Vec2(0,0);
    Vec2 *selection = nullptr;
    int offsetID = 0;

    // Display callback
    Window& window = app.create_window([&](Window&){
        glViewport(0,0,width,height);
        glClear(GL_COLOR_BUFFER_BIT);
        glPointSize(POINTSIZE);
        drawScene(glfwGetTime());

        lineShader->bind();

        // Draw line white
        lineShader->set_uniform("selection", -1);
        line->set_attributes(*lineShader);
        line->set_mode(GL_LINE_STRIP);
//        line->draw();

        // Draw points white and selected point blue
        if(selection!=nullptr) lineShader->set_uniform("selection", int(selection-&controlPoints[0]));
        line->set_mode(GL_POINTS);
        line->draw();

        lineShader->unbind();
    });
    window.set_title("Mouse");
    window.set_size(width, height);

    // Mouse movement callback
    window.add_listener<MouseMoveEvent>([&](const MouseMoveEvent &m){
        // Mouse position in clip coordinates
        pixelPosition = m.position;
        Vec2 p = 2.0f*(Vec2(m.position.x()/width,-m.position.y()/height) - Vec2(0.5f,-0.5f));
        if( selection && (p-position).norm() > 0.0f) {
            selection->x() = position.x();
            selection->y() = position.y();
            line->set_vbo<Vec2>("vposition", controlPoints);
        }
        position = p;
    });

    // Mouse click callback
    window.add_listener<MouseButtonEvent>([&](const MouseButtonEvent &e){
        // Mouse selection case
        if( e.button == GLFW_MOUSE_BUTTON_LEFT && !e.released) {

            /// Draw element id's to framebuffer
            selectionFB->bind();
            glViewport(0,0,width, height);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color must be 1,1,1,1
            glPointSize(POINTSIZE);
            selectionShader->bind();
            selectionShader->set_uniform("offsetID", offsetID);
            line->set_attributes(*selectionShader);
            line->set_mode(GL_POINTS);
            line->draw();
            selectionShader->unbind();
            glFlush();
            glFinish();

            selection = nullptr;
            unsigned char a[4];
            glReadPixels(int(pixelPosition[0]), height - int(pixelPosition[1]), 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &a);
            selection = &controlPoints[0] + (int)a[0];
            selectionFB->unbind();
        }
        // Mouse release case
        if( e.button == GLFW_MOUSE_BUTTON_LEFT && e.released) {
            if(selection) {
                selection->x() = position.x();
                selection->y() = position.y();
                selection = nullptr;
                line->set_vbo<Vec2>("vposition", controlPoints);
            }
        }
    });
    return app.run();
}

void init(){
    glClearColor(1,1,1, /*solid*/1.0 );

    fbShader = std::unique_ptr<Shader>(new Shader());
    fbShader->verbose = true;
    fbShader->add_vshader_from_source(fb_vshader);
    fbShader->add_fshader_from_source(fb_fshader);
    fbShader->link();

    quadShader = std::unique_ptr<Shader>(new Shader());
    quadShader->verbose = true;
    quadShader->add_vshader_from_source(quad_vshader);
    quadShader->add_fshader_from_source(quad_fshader);
    quadShader->link();

    quadInit(quad);

    loadTexture(ship, "ship.png");
    loadTexture(bender, "bender.png");
    loadTexture(moon, "moon.png");
    loadTexture(stars, "space2.png");

    lineShader = std::unique_ptr<Shader>(new Shader());
    lineShader->verbose = true;
    lineShader->add_vshader_from_source(line_vshader);
    lineShader->add_fshader_from_source(line_fshader);
    lineShader->link();

    controlPoints = std::vector<Vec2>();
//    controlPoints.push_back(Vec2(-0.7f, 1.0f));       //nice points
//    controlPoints.push_back(Vec2(-0.2f, -1.2f));
//    controlPoints.push_back(Vec2( 1.7f, 0.2f));
    controlPoints.push_back(Vec2(-0.7f, 0.95f));        //visible points
    controlPoints.push_back(Vec2(-0.2f, -0.95f));
    controlPoints.push_back(Vec2( 0.95f, 0.2f));

    line = std::unique_ptr<GPUMesh>(new GPUMesh());
    line->set_vbo<Vec2>("vposition", controlPoints);
    std::vector<unsigned int> indices = {0,1,2};
    line->set_triangles(indices);
}

void quadInit(std::unique_ptr<GPUMesh> &quad) {
    quad = std::unique_ptr<GPUMesh>(new GPUMesh());
    std::vector<Vec3> quad_vposition = {
        Vec3(-1, -1, 0),
        Vec3(-1,  1, 0),
        Vec3( 1, -1, 0),
        Vec3( 1,  1, 0)
    };
    quad->set_vbo<Vec3>("vposition", quad_vposition);
    std::vector<unsigned int> quad_triangle_indices = {
        0, 2, 1, 1, 2, 3
    };
    quad->set_triangles(quad_triangle_indices);
    std::vector<Vec2> quad_vtexcoord = {
        Vec2(0, 0),
        Vec2(0, 1),
        Vec2(1, 0),
        Vec2(1, 1)
    };
    quad->set_vtexcoord(quad_vtexcoord);
}

void loadTexture(std::unique_ptr<RGBA8Texture> &texture, const char *filename) {
    // Used snippet from https://raw.githubusercontent.com/lvandeve/lodepng/master/examples/example_decode.cpp
    std::vector<unsigned char> image; //the raw pixels
    unsigned width, height;
    //decode
    unsigned error = lodepng::decode(image, width, height, filename);
    //if there's an error, display it
    if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
    //the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...

    // unfortunately they are upside down...lets fix that
    unsigned char* row = new unsigned char[4*width];
    for(int i = 0; i < int(height)/2; ++i) {
        memcpy(row, &image[4*i*width], 4*width*sizeof(unsigned char));
        memcpy(&image[4*i*width], &image[image.size() - 4*(i+1)*width], 4*width*sizeof(unsigned char));
        memcpy(&image[image.size() - 4*(i+1)*width], row, 4*width*sizeof(unsigned char));
    }
    delete row;

    texture = std::unique_ptr<RGBA8Texture>(new RGBA8Texture());
    texture->upload_raw(width, height, &image[0]);
}

//Credit for this method to Jakob Riedle (Stack Overflow).
//takes values and computes the position of a point on the line between the lines p0-p1 and p1-p2.
float getPt( float n1 , float n2 , float perc ) {
    float ret_val;
    float diff = n2 - n1;
    ret_val = n1 + ( diff * perc );
    return ret_val;
}

//Calaculates the bezier cureve given three points and the time variable.
Vec2 calculateBezier(float t, Vec2 p0, Vec2 p1, Vec2 p2) {
    Vec2 xy;        //return value

    float xcord;
    float ycord;
    float xa;
    float ya;
    float xb;
    float yb;

    xa = getPt( p0(0) , p1(0) , t );
    ya = getPt( p0(1) , p1(1) , t );
    xb = getPt( p1(0) , p2(0) , t );
    yb = getPt( p1(1) , p2(1) , t );

    xcord = getPt( xa , xb , t );
    ycord = getPt( ya , yb , t );
    xy = Vec2(xcord, ycord);
    return xy;
}

//Draws individual elements into the scene.
void drawElement(Transform matrix, std::unique_ptr<RGBA8Texture> &texture) {
    quadShader->bind();
    quadShader->set_uniform("M", matrix.matrix());
    // Make texture unit 0 active
    glActiveTexture(GL_TEXTURE0);
    // Bind the texture to the active unit for drawing
    texture->bind();
    // Set the shader's texture uniform to the index of the texture unit we have
    // bound the texture to
    quadShader->set_uniform("tex", 0);
    quad->set_attributes(*quadShader);
    quad->draw();
    texture->unbind();
}

//Creates a window that displays the drawn elements. Calls the drawElement() method.
void drawScene(float timeCount)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float t2 = timeCount * SpeedFactor;
    float t = timeCount * SpeedFactor;
    t = fmodf(t, 1.0);

    //BEZIER CURVE PATH
    Vec2 xy = calculateBezier(t, controlPoints[0], controlPoints[1], controlPoints[2]);
    float xcord = xy(0);
    float ycord = xy(1);

    /* TRANSFORM MATRICES */
    //BACKGROUND
    Transform background = Transform::Identity();
    background *= Eigen::AngleAxisf(-(t2/14 + M_PI), Eigen::Vector3f::UnitZ());     //rotation
    background *= Eigen::AlignedScaling3f(1.5, 1.5, 1);                            //size

    //MOON
    Transform mun = Transform::Identity();
    mun *= Eigen::Translation3f(0.8, 1, 0);                                 //movement
    mun *= Eigen::AlignedScaling3f(1.4, 1.4, 1);                            //rotation
    mun *= Eigen::AngleAxisf(-(t2/4 + M_PI), Eigen::Vector3f::UnitZ());     //size

    //PLANET EXPRESS DELIVERY SHIP
    Transform planet_express = Transform::Identity();
    planet_express *= Eigen::Translation3f(xcord, ycord, 0);                            //movement
    planet_express  *= Eigen::AngleAxisf((1.6*t + M_PI) + 2, Eigen::Vector3f::UnitZ()); //rotation
    planet_express  *= Eigen::AlignedScaling3f(0.1f + t/2, 0.05f + t/4, 1);             //size

    //BENDER
    Transform bonder = Transform::Identity();
    float xcord2 = 0.2*std::cos(15*t);
    float ycord2 = 0.2*std::sin(15*t);
    bonder *= Eigen::Translation3f(xy(0) + xcord2, xy(1) + ycord2, 0);          //movement
    bonder *= Eigen::AngleAxisf(-10*t2 + M_PI, Eigen::Vector3f::UnitZ());       //rotation
    bonder *= Eigen::AlignedScaling3f(0.005 + t/8, 0.025 + t/6, 1);             //size

    //DRAW ELEMENTS OF SCENE
    drawElement(background, stars);
    drawElement(mun, moon);
    drawElement(planet_express, ship);
    drawElement(bonder, bender);

    quadShader->unbind();
    glDisable(GL_BLEND);
}
