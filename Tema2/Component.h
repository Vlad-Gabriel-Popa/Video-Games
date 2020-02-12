#pragma once
#include<vector>
#include <string>
#include <include/glm.h>

class Component
{
public:
	Component() {}
	virtual ~Component() {}
	virtual std::vector<std::tuple<std::vector<std::string>, glm::vec3, glm::mat4>> update(float deltaTimeSeconds) = 0;
	virtual std::vector<std::pair<glm::vec3, glm::vec3>> getBoundingBoxes() = 0;
};
