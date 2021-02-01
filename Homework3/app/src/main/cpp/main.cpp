#include "main.h"

void mouseDownEvents(float x, float y, bool doubleTouch)
{
    Scene::mouseDownEvents(x, y, doubleTouch);
}

void mouseMoveEvents(float x, float y, bool doubleTouch)
{
    Scene::mouseMoveEvents(x, y, doubleTouch);
}

void mouseUpEvents(float x, float y, bool doubleTouch)
{
    Scene::mouseUpEvents(x, y, doubleTouch);
}

void surfaceCreated(AAssetManager* aAssetManager) {

    // set clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // enable depth test
    glEnable(GL_DEPTH_TEST);

    // setup scene
    Scene::setup(aAssetManager);
}

void surfaceChanged(int width, int height) {

    // set viewport
    glViewport(0, 0, width, height);

    // set scene screen
    Scene::screen(width, height);
}

void drawFrame(float deltaTime) {

    // clear color buffer and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // update scene
    Scene::update(deltaTime);
}
