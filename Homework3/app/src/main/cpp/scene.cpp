#include "scene.h"

#include "obj_teapot.h"
#include "tex_flower.h"

#define NUM 3



Shader* Scene::vertexShader = nullptr;
Shader* Scene::fragmentShader = nullptr;
Program* Scene::program = nullptr;
Camera* Scene::camera = nullptr;
Light* Scene::light = nullptr;
Object** Scene::teapot = nullptr;
Material* Scene::flower = nullptr;
int Scene::_width = 0;
int Scene::_height = 0;

void Scene::setup(AAssetManager* aAssetManager) {

    // set asset manager
    Asset::setManager(aAssetManager);

    // create shaders
    vertexShader = new Shader(GL_VERTEX_SHADER, "vertex.glsl");
    fragmentShader = new Shader(GL_FRAGMENT_SHADER, "fragment.glsl");

    // create program
    program = new Program(vertexShader, fragmentShader);

    // create camera
    camera = new Camera(program);
    camera->eye = vec3(0.0f, 00.0f, 60.0f);

    // create light
    light = new Light(program);
    light->position = vec3(0.0f, 0.0f, 100.0f);

    // create floral texture
    flower = new Material(program, texFlowerData, texFlowerSize);

    // create teapot object
    teapot = new Object*[NUM];

    for (int i = 0; i < NUM; i++)
    {
        teapot[i] = new Object(program, flower, objTeapotVertices, objTeapotIndices,
                               objTeapotVerticesSize, objTeapotIndicesSize);
        teapot[i]->origin = vec3(0.0f, 0.0f+ (i*20.0f), 0.0f - (i*20.0f));
        teapot[i]->worldMatrix = translate(teapot[i]->origin) * rotate(radians(60.0f), vec3(1.0, 1.0, 0.0));
    }

    int i = 0;
    LOG_PRINT_DEBUG("Hello World %d %d\n", i, i+1);
}

void Scene::mouseUpEvents(float x, float y, bool doubleTouch)
{
}

void Scene::screen(int width, int height) {

    _width = width;
    _height = height;

    // set camera aspect ratio
    camera->aspect = (float) width / height;
}

void Scene::update(float deltaTime) {

    // use program
    program->use();

    // setup camera and light
    camera->setup();
    light->setup();

    // draw teapot
    for (int i = 0; i < NUM; i++)
    {
        teapot[i]->origin = vec3(teapot[i]->worldMatrix[3][0],
                teapot[i]->worldMatrix[3][1], teapot[i]->worldMatrix[3][2]);
        teapot[i]->draw();
    }
}


//┌───────────────────────────────────────────────────────────┐
int Scene::pickIndex = -1;
vec3 Scene::oldVec = vec3(0.0f, 0.0f, 0.0f);
//matrices are filled in column order
vec4 Scene::inverseTransform(float x, float y, bool isPoint)
{
    y = _height-y;
    float m11 = (cos(radians(camera->fovy/2))/sin(radians(camera->fovy/2)))/camera->aspect;
    float m22 = cos(radians(camera->fovy/2))/sin(radians(camera->fovy/2));
    vec4 camspace_ray = vec4 (((2.0f * x / _width) - 1.0f) / m11 , ((2.0f * y / _height) - 1.0f) / m22, -1.0f, 0.0f);
    vec4 camspace_start = vec4 (camera->zNear * ((2.0f * x / _width) - 1.0f) / m11 , camera->zNear * ((2.0f * y / _height) - 1.0f) / m22, -camera->zNear, 1.0f);
    mat4 camera2world = transpose(mat4(camera->viewMatrix[0][0],camera->viewMatrix[0][1],camera->viewMatrix[0][2],-camera->viewMatrix[3][0],
                            camera->viewMatrix[1][0],camera->viewMatrix[1][1],camera->viewMatrix[1][2],-camera->viewMatrix[3][1],
                            camera->viewMatrix[2][0],camera->viewMatrix[2][1],camera->viewMatrix[2][2],-camera->viewMatrix[3][2],
                            camera->viewMatrix[0][3],camera->viewMatrix[1][3],camera->viewMatrix[2][3],camera->viewMatrix[3][3]));

    if (isPoint){
        return camera2world * camspace_start;
    }else{
        return camera2world * camspace_ray;
    }
}

vec3 Scene::calculateArcballvec(float x, float y)
{
    y = _height - y;
    float ballx = (2*x/_width)-1;
    float bally = (2*y/_height)-1;
    float twosum = pow(ballx,2.0f) + pow(bally,2.0f);
    if (twosum>1.0f)
        return normalize(vec3(ballx, bally, 0.0f));
    float ballz = sqrt(1- pow(ballx,2.0f) - pow(bally,2.0f));
    return vec3(ballx,bally,ballz);
}

void Scene::mouseDownEvents(float x, float y, bool doubleTouch)
{
    vec4 ray_start = inverseTransform(x,y,true);//world space ray start and direction
    vec4 ray = inverseTransform(x,y,false);
    vec3 v = calculateArcballvec(x,y);
    float min_t = 10000;
    for(int i=0; i<NUM; i++){
        vec4 obj_ray_start = ray_start;// technically still in world space
        vec4 obj_ray = ray;// but we don't need to go to the object space since our bounding spheres are identical
        for(int t = 0;t<5000; t++){
            obj_ray_start += 0.1f * obj_ray;
            vec3 diff = vec3(obj_ray_start) - teapot[i]->origin;
            float dist = sqrt(pow(diff[0],2.0f)+ pow(diff[1],2.0f)+ pow(diff[2],2.0f));//assumes object center is at origin
            if(dist < 10.0f){//distance set to 10 for now
                if(t<min_t){
                    min_t = t;
                    pickIndex = i;
                    if(!doubleTouch)
                        oldVec = vec3 (ray_start);
                    else
                        oldVec = v;
                }
                break;
            }
        }
    }
}

void Scene::mouseMoveEvents(float x, float y, bool doubleTouch)
{
    if (Scene::pickIndex==-1) return;
    if(!doubleTouch){
        vec4 new_ray = inverseTransform(x,y,true);//ray start point in world space(on Near plane)
        vec3 temp_ = vec3(teapot[pickIndex]->origin) + vec3(camera->viewMatrix[3]);
        float ratio = sqrt(pow(temp_[0],2.0f)+ pow(temp_[1],2.0f)+ pow(temp_[2],2.0f));//ratio of camera ray to world ray
        vec3 diff = new_ray - vec4(oldVec,0);
        oldVec = vec3 (new_ray);
        teapot[pickIndex]->worldMatrix[3][0] += ratio * diff[0];
        teapot[pickIndex]->worldMatrix[3][1] += ratio * diff[1];
        teapot[pickIndex]->worldMatrix[3][2] += ratio * diff[2];
    }else{
        vec3 new_v = calculateArcballvec(x,y);
        vec3 axis = cross(oldVec, new_v);
        float cosine = (oldVec[0]* new_v[0])+(oldVec[1]* new_v[1])+(oldVec[2]* new_v[2]) ;
        float angle = acos(abs(cosine));
        axis = vec3(inverse(teapot[pickIndex]->worldMatrix) * inverse(camera->viewMatrix) * vec4(axis,0.0f));
        teapot[pickIndex]->worldMatrix = teapot[pickIndex]->worldMatrix * rotate(angle, axis);
        oldVec = new_v;
    }
}
//└───────────────────────────────────────────────────────────┘









