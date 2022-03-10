#pragma once

#include "Shader.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <string>

using namespace std;

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
	glm::vec3 tangent;
	glm::vec3 bitangent;
};

struct Texture
{
	unsigned int id;
	string type;
	string path;
};

class Mesh
{
public:
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	Mesh(const vector<Vertex>&, const vector<unsigned int>&, const vector<Texture>&);
	void Draw(Shader&);

private:
	unsigned int VAO, VBO, EBO;

	void setupMesh();
};

Mesh::Mesh(const vector<Vertex>& vertices, const vector<unsigned int>& indices, 
	const vector<Texture>& textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	setupMesh();
}

void Mesh::setupMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	//vertex attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
	glEnableVertexAttribArray(3);

	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));
	glEnableVertexAttribArray(4);
	
	glBindVertexArray(0);
}

void Mesh::Draw(Shader& shader)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;

	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);

		string textureNr;
		string type_name = textures[i].type;
		if (type_name == "texture_diffuse")
			textureNr = to_string(diffuseNr++);
		else if (type_name == "texture_specular")
			textureNr = to_string(specularNr++);
		else if (type_name == "texture_normal")
			textureNr = to_string(normalNr++);
		else if (type_name == "texture_height")
			textureNr = to_string(heightNr++);

		shader.setFloat(("material."+type_name+textureNr).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	//draw mesh
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	//set everything back to defaults once configured
	glActiveTexture(GL_TEXTURE0);
}