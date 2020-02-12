#pragma once
#include <include/glm.h>
#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>
#include "Component.h"
#include "Fuel.h"
#include "Obstacle.h"
#include "Cloud.h"

class Manager
{
public:
	Manager(float yMin, float yMax, float zMin, float zMax);
	~Manager();
	std::vector<std::tuple<std::vector<std::string>, glm::vec3, glm::mat4>> update(float deltaTimeSeconds);
	std::vector<std::pair<glm::vec3, glm::vec3>> getBoundingBoxes();
	int detect_collision(std::vector<std::pair<glm::vec3, glm::vec3>> bounding_boxes, bool colliding);
	glm::vec3 get_collided();
	void set_game_over();
	bool first_person = false, third_person = false;
private:
	std::vector<std::tuple<std::vector<std::string>, glm::vec3, glm::mat4>> components;
	float angluar_speed;
	float angularStep;
	std::vector<Fuel*> fuel;
	std::vector<Obstacle*> obstacles;
	std::vector<Cloud*> clouds;
	glm::vec3 collision_obstacle;

	float time_till_next_fuel;
	float time_till_next_obstacle;
	float time_till_next_cloud;
	float yMin, yMax, zMin, zMax;
	float speed;
	bool game_over;
};