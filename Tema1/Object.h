#pragma once

class Object
{
public:
	Object() {}
	virtual ~Object() {}
	virtual std::vector<std::pair<std::string, glm::mat3>> update(glm::ivec2 resolution, float deltaTimeSeconds) = 0;
	virtual std::vector<glm::vec3> getBoundingBoxes() = 0;
};
