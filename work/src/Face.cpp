#include "Face.hpp"
#include "cgra/cgra_mesh.hpp"

// glm
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// project
#include "opengl.hpp"



using namespace glm;



Face::Face(cgra::mesh_builder meshb, int resolution, glm::vec3 localUp) {
	this->meshb = meshb;
	this->resolution = resolution;
	this->localUp = localUp;
	this->axisA = vec3(localUp.y, localUp.z, localUp.x);
	this->axisB = cross(localUp, axisA);
}

void Face::createMesh() {
    int vertexCount = resolution * resolution;
    std::vector<vec3> vertices(vertexCount);
    std::vector<vec3> normals(vertexCount); // Store normals
    std::vector<vec2> uvs(vertexCount); // Store UVs
    std::vector<unsigned int> triangles(6 * (resolution - 1) * (resolution - 1));

    int triIndex = 0;

    for (int y = 0; y < resolution; y++) {
        for (int x = 0; x < resolution; x++) {
            int i = x + y * resolution;
            vec2 percent = vec2(static_cast<float>(x), static_cast<float>(y));
            percent.x /= static_cast<float>(resolution - 1);
            percent.y /= static_cast<float>(resolution - 1);

            vec3 pointOnUnitCube = localUp + (percent.x - 0.5f) * 2 * axisA + (percent.y - 0.5f) * 2 * axisB;
            vec3 pointOnUnitSphere = normalize(pointOnUnitCube);
            vertices[i] = pointOnUnitSphere;

            // Compute normals as the same as the vertices since it's a sphere
            normals[i] = vertices[i];

            // Compute UVs based on percent
            uvs[i] = percent;

            if (x != resolution - 1 && y != resolution - 1) {
                triangles[triIndex] = i;
                triangles[triIndex + 1] = i + resolution + 1;
                triangles[triIndex + 2] = i + resolution;

                triangles[triIndex + 3] = i;
                triangles[triIndex + 4] = i + 1;
                triangles[triIndex + 5] = i + resolution + 1;
                triIndex += 6;
            }
        }
    }
    meshb.clear();

    // Add the new vertices, normals, and UVs to the mesh_builder
    for (int i = 0; i < vertexCount; i++) {
        meshb.push_vertex(cgra::mesh_vertex{ vertices[i], normals[i], uvs[i] });
    }

    for (int i = 0; i < triangles.size(); i += 3) {
        meshb.push_indices({ triangles[i], triangles[i + 1], triangles[i + 2] });
    }
    mesh = meshb.build();
}



void Face::draw(const glm::mat4& view, const glm::mat4 proj)
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
    glUniform1f(glGetUniformLocation(shader, "ONs"), oren_nayar);

    glUniform1f(glGetUniformLocation(shader, "Ts"), texture_strength);
    glUniform1f(glGetUniformLocation(shader, "roughness"), roughness);
    glUniform1f(glGetUniformLocation(shader, "material"), material);
    glUniform1i(1, 0);
    mesh.draw();

}

