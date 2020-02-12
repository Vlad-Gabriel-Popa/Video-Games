#include "CreateShape.h"
#include <time.h>
#include <Core/Engine.h>
#include <iostream>

Mesh* Object3D::create_cube(std::string name) {
	std::vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(0, 1, 1), glm::normalize(glm::vec3(-1, 0,  1))),
		VertexFormat(glm::vec3(1, -1,  1), glm::vec3(1, 0, 1), glm::normalize(glm::vec3(1, 0,  1))),
		VertexFormat(glm::vec3(-1,  1,  1), glm::vec3(1, 0, 0), glm::normalize(glm::vec3(0,  1,  0))),
		VertexFormat(glm::vec3(1,  1,  1), glm::vec3(0, 1, 0), glm::normalize(glm::vec3(0,  1,  0))),
		VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(1, 1, 1), glm::normalize(glm::vec3(-1, 0, -1))),
		VertexFormat(glm::vec3(1, -1, -1), glm::vec3(0, 1, 1), glm::normalize(glm::vec3(1, 0, -1))),
		VertexFormat(glm::vec3(-1,  1, -1), glm::vec3(1, 1, 0), glm::normalize(glm::vec3(0,  1, 0))),
		VertexFormat(glm::vec3(1,  1, -1), glm::vec3(0, 0, 1), glm::normalize(glm::vec3(0,  1, 0))),
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 2,		1, 3, 2,
		2, 3, 7,		2, 7, 6,
		1, 7, 3,		1, 5, 7,
		6, 7, 4,		7, 5, 4,
		0, 4, 1,		1, 4, 5,
		2, 6, 4,		0, 2, 4,
	};
	Mesh* cube = new Mesh(name);
	cube->InitFromData(vertices, indices);
	return cube;

}



Mesh* Object3D::cube_up(std::string name) {
	std::vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(0, 1, 1), glm::vec3(0, 1,  0)),
		VertexFormat(glm::vec3(1, -1,  1), glm::vec3(1, 0, 1), glm::vec3(0, 1,  0)),
		VertexFormat(glm::vec3(-1,  1,  1), glm::vec3(1, 0, 0), glm::vec3(0,  1,  0)),
		VertexFormat(glm::vec3(1,  1,  1), glm::vec3(0, 1, 0), glm::vec3(0,  1,  0)),
		VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(1, 1, 1), glm::vec3(0, 1, 0)),
		VertexFormat(glm::vec3(1, -1, -1), glm::vec3(0, 1, 1), glm::vec3(0, 1, 0)),
		VertexFormat(glm::vec3(-1,  1, -1), glm::vec3(1, 1, 0), glm::vec3(0,  1, 0)),
		VertexFormat(glm::vec3(1,  1, -1), glm::vec3(0, 0, 1), glm::vec3(0,  1, 0)),
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 2,		1, 3, 2,
		2, 3, 7,		2, 7, 6,
		1, 7, 3,		1, 5, 7,
		6, 7, 4,		7, 5, 4,
		0, 4, 1,		1, 4, 5,
		2, 6, 4,		0, 2, 4,
	};
	Mesh* cube = new Mesh(name);
	cube->InitFromData(vertices, indices);
	return cube;

}

Mesh* Object3D::pyramid_base(std::string name) {
	std::vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(-4, -0.5,  0.5), glm::vec3(0, 1, 1), glm::normalize(glm::vec3(-1, 0,  1))),
		VertexFormat(glm::vec3(2, -1,  1), glm::vec3(1, 0, 1), glm::normalize(glm::vec3(2, 0,  1))),
		VertexFormat(glm::vec3(-4,  0.5,  0.5), glm::vec3(1, 0, 0), glm::normalize(glm::vec3(0,  1,  0))),
		VertexFormat(glm::vec3(2,  1,  1), glm::vec3(0, 1, 0), glm::normalize(glm::vec3(2,  1,  1))),
		VertexFormat(glm::vec3(-4, -0.5, -0.5), glm::vec3(1, 1, 1), glm::normalize(glm::vec3(-4, 0, -0.5))),
		VertexFormat(glm::vec3(2, -1, -1), glm::vec3(0, 1, 1), glm::normalize(glm::vec3(2, 0, -1))),
		VertexFormat(glm::vec3(-4,  0.5, -0.5), glm::vec3(1, 1, 0), glm::normalize(glm::vec3(-4,  0.5, -0.5))),
		VertexFormat(glm::vec3(2,  1, -1), glm::vec3(0, 0, 1), glm::normalize(glm::vec3(2,  1, -1))),
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 2,		1, 3, 2,
		2, 3, 7,		2, 7, 6,
		1, 7, 3,		1, 5, 7,
		6, 7, 4,		7, 5, 4,
		0, 4, 1,		1, 4, 5,
		2, 6, 4,		0, 2, 4,
	};
	Mesh* cube = new Mesh(name);
	cube->InitFromData(vertices, indices);
	return cube;


}


Mesh* Object3D::star(std::string name) {
		
	std::vector<VertexFormat> vertices=
	{
		VertexFormat(glm::vec3(0, 0, 35), glm::vec3(0, 1, 1), glm::normalize(glm::vec3(0, 0.2f,  1))),
		VertexFormat(glm::vec3(0, 0, -35), glm::vec3(0, 1, 1), glm::normalize(glm::vec3(0, 0.2f,  -1))),
		VertexFormat(glm::vec3(0, 84,  0), glm::vec3(1, 0, 1), glm::normalize(glm::vec3(0, 1,  0))),
		VertexFormat(glm::vec3(18, 25,  0), glm::vec3(1, 0, 0), glm::normalize(glm::vec3(1,  1,  0))),
		VertexFormat(glm::vec3(81, 23,  0), glm::vec3(0, 1, 0), glm::normalize(glm::vec3(0.8f,  0.5f,  0))),
		VertexFormat(glm::vec3(32, -11, 0), glm::vec3(1, 1, 1), glm::normalize(glm::vec3(1, 0.4f, 0))),
		VertexFormat(glm::vec3(50, -66, 0), glm::vec3(0, 1, 1), glm::normalize(glm::vec3(1, 0.1f, 0))),
		VertexFormat(glm::vec3(0, -36, 0), glm::vec3(0, 1, 1), glm::normalize(glm::vec3(0, -0.2f, 0))),
		VertexFormat(glm::vec3(-18, 25,  0), glm::vec3(1, 0, 0), glm::normalize(glm::vec3(-1,  1,  0))),
		VertexFormat(glm::vec3(-81, 23,  0), glm::vec3(0, 1, 0), glm::normalize(glm::vec3(-0.8f,  0.5f,  0))),
		VertexFormat(glm::vec3(-32, -11, 0), glm::vec3(1, 1, 1), glm::normalize(glm::vec3(-1, 0.4f, 0))),
		VertexFormat(glm::vec3(-50, -66, 0), glm::vec3(0, 1, 1), glm::normalize(glm::vec3(-1, 0.1f, 0))),
    };

std::vector<unsigned short> indices =
	{
		0, 3, 2,		0, 4, 3,
		0, 5, 4,		0, 6, 5,
		0, 7, 6,		0, 2, 8,
		0, 8, 9,		0, 9, 10,
		0, 10, 11,		0, 11, 7,

		1, 2, 3,		1, 3, 4,
		1, 4, 5,		1, 5, 6,
		1, 6, 7,		1, 8, 2,
		1, 9, 8,		1, 10, 9,
		1, 11, 10,		1, 7, 11,

	};

	Mesh* star = new Mesh(name);
	star->InitFromData(vertices, indices);
	return star;
}

Mesh* Object3D::gas_tank(std::string name) {

	std::vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(35, 134,  30), glm::vec3(0, 1, 1), glm::normalize(glm::vec3(0, 1,  0.2))),
		VertexFormat(glm::vec3(79, 177,  30), glm::vec3(1, 0, 1), glm::normalize(glm::vec3(0, 1,  0.2))),
		VertexFormat(glm::vec3(141, 128,  30), glm::vec3(1, 0, 0), glm::normalize(glm::vec3(0,  0.8,  0.5))),
		VertexFormat(glm::vec3(141, 78,  30), glm::vec3(0, 1, 0), glm::normalize(glm::vec3(0,  0.8,  0.5))),
		VertexFormat(glm::vec3(87, 32, 30), glm::vec3(1, 1, 1), glm::normalize(glm::vec3(0, 0.5f, 0.5))),
		VertexFormat(glm::vec3(87, -38, 30), glm::vec3(0, 1, 1), glm::normalize(glm::vec3(0, 0.8, 0.5))),
		VertexFormat(glm::vec3(131, -78, 30), glm::vec3(1, 1, 0), glm::normalize(glm::vec3(0,  0.8, 0.5))),
		VertexFormat(glm::vec3(131, -142, 30), glm::vec3(0, 0, 1), glm::normalize(glm::vec3(0,  0.8, 0.5))),
		VertexFormat(glm::vec3(31, -138, 30), glm::vec3(0, 0, 1), glm::normalize(glm::vec3(0,  0.2, 0.5))),
		VertexFormat(glm::vec3(26, -108, 30), glm::vec3(0, 0, 1), glm::normalize(glm::vec3(0,  0.2, 0.5))),
		
		VertexFormat(glm::vec3(-35, 134,  30), glm::vec3(0, 1, 1), glm::normalize(glm::vec3(0, 1,  0.5))),
		VertexFormat(glm::vec3(-79, 177,  30), glm::vec3(1, 0, 1), glm::normalize(glm::vec3(0, 1,  0.5))),
		VertexFormat(glm::vec3(-141, 128,  30), glm::vec3(1, 0, 0), glm::normalize(glm::vec3(0,  0.8,  0.5))),
		VertexFormat(glm::vec3(-141, 78,  30), glm::vec3(0, 1, 0), glm::normalize(glm::vec3(0,  0.8,  0.5))),
		VertexFormat(glm::vec3(-87, 32, 30), glm::vec3(1, 1, 1), glm::normalize(glm::vec3(0, 0.5f, 0.5))),
		VertexFormat(glm::vec3(-87, -38, 30), glm::vec3(0, 1, 1), glm::normalize(glm::vec3(0, 0.8, 0.5))),
		VertexFormat(glm::vec3(-131, -78, 30), glm::vec3(1, 1, 0), glm::normalize(glm::vec3(0,  0.8, 0.5))),
		VertexFormat(glm::vec3(-131, -142, 30), glm::vec3(0, 0, 1), glm::normalize(glm::vec3(0,  0.8, 0.5))),
		VertexFormat(glm::vec3(-31, -138, 30), glm::vec3(0, 0, 1), glm::normalize(glm::vec3(0,  0.2f, 0.5))),
		VertexFormat(glm::vec3(-26, -108, 30), glm::vec3(0, 0, 1), glm::normalize(glm::vec3(0,  0.2f, 0.5))),

	    VertexFormat(glm::vec3(35, 134,  -30), glm::vec3(0, 1, 1), glm::normalize(glm::vec3(0, 1,  -0.2))),
		VertexFormat(glm::vec3(79, 177,  -30), glm::vec3(1, 0, 1), glm::normalize(glm::vec3(0, 1,  -0.2))),
		VertexFormat(glm::vec3(141, 128,  -30), glm::vec3(1, 0, 0), glm::normalize(glm::vec3(0,  0.8,  -0.5))),
		VertexFormat(glm::vec3(141, 78,  -30), glm::vec3(0, 1, 0), glm::normalize(glm::vec3(0,  0.8,  -0.5))),
		VertexFormat(glm::vec3(87, 32, -30), glm::vec3(1, 1, 1), glm::normalize(glm::vec3(0, 0.5, -0.5))),
		VertexFormat(glm::vec3(87, -38, -30), glm::vec3(0, 1, 1), glm::normalize(glm::vec3(0, 0.8, -0.5))),
		VertexFormat(glm::vec3(131, -78, -30), glm::vec3(1, 1, 0), glm::normalize(glm::vec3(0,  0.8, -0.5))),
		VertexFormat(glm::vec3(131, -142, -30), glm::vec3(0, 0, 1), glm::normalize(glm::vec3(0,  0.8, -0.5))),
		VertexFormat(glm::vec3(31, -138, -30), glm::vec3(0, 0, 1), glm::normalize(glm::vec3(0,  0.2f, -0.5))),
		VertexFormat(glm::vec3(26, -108, -30), glm::vec3(0, 0, 1), glm::normalize(glm::vec3(0,  0.2f, -0.5))),

		VertexFormat(glm::vec3(-35, 134,  -30), glm::vec3(0, 1, 1), glm::normalize(glm::vec3(0, 1,  -0.2))),
		VertexFormat(glm::vec3(-79, 177,  -30), glm::vec3(1, 0, 1), glm::normalize(glm::vec3(0, 1,  -0.2))),
		VertexFormat(glm::vec3(-141, 128,  -30), glm::vec3(1, 0, 0), glm::normalize(glm::vec3(0,  0.8,  -0.5))),
		VertexFormat(glm::vec3(-141, 78,  -30), glm::vec3(0, 1, 0), glm::normalize(glm::vec3(0,  0.8, -0.5))),
		VertexFormat(glm::vec3(-87, 32, -30), glm::vec3(1, 1, 1), glm::normalize(glm::vec3(0, 0.5, -0.5))),
		VertexFormat(glm::vec3(-87, -38, -30), glm::vec3(0, 1, 1), glm::normalize(glm::vec3(0, 0.8, -0.5))),
		VertexFormat(glm::vec3(-131, -78, -30), glm::vec3(1, 1, 0), glm::normalize(glm::vec3(0,  0.8, -0.5))),
		VertexFormat(glm::vec3(-131, -142, -30), glm::vec3(0, 0, 1), glm::normalize(glm::vec3(0,  0.8, -0.5))),
		VertexFormat(glm::vec3(-31, -138, -30), glm::vec3(0, 0, 1), glm::normalize(glm::vec3(0,  0.2f, -0.5))),
		VertexFormat(glm::vec3(-26, -108, -30), glm::vec3(0, 0, 1), glm::normalize(glm::vec3(0,  0.2f, -0.5))),

	};


	std::vector<unsigned short> indices =
	{
		0, 2, 1,		2, 4, 3,
		0, 4, 2,		0, 9, 4,
		4, 9, 5,		5, 9, 7,
		5, 7, 6,		9, 8, 7,
		0, 10, 9,		10, 19, 9,
		11, 12, 10,		13, 14, 12,
		12, 14, 10,     14, 19, 10,
		15, 19, 14,     17, 19, 15,
		16, 17, 15,     17, 18, 19,

		20, 22, 21,		22, 24, 23,
		20, 24, 22,		20, 29, 24,
		24, 29, 25,		25, 29, 27,
		25, 27, 26,		29, 28, 27,
		20, 30, 29,		30, 39, 29,
		31, 32, 30,		33, 34, 32,
		32, 34, 30,     34, 39, 30,
		35, 39, 34,     37, 39, 35,
		36, 37, 35,     37, 38, 39,

		0, 1, 20,       1, 21, 20,
		1, 2, 21,       2, 22, 21,
		2, 3, 22,       3, 23, 22,
		3, 4, 23,       4, 24, 23,
		4, 5, 24,       5, 25, 24,
		5, 6, 25,       6, 26, 25,
		6, 7, 26,       7, 27, 26,
		7, 8, 27,       8, 28, 27,
		8, 9, 28,       9, 29, 28,

		10, 0, 30,      0, 20, 30,
		39, 29, 19,     29, 9, 19,

		11, 10, 31,       10, 30, 31,
		12, 11, 32,       11, 31, 32,
		13, 12, 33,       12, 32, 33,
		14, 13, 34,       13, 33, 34,
		15, 14, 35,       14, 34, 35,
		16, 15, 36,       15, 35, 36,
		17, 16, 37,       16, 36, 37,
		18, 17, 38,       17, 37, 38,
		19, 18, 39,       18, 38, 39,
		

	};


	Mesh* fuel = new Mesh(name);
	fuel->InitFromData(vertices, indices);
	return fuel;


}

Mesh* Object3D::create_cylinder() {
	std::vector<VertexFormat> vertices;

	std::vector<unsigned short> indices;
	srand(time(NULL));

	//Data is composed of 3 values : offset, angle, and direction
	glm::vec3 data(0, 0, -1);

	vertices.push_back(VertexFormat(glm::vec3(0,0,1), data));
	vertices.push_back(VertexFormat(glm::vec3(0,0,-1), data));

	int i = 0;
	int nr = 30;
	for (double alpha = 0; alpha < 2 * M_PI; alpha += 0.15f)
	{

		double x = cos(alpha);
		double y = sin(alpha);
		glm::vec3 norm = glm::normalize(glm::vec3(cos(alpha), sin(alpha), 0));
		vertices.push_back(VertexFormat(glm::vec3(x, y, 1), data, norm));
		
		float unit = 2.f / (float)(nr + 2);
		float pos = 1.f;

		for (int p = 0; p < nr; p++) {
			pos -= unit;

		
			float x1 = 1.03f;
			float x2 = 0.97f;

			float r = 1.f + (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5f)* (x1 - x2);
		//	float offset = -(1.f/(x1-x2)) * M_PI * r + (x1/(x1-x2)) * M_PI;
			
			float offset = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 3;
			float direction = rand() % 2;


			vertices.push_back(VertexFormat(glm::vec3(x, y, pos), glm::vec3(offset, alpha, direction), norm));
			if (i != 0) {

				int index = (nr + 2) * i + 3 + p;
				indices.push_back(index);
				indices.push_back(index - (nr+2));
				indices.push_back(index - 1);

				indices.push_back(index - 1);
				indices.push_back(index - (nr + 2));
				indices.push_back(index - (nr + 2) - 1);
			}
		}
		vertices.push_back(VertexFormat(glm::vec3(x, y, -1), data, norm));
		int index = (nr + 2) * (i+1) + 1;
		indices.push_back(index);
		indices.push_back(index - (nr + 2));
		indices.push_back(index - 1);

		indices.push_back(index - 1);
		indices.push_back(index - (nr + 2));
		indices.push_back(index - (nr + 2) - 1);
		
		if (i != 0) {

			indices.push_back(index);
			indices.push_back(index - (nr + 2));
			indices.push_back(1);

			index = (nr + 2) * i + 2;
			indices.push_back(index);
			indices.push_back(index - (nr + 2));
			indices.push_back(0);
		}

		i++;

	}

	for (int p = 0; p < nr+1; p++) {
		

		int index = (nr + 2) * (i-1) + 3 + p;
		indices.push_back(p+2);
		indices.push_back(index);
		indices.push_back(p+1);

		indices.push_back(p+1);
		indices.push_back(index);
		indices.push_back(index - 1);
		
	}

	int index = (nr + 2) * i + 1;
	indices.push_back(nr+3);
	indices.push_back(index);
	indices.push_back(1);

	index = (nr + 2) * (i-1) + 2;
	indices.push_back(2);
	indices.push_back(index);
	indices.push_back(0);


	Mesh* cylinder = new Mesh("cylinder");
	cylinder->InitFromData(vertices, indices);
	return cylinder;
}