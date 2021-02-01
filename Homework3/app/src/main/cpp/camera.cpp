#include "camera.h"

Camera::Camera(Program* program)
        : eye(vec3(0.0f)),
          at(vec3(0.0f)),
          up(vec3(0.0f, 1.0f, 0.0f)),
          fovy(60.0f),
          aspect(1.0f),
          zNear(1.0f),
          zFar(150.0f) {

    // create camera
    create(program);

    // setup camera
    setup();
}

void Camera::create(Program* program) {
    LOG_PRINT_DEBUG("Create camera");

    // set attribute
    this->program = program;

    // check uniform locations
    if (glGetUniformLocation(program->get(), "viewMat") < 0) {
        LOG_PRINT_WARN("Fail to get uniform location: %s", "viewMat");
    }
    if (glGetUniformLocation(program->get(), "projMat") < 0) {
        LOG_PRINT_WARN("Fail to get uniform location: %s", "projMat");
    }
}

void Camera::setup() {
//    LOG_PRINT_DEBUG("Set camera");

    // create matrix
    //viewMatrix = lookAt(eye, at, up);
    viewMatrix = mat4(1.000000, 0.000000, 0.000000, 0.000000,
    0.000000, 1.000000, 0.000000, 0.000000,
    0.000000, 0.000000, 1.000000, 0.000000,
    0.000000, 0.000000, -60.000000, 1.000000);
    projMatrix = perspective(radians(fovy), aspect, zNear, zFar);

    // get uniform locations
    GLint viewMatLoc = glGetUniformLocation(program->get(), "viewMat");
    GLint projMatLoc = glGetUniformLocation(program->get(), "projMat");

    // set uniform data
    if (viewMatLoc >= 0) glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, value_ptr(viewMatrix));
    if (projMatLoc >= 0) glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, value_ptr(projMatrix));
}
