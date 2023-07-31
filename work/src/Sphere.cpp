#include "Sphere.hpp"
#include <glm/detail/type_mat.hpp>


void Sphere::draw(const glm::mat4& view, const glm::mat4 proj)
{
	glm::mat4 modelview = view * modelTransform;

	glUseProgram(shader); // load shader and variables
    glUniformMatrix4fv(glGetUniformLocation(shader, "uProjectionMatrix"), 1, false, value_ptr(proj));
	glUniformMatrix4fv(glGetUniformLocation(shader, "uModelViewMatrix"), 1, false, value_ptr(modelview));
	glUniform3fv(glGetUniformLocation(shader, "uColor"), 1, value_ptr(color));
	mesh.draw(); 
    glUniform1f(glGetUniformLocation(shader, "As"), ambient);
    glUniform1f(glGetUniformLocation(shader, "Ds"), diffuse);
    glUniform1f(glGetUniformLocation(shader, "Ss"), specular);
    glUniform1f(glGetUniformLocation(shader, "Cs"), cook);
    glUniform1f(glGetUniformLocation(shader, "ONs"), oren_nayar);
    glUniform1f(glGetUniformLocation(shader, "Ts"), texture_strength);
    glUniform1f(glGetUniformLocation(shader, "roughness"), roughness);
    glUniform1f(glGetUniformLocation(shader, "material"), material);

    glUniform1i(1, 0);
}

cgra::gl_mesh Sphere::createMesh()
{
    cgra::mesh_builder mb;
    float pi = 3.14159265359;
    float latStep = pi / lat;
    float longStep = 2 * pi / lon;
    
    float x, y, z;
    float u, v;
    float uStep = 1.0f / lon;
    float vStep = 1.0f / lat;
    float uCoord = 0.0f;
    float vCoord = 0.0f;

    for (int i = 0; i < lat + 1; i++) {
        for (int j = 0; j < lon +1; j++) {
            x = rad * sin(latStep * i) * cos(longStep * j);
            y = rad * sin(latStep * i) * sin(longStep * j);
            z = rad * cos(latStep * i);

            u = uCoord;
            v = vCoord;

            mb.push_vertex({ {x, y, z}, {x, y, z}, {u, v} }); // Add vertex position, normal, and texture coordinate

            uCoord += uStep;
        }

        uCoord = 0.0f;
        vCoord += vStep;
    }

    // Add indices for the sphere faces
    for (int i = 0; i < lat +1; i++) {
        for (int j = 0; j < lon +1 ; j++) {
            int p1 = i * lon + j;
            int p2 = i * lon + j + 1;
            int p3 = (i + 1) * lon + j + 1;
            int p4 = (i + 1) * lon + j;

            // Triangle 1
            mb.push_index(p1);
            mb.push_index(p2);
            mb.push_index(p3);

            // Triangle 2
            mb.push_index(p1);
            mb.push_index(p3);
            mb.push_index(p4);
        }
    }

    cgra::gl_mesh g = mb.build();
    return g;
}












  














