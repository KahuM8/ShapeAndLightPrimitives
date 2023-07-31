
#pragma once

// glm
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// project
#include "opengl.hpp"
#include "cgra/cgra_mesh.hpp"
using namespace cgra;


class Face {
	
public:
	float ambient = 0.2;
	float diffuse = 0.5;
	float specular = 0.8;
	float cook = 0.1;
	float oren_nayar = 0.1;
	float roughness = 0.1;
	float material = 0.1;
	float texture_strength = 0;
	void draw(const glm::mat4& view, const glm::mat4 proj);
	mesh_builder meshb;
	int resolution;
	glm::vec3 localUp;
	glm::vec3 axisA;
	glm::vec3 axisB;
	
	Face(mesh_builder mesh, int resolution, glm::vec3 localUp);
	void createMesh();
	

	GLuint shader = 0;
	cgra::gl_mesh mesh;
	glm::vec3 color{0.7};
	glm::mat4 modelTransform{1.0};
	GLuint texture;

};