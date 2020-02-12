#include "Object2D.h"

#include <Core/Engine.h>

Mesh* Object2D::CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };
	
	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}


Mesh* Object2D::CreateCircle(std::string name, glm::vec3 center, float radius, glm::vec3 color)
{
	std::vector<VertexFormat> vertices;

	std::vector<unsigned short> indices;

	vertices.push_back(VertexFormat(center, color));
	int i = 1;
	for (double alpha = 0; alpha < 2 * M_PI; alpha += 0.01f)
	{

		double x = radius*cos(alpha);
		double y = radius*sin(alpha);
		vertices.push_back(VertexFormat(glm::vec3(x, y, 0), color));
		if (i != 1)
		{
			indices.push_back(i);
			indices.push_back(i - 1);
			indices.push_back(0);
		}
		i++;
	}
	indices.push_back(1);
	indices.push_back(i - 1);
	indices.push_back(0);
	
	Mesh* circle = new Mesh(name);
	circle->InitFromData(vertices, indices);
	return circle;

}