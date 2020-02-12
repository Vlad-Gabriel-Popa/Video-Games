#pragma once
#include <include/glm.h>
#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>
#include "Component.h"

class Cloud:Component
{
public:
	Cloud(float zCoord, float yCoord, float speed);
	~Cloud();
	std::vector<std::tuple<std::vector<std::string>, glm::vec3, glm::mat4>> update(float deltaTimeSeconds);
	std::vector<std::pair<glm::vec3, glm::vec3>> getBoundingBoxes();
	float getAngle();

private:
	std::vector<std::tuple<std::vector<std::string>, glm::vec3, glm::mat4>> components, rotors;
	std::vector<glm::vec3> cube_positions;
	std::vector<glm::vec3> rand_axes;
	std::vector<float> rand_speed;
	float angluar_speed;

	float rotationStep = 0;
	float rotation_speed = 4.5f;
	float oy_position;
	float angle;
	bool start;
	float angularStep;

	float zCoord;
	float yCoord;
	float speed;
};