#include "Cloud.h"
#include <vector>
#include <iostream>
#include<string>
#include <time.h>
using namespace std;

Cloud::Cloud(float zCoord, float yCoord, float speed) {
	
	this->zCoord = zCoord;
	this->yCoord = yCoord;
	this->angluar_speed = speed;
	
	int rnd = rand() % 5;
	int number_of_squares = 4 + rnd;

	float max_x = 10.f + +rnd / 1.5f + (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 5; 
	float max_y = 3.5f + (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 4 + rnd / 1.5f;
	float max_z = 8.f + (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 4;


	for (int i = 0; i < number_of_squares; i++) {
		std::vector<std::string> data(2);
		data[0] = "cube";
		data[1] = "MainShader";

		float rand_scale =2*( 4.f +  (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) + rnd/6.f);
		
		float pos_x = max_x * ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 2 - 1);
		float pos_y = max_y * ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 2 - 1);
		float pos_z = max_z * ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 2 - 1);

		cube_positions.push_back(glm::vec3(pos_x, pos_y, pos_z));

		float rand_angle1 = rand() % 90;
		float rand_angle2 = rand() % 90;
		

		rand_speed.push_back(static_cast <float> (rand()) / static_cast <float> (RAND_MAX));

		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::rotate(modelMatrix, RADIANS(rand_angle2), glm::vec3(1,0,0));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(rand_angle1), glm::vec3(0,0,1));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(rand_scale, rand_scale, rand_scale));
		components.push_back(std::make_tuple(data, glm::vec3(0.8f, 0.8f, 0.8f), modelMatrix));

		float rand_ox = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float rand_oy = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float rand_oz = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		rand_axes.push_back(glm::vec3(rand_ox, rand_oy, rand_oz));


	}

	angularStep = - M_PI/4 * 40;

}

Cloud::~Cloud() {

}

std::vector<std::tuple<std::vector<std::string>, glm::vec3, glm::mat4>> Cloud::update(float deltaTimeSeconds) {

	std::vector<std::tuple<std::vector<std::string>, glm::vec3, glm::mat4>> out;



	glm::mat4 transform = glm::mat4(1);
	transform = glm::rotate(transform, angularStep / 40, glm::vec3(0, 0, 1));
	transform = glm::translate(transform, glm::vec3(0, yCoord, zCoord));

	angularStep += angluar_speed * deltaTimeSeconds;
	rotationStep += rotation_speed * deltaTimeSeconds;

	int i = 0;
	for (auto& component : components) {
		vector<string> data;
		glm::vec3 color;
		glm::mat4 modelMatrix;
		std::tie(data, color, modelMatrix) = component;

		glm::mat4 transform_aux = glm::translate(transform, glm::vec3(cube_positions[i].x, cube_positions[i].y, cube_positions[i].z));
		transform_aux = glm::rotate(transform_aux, -rotationStep /4.f * rand_speed[i] , glm::vec3(rand_axes[i].x, rand_axes[i].y, rand_axes[i].z));
		out.push_back(std::make_tuple(data, color, transform_aux * modelMatrix));

		i++;
	}

	return out;
}

float Cloud::getAngle() {
	return angularStep / 40;
}

std::vector<std::pair<glm::vec3, glm::vec3>> Cloud::getBoundingBoxes() {
	return std::vector<std::pair<glm::vec3, glm::vec3>>();
}
