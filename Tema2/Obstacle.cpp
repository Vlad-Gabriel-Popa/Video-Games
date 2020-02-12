#include "Obstacle.h"
#include <vector>
#include <iostream>
#include<string>

using namespace std;

Obstacle::Obstacle(float zCoord, float yCoord, float speed) {
	
	this->zCoord = zCoord;
	this->yCoord = yCoord;
	this->angular_speed = speed;
	
	{
		std::vector<std::string> data(2);
		data[0] = "star";
		data[1] = "MainShader";

		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f / 26.f, 1.f / 26.f, 1.f / 26.f));
		components.push_back(std::make_tuple(data, glm::vec3(1, 0.15f, 0.15f), modelMatrix));
	}
	/*
	{
		std::vector<std::string> data(2);
		data[0] = "cube";
		data[1] = "MainShader";

		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::scale(modelMatrix, glm::vec3(2.f, 2.f, 0.8f));
		components.push_back(std::make_tuple(data, glm::vec3(0, 0, 0), modelMatrix));
	}
	*/
	angularStep = -M_PI/4.f * 40;


}

Obstacle::~Obstacle() {

}

float Obstacle::getAngle() {
	return angularStep / 40;
}


std::vector<std::tuple<std::vector<std::string>, glm::vec3, glm::mat4>> Obstacle::update(float deltaTimeSeconds, float angular_speed) {

	std::vector<std::tuple<std::vector<std::string>, glm::vec3, glm::mat4>> out;



	glm::mat4 transform = glm::mat4(1);
	transform = glm::rotate(transform, angularStep / 40, glm::vec3(0, 0, 1));
	transform = glm::translate(transform, glm::vec3(0, yCoord, zCoord));
	transform = glm::rotate(transform, -rotationStep, glm::vec3(0, 1, 0));
	

	angularStep += angular_speed * deltaTimeSeconds;
	rotationStep += rotation_speed * deltaTimeSeconds;

	for (auto& component : components) {
		vector<string> data;
		glm::vec3 color;
		glm::mat4 modelMatrix;
		std::tie(data, color, modelMatrix) = component;

		out.push_back(std::make_tuple(data, color, transform * modelMatrix));
	}

	return out;
}

std::vector<std::pair<glm::vec3, glm::vec3>> Obstacle::getBoundingBoxes() {
	std::vector<std::pair<glm::vec3, glm::vec3>> out;
	
	glm::mat4 transform = glm::mat4(1);
	transform = glm::rotate(transform, angularStep / 40, glm::vec3(0, 0, 1));
	transform = glm::translate(transform, glm::vec3(0, yCoord, zCoord));

	glm::vec3 centre = transform * glm::vec4(0, 0, 0, 1);
	float x = 2.f;
	float y = 2.f;
	float z = 0.8f;

	out.push_back(std::make_pair(centre, glm::vec3(x,y,z)));
	
	return out;
	
}
