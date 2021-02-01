#ifndef OPENGLES_SCENE_H
#define OPENGLES_SCENE_H

#include "global.h"
#include "program.h"
#include "camera.h"
#include "light.h"
#include "object.h"
#include "material.h"




class Scene {

private:
    static Shader* vertexShader;
    static Shader* fragmentShader;
    static Program* program;
    static Camera* camera;
    static Light* light;
    static Object** teapot;
    static Material* flower;

    static int _width;
    static int _height;
    static int pickIndex;
    static vec3 oldVec;

    static vec4 inverseTransform(float x, float y, bool dotFlag);
    static vec3 calculateArcballvec(float x, float y);

public:
    static void setup(AAssetManager* aAssetManager);
    static void screen(int width, int height);
    static void update(float deltaTime);

    static void mouseDownEvents(float x, float y, bool doubleTouch);
    static void mouseMoveEvents(float x, float y, bool doubleTouch);
    static void mouseUpEvents(float x, float y, bool doubleTouch);
};

#endif // OPENGLES_SCENE_H
