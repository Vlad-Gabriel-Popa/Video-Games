#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object3D
{
	Mesh* create_cube(std::string name);
	Mesh* cube_up(std::string name);
	Mesh* create_cylinder();
	Mesh* pyramid_base(std::string name);
	Mesh* gas_tank(std::string name);
	Mesh* star(std::string name);

}

