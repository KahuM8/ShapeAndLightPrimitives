#include "Torus.hpp"
#include <stb.h>
#include <glm/detail/type_mat.hpp>




using namespace std;
using namespace cgra;
using namespace glm;



void Torus::createMesh() {
	mesh_builder mb;
	mesh_vertex mv;

	vector<vec3> vertices;
	vector<vec3> normals;
	vector<vec2> uv;


	float du = 2 * M_PI /numMajorSegments;
	float dv = 2 * M_PI /numMinorSegments;

	for (int i = 0; i < numMajorSegments; i++) {
		float u = i * du;
		for (int j = 0; j <= numMinorSegments; j++) {
			float v = (j % numMinorSegments) * dv;
			for (int k = 0; k < 2; k++) {
			float uu = u + k * du;
			float x = (majorRadius + minorRadius * cos(v)) * cos(uu);
			float y = (majorRadius + minorRadius * cos(v)) * sin(uu);
			float z = minorRadius * sin(v);

			float nx = cos(uu) * cos(v);
			float ny = sin(uu) * cos(v);
			float nz = sin(v);

			float s = u / (2 * M_PI);
			float t = v / (2 * M_PI);

			vertices.push_back(vec3(x, y, z));
			normals.push_back(vec3(nx, ny, nz));
			uv.push_back(vec2(s, t));
			}
			v += dv;
		}
	}
	for (int i = 2; i < vertices.size(); i++) {
		mb.push_index(i - 2);
		mb.push_index(i - 1);
		mb.push_index(i);
	}

	for (int i = 0; i < vertices.size(); i++) {
		mv.pos = vertices[i];
		mv.norm = normals[i];
		mv.uv = uv[i];
		mb.push_vertex(mv);
	}

	mesh = mb.build();
 }


void Torus::draw(const glm::mat4& view, const glm::mat4 proj)
{
	glm::mat4 modelview = view * modelTransform;

	glUseProgram(shader); // load shader and variables
	glUniformMatrix4fv(glGetUniformLocation(shader, "uProjectionMatrix"), 1, false, value_ptr(proj));
	glUniformMatrix4fv(glGetUniformLocation(shader, "uModelViewMatrix"), 1, false, value_ptr(modelview));
	glUniform3fv(glGetUniformLocation(shader, "uColor"), 1, value_ptr(color));
	glUniform1f(glGetUniformLocation(shader, "As"), ambient);
	glUniform1f(glGetUniformLocation(shader, "Ds"), diffuse);
	glUniform1f(glGetUniformLocation(shader, "Ss"), specular);
	glUniform1f(glGetUniformLocation(shader, "Cs"), cook);
	glUniform1f(glGetUniformLocation(shader, "Ts"), texture_strength);
	glUniform1f(glGetUniformLocation(shader, "roughness"), roughness);
	glUniform1f(glGetUniformLocation(shader, "material"), material);
	glUniform1f(glGetUniformLocation(shader, "ONs"), oren_nayar);
	glUniform1i(1, 0);
	mesh.draw();
}