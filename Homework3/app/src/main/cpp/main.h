#ifndef OPENGLES_MAIN_H
#define OPENGLES_MAIN_H

#include "global.h"
#include "scene.h"

void mouseDownEvents(float x, float y, bool doubleTouch);
void mouseMoveEvents(float x, float y, bool doubleTouch);
void mouseUpEvents(float x, float y, bool doubleTouch);

void surfaceCreated(AAssetManager* aAssetManager);
void surfaceChanged(int width, int height);
void drawFrame(float deltaTime);

extern "C"
JNIEXPORT void JNICALL
Java_kr_ac_korea_media_opengles_MainActivity_mouseDownEvents(JNIEnv *env, jobject instance,
                                                             jfloat x, jfloat y, jboolean doubleTouch) {
    // call native function
    mouseDownEvents(x, y, doubleTouch);
}

extern "C"
JNIEXPORT void JNICALL
Java_kr_ac_korea_media_opengles_MainActivity_mouseMoveEvents(JNIEnv *env, jobject instance,
                                                             jfloat x, jfloat y, jboolean doubleTouch) {
    // call native function
    mouseMoveEvents(x, y, doubleTouch);
}

extern "C"
JNIEXPORT void JNICALL
Java_kr_ac_korea_media_opengles_MainActivity_mouseUpEvents(JNIEnv *env, jobject instance,
                                                         jfloat x, jfloat y, jboolean doubleTouch) {
    // call native function
    mouseUpEvents(x, y, doubleTouch);
}

extern "C"
JNIEXPORT void JNICALL
Java_kr_ac_korea_media_opengles_MainActivity_surfaceCreated(JNIEnv *env, jobject instance,
                                                            jobject assetManager) {
    // call native function
    surfaceCreated(AAssetManager_fromJava(env, assetManager));
}

extern "C"
JNIEXPORT void JNICALL
Java_kr_ac_korea_media_opengles_MainActivity_surfaceChanged(JNIEnv *env, jobject instance,
                                                            jint width, jint height) {
    // call native function
    surfaceChanged(width, height);
}

extern "C"
JNIEXPORT void JNICALL
Java_kr_ac_korea_media_opengles_MainActivity_drawFrame(JNIEnv *env, jobject instance,
                                                       jfloat deltaTime) {
    // call native function
    drawFrame(deltaTime);
}

#endif // OPENGLES_MAIN_H
