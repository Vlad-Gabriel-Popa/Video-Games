#include "Manager.h"
#include <vector>
#include <iostream>
#include<string>

using namespace std;

Manager::Manager(float yMin, float yMax, float zMin, float zMax) {
	
	this->yMin = yMin;
	this->yMax = yMax;
	this->zMin = zMin;
	this->zMax = zMax;
	
	angluar_speed = 5;

	time_till_next_fuel = 2;
	time_till_next_cloud = 0;
	time_till_next_obstacle = 0.2f;

}

Manager::~Manager() {

}

std::vector<std::tuple<std::vector<std::string>, glm::vec3, glm::mat4>> Manager::update(float deltaTimeSeconds) {

	time_till_next_cloud -= deltaTimeSeconds;
	time_till_next_fuel -= deltaTimeSeconds;
	time_till_next_obstacle -= deltaTimeSeconds;

	if (game_over) {
		angluar_speed -= deltaTimeSeconds;
		if (angluar_speed < 0) {
			angluar_speed = 0;
		}
	}
	else {
		angluar_speed += 0.1f * deltaTimeSeconds;
		if (angluar_speed > 12) {
			angluar_speed = 12;
		}
	}

	if (!game_over) {
		if (time_till_next_cloud < 0) {
			float zCoord = -40.f - rand() % 50;
			float yCoord = 235.f + rand() % 65;

			clouds.push_back(new Cloud(zCoord, yCoord, angluar_speed));


			time_till_next_cloud = 1.4f + static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		}


		if (clouds.size() && clouds.front()->getAngle() > M_PI / 2) {
			clouds.erase(clouds.begin());
		}

		if (time_till_next_obstacle < 0) {

			float yCoord = 190.f + rand() % 55;
			float oz = 0;
			if (third_person) {
				oz = (rand() % 3 - 1)*5.f;
			}
			obstacles.push_back(new Obstacle(oz, yCoord, angluar_speed));

			if (!first_person && !third_person) {
				time_till_next_obstacle = (0.4f + static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) / ((angluar_speed - 4) / 1.5f);
			}
			if (first_person || third_person) {
				time_till_next_obstacle = (0.4f + static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) / ((angluar_speed - 4));
			}

		}


		if (obstacles.size() && obstacles.front()->getAngle() > M_PI / 10.f) {
			obstacles.erase(obstacles.begin());
		}


		if (time_till_next_fuel < 0) {
			float radius = 195.f + rand() % 45;

			int number_of_tanks = rand() % 10;
			float oz = -5.f;
			if (third_person) {
				oz = (rand() % 3 - 1) * 5.f;
			}
			if (rand() % 2) {
				for (int i = 0; i < number_of_tanks; i++) {

					float xCoord = 6 * i;
					float yCoord = radius + 4.5f * sin(M_PI * (xCoord / 48.f));
					fuel.push_back(new Fuel(oz, xCoord, yCoord, angluar_speed));
				}
			}
			else {
				for (int i = 0; i < number_of_tanks; i++) {

					float xCoord = 6 * i;
					float yCoord = radius + 4.5f * cos(M_PI * (xCoord / 48.f));
					
					fuel.push_back(new Fuel(oz, xCoord, yCoord, angluar_speed));
				}
			}
			time_till_next_fuel = 5.f + static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 6.f;
		}

		while (fuel.size() && fuel.front()->getAngle() > M_PI / 4.f) {
			fuel.erase(fuel.begin());
		}

	}
	std::vector<std::tuple<std::vector<std::string>, glm::vec3, glm::mat4>> out, component_out;
	for (auto& cloud : clouds) {
		component_out = cloud->update(deltaTimeSeconds);
		out.insert(out.end(), component_out.begin(), component_out.end());
	}

	for (auto& fuel_comp : fuel) {
		component_out = fuel_comp->update(deltaTimeSeconds, angluar_speed);
		out.insert(out.end(), component_out.begin(), component_out.end());
	}

	for (auto& obstacle : obstacles) {
		component_out = obstacle->update(deltaTimeSeconds, angluar_speed);
		out.insert(out.end(), component_out.begin(), component_out.end());
	}
	
	return out;
}

bool has_collided(std::pair<glm::vec3, glm::vec3> bb1, std::pair<glm::vec3, glm::vec3> bb2) {
	glm::vec3 centre1 = bb1.first;
	glm::vec3 size1 = bb1.second;
	glm::vec3 centre2 = bb2.first;
	glm::vec3 size2 = bb2.second;


	if (centre1.x <= centre2.x && centre1.x + size1.x < centre2.x - size2.x || centre1.x >= centre2.x && centre1.x - size1.x > centre2.x + size2.x) {
	
		return false;

	}
	if (centre1.y <= centre2.y && centre1.y + size1.y < centre2.y - size2.y || centre1.y >= centre2.y && centre1.y - size1.y > centre2.y + size2.y)
		return false;
	if (centre1.z <= centre2.z && centre1.z + size1.z < centre2.z - size2.z || centre1.z >= centre2.z && centre1.z - size1.z > centre2.z + size2.z)
		return false;
	
	return true;
}

int Manager::detect_collision(std::vector<std::pair<glm::vec3, glm::vec3>> bounding_boxes, bool colliding) {
	std::vector<std::pair<glm::vec3, glm::vec3>> bbs,bb;
	
	if (!colliding) {
		for (auto& obstacle : obstacles) {
			bb = obstacle->getBoundingBoxes();
			bbs.insert(bbs.end(), bb.begin(), bb.end());
		}


		for (auto& bounding_box : bounding_boxes) {
			glm::vec3 centre = bounding_box.first;
			glm::vec3 size = bounding_box.second;

			int idx = 0;
			for (auto& bb : bbs) {
				if (has_collided(bounding_box, bb)) {
					collision_obstacle = bb.first;
					obstacles.erase(obstacles.begin() + idx);
					return -1;
				}
				idx++;
			}
		}

		bbs.clear();
	}
	for (auto& tank : fuel) {
		bb = tank->getBoundingBoxes();
		bbs.insert(bbs.end(), bb.begin(), bb.end());
	}


	for (auto& bounding_box : bounding_boxes) {
		glm::vec3 centre = bounding_box.first;
		glm::vec3 size = bounding_box.second;

		int idx = 0;
		for (auto& bb : bbs) {
			if (has_collided(bounding_box, bb)) {
				fuel.erase(fuel.begin() + idx);
				return 1;
			}
			idx++;
		}


	}

	return 0;
}

glm::vec3 Manager::get_collided() {
	return collision_obstacle;
}
std::vector<std::pair<glm::vec3, glm::vec3>> Manager::getBoundingBoxes() {
	return std::vector<std::pair<glm::vec3, glm::vec3>>();
}

void Manager::set_game_over() {
	game_over = true;
}