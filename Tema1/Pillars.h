#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>
#include <random>
#include "Object.h"

class Pillars : public Object
{
public:
	Pillars(std::mt19937 gen, float ox_position = 110.0f, float previous_hole_position = 50.0f, float width = 25.0f, float pillar_speed = 20.0f, bool gangster_mode = false, bool move = false, float pillar_width = 7.0f, float brick_width = 10.0f, float brick_lenght = 8.0f);
	~Pillars();
	std::vector<std::pair<std::string, glm::mat3>> update(glm::ivec2 resolution, float deltaTimeSeconds);
	std::vector<glm::vec3> getBoundingBoxes();
	float ox_position;
	float hole_position;
	bool counted;
	void stop();
	void gangster();
protected:
	std::string up_color, down_color, colors[5];
	float wait_time;
	float move_distance;
	float current_move;
	bool moving_up;
	bool gangster_mode;
	bool move;
	float gangster_angle;
	bool game_over;
	float hole_width;
	float pillar_speed;
	float pillar_width;
	float brick_width;
	float brick_length;
	glm::mat3 transformation1, transformation2;
	std::vector<glm::vec3> bounding_boxes;
	std::vector<std::pair<std::string, glm::mat3>> up_pillar, down_pillar;

};
