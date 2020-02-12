#pragma once

#include <string>
#include <vector>
#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Colision
{

	bool has_colided(std::vector<glm::vec3> source, std::vector<glm::vec3> target);

}
