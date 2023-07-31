#include "Face.hpp"
#include "cgra/cgra_mesh.hpp"

class edgeMaker {
private:


public:
		int resolution = 3;
		std::vector<Face> faces; // Store the six faces of the cube
		edgeMaker(int resolution) {
			this->resolution = resolution;
			init();

	}

		void init() {
			glm::vec3 directions[] = {
				glm::vec3(0, 1, 0),  // Top face
				glm::vec3(0, -1, 0), // Bottom face
				glm::vec3(-1, 0, 0), // Left face
				glm::vec3(1, 0, 0),  // Right face
				glm::vec3(0, 0, 1),  // Front face
				glm::vec3(0, 0, -1)  // Back face
			};

			mesh_builder meshb[6];
			int resolution = 4;

			for (int i = 0; i < 6; ++i) {
				Face face(meshb[i], resolution, directions[i]);
				faces.push_back(face);
			}
		}

	void createMesh() {
		for (int i = 0; i < faces.size(); i++) {
			faces[i].createMesh();
			faces[i].ambient = ambient;
			faces[i].diffuse = diffuse;
			faces[i].specular = specular;
			faces[i].cook = cook;
			faces[i].texture_strength = texture_strength;
		}
	}

	void draw(const glm::mat4& view, const glm::mat4 proj) {
		for (int i = 0; i < faces.size(); i++) {
			faces[i].draw(view, proj);
		}
	}

	void updateResolutions() {
		for (int i = 0; i < faces.size(); i++) {
			faces[i].resolution = resolution;
		}
		createMesh();
	
	}

	float ambient = 0.2;
	float diffuse = 0.5;
	float specular = 0.8;
	float cook = 0.1;
	float oren_nayar = 0.1;
	float roughness = 0.1;
	float material = 0.1;
	float texture_strength = 0;

	GLuint shader = 0;
	cgra::gl_mesh mesh;
	glm::vec3 color{ 0.7 };
	glm::mat4 modelTransform{ 1.0 };
	GLuint texture;


};
