#pragma once

#include <vector>
#include "opengl.hpp"
#include "cgra/cgra_mesh.hpp"
#include <glm/gtc/type_ptr.hpp>


// glm
#include <stb.h>




using namespace cgra;

class Torus {
public:
    float ambient = 0.2;
    float diffuse = 0.5;
    float specular = 0.8;
    float cook = 0.1;
    float texture_strength = 0;
    float oren_nayar = 0.1;
    float roughness = 0.1;
    float material = 0.1;
    GLuint shader;
    cgra::gl_mesh mesh;
    float majorRadius =1;
    float minorRadius = 0.5;
    int numMajorSegments = 10;
    int numMinorSegments = 10;
    glm::mat4 modelTransform {1.0};
    glm::vec3 color {0.7};

    void createMesh();
    void draw(const glm::mat4 &view, const glm::mat4 proj);
    
    

};
