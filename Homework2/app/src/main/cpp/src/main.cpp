#include "main.h"

void surfaceCreated(AAssetManager* aAssetManager) {
    //┌ 1. Implement depth testing ────────────────────────────┐
    glClearDepthf(1.0f);
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    //└──────────────────────────────────────────┘

    //┌ 4. Implement alpha blending────────────────────────────┐
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);
    //└──────────────────────────────────────────┘

    Scene::setup(aAssetManager);
}

void surfaceChanged(int width, int height) {
    glViewport(0, 0, width, height);
    Scene::screen(width, height);
}

void drawFrame(float deltaTime) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Scene::update(deltaTime);
}

