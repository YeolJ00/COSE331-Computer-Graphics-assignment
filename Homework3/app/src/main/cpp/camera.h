#ifndef OPENGLES_CAMERA_H
#define OPENGLES_CAMERA_H

#include "global.h"
#include "program.h"

class Camera {

public:
    vec3 eye;
    vec3 at;
    vec3 up;
    float fovy;
    float aspect;
    float zNear;
    float zFar;

    mat4 viewMatrix;
    mat4 projMatrix;

    Camera(Program *program);

    virtual void setup();

private:
    Program *program;

    virtual void create(Program* program);
};

#endif // OPENGLES_CAMERA_H
