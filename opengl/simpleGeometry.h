#pragma once

#include <vector>
#include "public.h"
#include "Shader.h"

using namespace std;

class simpleGeometry
{	
	vector<float> values;
	unsigned texture_ID;
	unsigned VAO, VBO;
	unsigned num_values_in_vertex;
public:
	simpleGeometry(vector<float> const& vec, string const& path, mode_simple_geometry mode);
	void setup(mode_simple_geometry _mode);
	void Draw(Shader& shader);
};

simpleGeometry::simpleGeometry(vector<float> const& vec, string const& path, mode_simple_geometry mode)
{
	values = vec;
	texture_ID = loadTexture(path.c_str());
	setup(mode);
}

void simpleGeometry::setup(mode_simple_geometry _mode)
{	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	switch (_mode)
	{
	case HAVE_BOTH:
		num_values_in_vertex = 8;
		glBufferData(GL_ARRAY_BUFFER, values.size() * sizeof(float), &values[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
		break;

	case HAVE_TEXCOORD:
		num_values_in_vertex = 5;
		glBufferData(GL_ARRAY_BUFFER, values.size() * sizeof(float), &values[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		break;

	case HAVE_NORMAL:
		num_values_in_vertex = 6;
		glBufferData(GL_ARRAY_BUFFER, values.size() * sizeof(float), &values[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		break;

	case ONLY_POS:
		num_values_in_vertex = 3;
		glBufferData(GL_ARRAY_BUFFER, values.size() * sizeof(float), &values[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
		glEnableVertexAttribArray(0);
		break;

	}
	glBindVertexArray(VAO);
}

void simpleGeometry::Draw(Shader& shader)
{
	shader.use();
	glBindTexture(GL_TEXTURE_2D, texture_ID);
	
	// draw triangles
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, values.size() / num_values_in_vertex);
	
	// set everything back to defaults onces finished
	glBindVertexArray(0);
}