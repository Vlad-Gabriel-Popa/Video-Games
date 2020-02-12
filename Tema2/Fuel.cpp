#include "Fuel.h"
#include <vector>
#include <iostream>
#include<string>

using namespace std;

Fuel::Fuel(float zCoord, float xCoord, float yCoord, float speed) {

	this->zCoord = zCoord;
	this->xCoord = xCoord;
	this->yCoord = yCoord;
	this->angular_speed = speed;

	glm::vec3 color(0.03f, 0.18f, 0.39f);

	{
		std::vector<std::string> data(2);
		data[0] = "gas_tank";
		data[1] = "MainShader";

		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.f, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0f / 100.0f, 1.0f / 100.0f, 1.0f / 60.0f));
		components.push_back(std::make_tuple(data, color, modelMatrix));
	}

	{
		std::vector<std::string> data(2);
		data[0] = "cube";
		data[1] = "MainShader";

		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.1f, 0.f, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.4f, 1.4f, 0.25f));
		components.push_back(std::make_tuple(data, glm::vec3(0,0,0), modelMatrix));
	}

	{
		std::vector<std::string> data(2);
		data[0] = "cube";
		data[1] = "MainShader";

		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(1.1f, 0.f, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.4f, 1.4f, 0.35f));
		components.push_back(std::make_tuple(data, glm::vec3(0, 0, 0), modelMatrix));
	}

	{
		std::vector<std::string> data(2);
		data[0] = "cube";
		data[1] = "MainShader";

		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 1.5f, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1.35f, 0.4f, 0.35f));
		components.push_back(std::make_tuple(data, glm::vec3(0, 0, 0), modelMatrix));
	}

	{
		std::vector<std::string> data(2);
		data[0] = "cube";
		data[1] = "MainShader";

		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -1.18f, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f, 0.4f, 0.35f));
		components.push_back(std::make_tuple(data, glm::vec3(0, 0, 0), modelMatrix));
	}


	{
		std::vector<std::string> data(2);
		data[0] = "cube";
		data[1] = "MainShader";

		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(1.23f, 1.5f, 0));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(45), glm::vec3(0, 0, 1));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.55f, 0.55f));
		components.push_back(std::make_tuple(data, glm::vec3(0,0,0), modelMatrix));
	}
	/*
	{
		std::vector<std::string> data(2);
		data[0] = "cube";
		data[1] = "MainShader";

		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1.3f, 1.3f, 0.9f));
		components.push_back(std::make_tuple(data, glm::vec3(1, 1, 1), modelMatrix));
	}
	*/
	{
		std::vector<std::string> data(2);
		data[0] = "cube";
		data[1] = "MainShader";

		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(1.23f, 1.5f, 0));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(45), glm::vec3(0, 0, 1));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(2.f, 0.35f, 0.35f));
		components.push_back(std::make_tuple(data, glm::vec3(0.5f, 0.5f, 0.5f), modelMatrix));
	}


	angularStep = -M_PI/4 * 40;
}

Fuel::~Fuel() {

}

std::vector<std::tuple<std::vector<std::string>, glm::vec3, glm::mat4>> Fuel::update(float deltaTimeSeconds, float angular_speed) {

	std::vector<std::tuple<std::vector<std::string>, glm::vec3, glm::mat4>> out;

	
	
	glm::mat4 transform = glm::mat4(1);
	transform = glm::rotate(transform, angularStep/40, glm::vec3(0, 0, 1));
	transform = glm::translate(transform, glm::vec3(xCoord, yCoord, zCoord));
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

float Fuel::getAngle() {
	return angularStep / 40;
}

std::vector<std::pair<glm::vec3, glm::vec3>> Fuel::getBoundingBoxes() {
	std::vector<std::pair<glm::vec3, glm::vec3>> out;

	glm::mat4 transform = glm::mat4(1);
	transform = glm::rotate(transform, angularStep / 40, glm::vec3(0, 0, 1));
	transform = glm::translate(transform, glm::vec3(xCoord, yCoord, zCoord));
	
	glm::vec3 centre = transform * glm::vec4(0, 0, 0, 1);
	float x = 2.f;
	float y = 2.f;
	float z = 0.8f;

	out.push_back(std::make_pair(centre, glm::vec3(x, y, z)));

	return out;
}
