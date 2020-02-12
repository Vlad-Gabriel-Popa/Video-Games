#include "Pillars.h"
#include "PillarManager.h"

#include <vector>
#include<string>
#include <iostream>
#include <random>
#include <time.h>

using namespace std;

PillarManager::~PillarManager()
{
}

PillarManager::PillarManager() {
	std::mt19937 gen(rd());
	this->gen = gen;
	this->distance_pillars = 40;
	this->pillar_speed = 30;
	game_over = false;
	gangster_mode = false;
}

std::vector<std::pair<std::string, glm::mat3>>  PillarManager::update(glm::ivec2 resolution, float deltaTimeSeconds) {
	std::vector<std::pair<std::string, glm::mat3>> output, pillar_output;

	// Pillar speed and distance between pillars will increase at every frame
	pillar_speed += deltaTimeSeconds;
	distance_pillars += deltaTimeSeconds / 4;
	if (!started)
		return output;

	//Create pillar if there is none
	if (pillars.empty()) {
		bool move = false;
		if (rand() % 3 == 0) {
			move = true;
		}
		pillars.push_back(Pillars(gen, 110, 50.0f, 35.0f, pillar_speed, gangster_mode, move));
	}

	//Create new pillar if distance is greater then distance_pillars
	if (130 - pillars.back().ox_position >= distance_pillars) {
		float spawn_ox = 220 - pillars.back().ox_position;
		bool move = false;
		if (rand() % 3 == 0) {
			move = true;
		}
		pillars.push_back(Pillars(gen, spawn_ox, pillars.back().hole_position, 35.0f, pillar_speed, gangster_mode, move));
	}

	//Delete pillar that exited from the screen
	if (pillars.front().ox_position <= -50) {
		pillars.erase(pillars.begin());
	}

	// Calculate position for every pillar
	for (Pillars& pillar : pillars) {
		pillar_output = pillar.update(resolution, deltaTimeSeconds);
		output.insert(output.end(), pillar_output.begin(), pillar_output.end());
	}
	return output;
}

std::vector<glm::vec3> PillarManager::getBoundingBoxes() {
	std::vector<glm::vec3> output, pillar_output;

	for (auto& pillar : pillars) {
		pillar_output = pillar.getBoundingBoxes();
		output.insert(output.end(), pillar_output.begin(), pillar_output.end());
	}
	return output;
}

void PillarManager::stop() {
	game_over = true;
	for (auto& pillar : pillars) {
		pillar.stop();
	}
}
void PillarManager::gangster() {
	gangster_mode = !gangster_mode;
	for (auto& pillar : pillars) {
		pillar.gangster();
	}

	if (gangster_mode) {
		distance_pillars += 10;
	}
	else {
		distance_pillars -= 10;
	}
}

int PillarManager::get_score(float position) {
	int score = 0;
	for (auto& pillar : pillars) {
		if (!pillar.counted) {
			if (position >= pillar.ox_position) {
				score += 1;
				pillar.counted = true;
			}
		}
	}
	return score;
}