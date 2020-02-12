#include "CreateObjects.h"
#include <iostream>
Mesh* Objects::generate_terrain(float size, int mapWidth, int mapHeight) {
	std::vector<VertexFormat> vertices;
	for (int line = 0; line < mapHeight; line++) {
		for (int column = 0; column < mapWidth; column++) {
			float ln = (float)line;
			float cl = (float)column;
			vertices.push_back(VertexFormat(glm::vec3(cl / (mapWidth - 1) - 0.5f, 0, ln / (mapHeight - 1) - 0.5f),
								glm::vec3(0), glm::vec3(0), glm::vec2(cl/(mapWidth-1), ln / (mapHeight - 1))));
		}
	}

	std::vector<unsigned short> indices;
	for (unsigned short idx = 0; idx < mapWidth * (mapHeight-1); idx++){
		if ( (idx+1) % mapWidth != 0) {
			indices.push_back(idx);
			indices.push_back(idx + mapWidth);
			indices.push_back(idx + mapWidth + 1);

			indices.push_back(idx);
			indices.push_back(idx + mapWidth + 1);
			indices.push_back(idx + 1);
		}
	}

	Mesh* terrain = new Mesh("terrain");
	terrain->InitFromData(vertices, indices);
	return terrain;
}