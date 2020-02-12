#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>
#include <random>
#include "Object.h"
#include "Pillars.h"

class PillarManager : public Object
{
public:
	PillarManager();
	~PillarManager();
	bool started;
	std::vector<std::pair<std::string, glm::mat3>> update(glm::ivec2 resolution, float deltaTimeSeconds);
	std::vector<glm::vec3> getBoundingBoxes();
	int get_score(float bird_position);
	void stop();
	void gangster();
protected:
	bool game_over;
	bool gangster_mode;
	std::vector<Pillars> pillars;
	float pillar_speed;
	float distance_pillars;
	std::random_device rd;
	std::mt19937 gen;
};
