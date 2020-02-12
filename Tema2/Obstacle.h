#pragma once
#include <include/glm.h>
#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>
#include "Component.h"

class Obstacle
{
public:
	Obstacle(float zCoord, float yCoord, float speed);
	~Obstacle();
	std::vector<std::tuple<std::vector<std::string>, glm::vec3, glm::mat4>> update(float deltaTimeSeconds, float angular_speed);
	std::vector<std::pair<glm::vec3, glm::vec3>> getBoundingBoxes();
	float getAngle();

private:
	std::vector<std::tuple<std::vector<std::string>, glm::vec3, glm::mat4>> components;
	float angular_speed;
	float oy_position;
	float angle;
	bool start;
	float angularStep;

	float rotationStep = 0;
	float rotation_speed = 4.5f;
	float zCoord;
	float yCoord;
	float speed;
};