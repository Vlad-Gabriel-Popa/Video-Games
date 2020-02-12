#include "Plane.h"
#include <vector>
#include <iostream>
#include<string>

using namespace std;

Plane::Plane(int mouseY, int screen_height) {

	glm::vec3 color(1, 0.15f, 0.15f);

	{
		std::vector<std::string> data(2);
		data[0] = "plane_body";
		data[1] = "MainShader";
		
		
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.6, 1.6, 1.6));
			components.push_back(std::make_tuple(data, color, modelMatrix));
	}

	{
		std::vector<std::string> data(2);
		data[0] = "cube";
		data[1] = "MainShader";

		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-4.f, -0.04f, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f, 1.88f, 1.88f));
		components.push_back(std::make_tuple(data, glm::vec3(1,1,1), modelMatrix));
	}


	{
		std::vector<std::string> data(2);
		data[0] = "window";
		data[1] = "MainShader";

		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.3f, 0.7f, 0));

		modelMatrix = glm::rotate(modelMatrix, (float)(M_PI / 32), glm::vec3(0, 0, 1));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.8f, 1.5f, 1.f));
		components.push_back(std::make_tuple(data, glm::vec3(0.1, 0.1, 0.1), modelMatrix));
	}
	

	{
		std::vector<std::string> data(2);
		data[0] = "cube";
		data[1] = "MainShader";
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -0.2f, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(2.2f, 0.6f, 16.f));
		components.push_back(std::make_tuple(data, color, modelMatrix));
	}
	{
		std::vector<std::string> data(2);
		data[0] = "cube";
		data[1] = "MainShader";
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -0.2f, 6.f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(2.22f, 0.62f, 0.7f));
		components.push_back(std::make_tuple(data, glm::vec3(1,1,1), modelMatrix));
	}

	{
		std::vector<std::string> data(2);
		data[0] = "cube";
		data[1] = "MainShader";
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -0.2f, -6.f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(2.22f, 0.62f, 0.7f));
		components.push_back(std::make_tuple(data, glm::vec3(1, 1, 1), modelMatrix));
	}

	


	{
		std::vector<std::string> data(2);
		data[0] = "nose";
		data[1] = "MainShader";
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(3.8f, 0.f, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1.4f, 1.4f, 1.4f));
		components.push_back(std::make_tuple(data, glm::vec3(0.13f, 0.05f, 0.05f), modelMatrix));
	}

	{
		std::vector<std::string> data(2);
		data[0] = "cube";
		data[1] = "MainShader";
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(5.7f, 0, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1.6f, 0.3f, 0.3f));
		components.push_back(std::make_tuple(data, glm::vec3(0.66f, 0.66f, 0.7f), modelMatrix));
		
	}
/*
	{
		std::vector<std::string> data(2);
		data[0] = "cube";
		data[1] = "MainShader";
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(12.f, 2.2f, 8.f));
		components.push_back(std::make_tuple(data, glm::vec3(0.66f, 0.66f, 0.7f), modelMatrix));

	}
	*/

	{
		std::vector<std::string> data(2);
		data[0] = "cube";
		data[1] = "MainShader";
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(6.f, 1.5f, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.25f, 3.f, 0.5f));
		rotors.push_back(std::make_tuple(data, glm::vec3(0.66f, 0.66f, 0.7f), modelMatrix));
	}

	{
		std::vector<std::string> data(2);
		data[0] = "cube";
		data[1] = "MainShader";
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(6.f, 0.f, 0));
		modelMatrix = glm::rotate(modelMatrix, (float)(2 * M_PI / 3), glm::vec3(1, 0, 0));
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.f, 1.5f, 0.f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.25f, 3.f, 0.5f));
		rotors.push_back(std::make_tuple(data, glm::vec3(0.66f, 0.66f, 0.7f), modelMatrix));
	}

	{
		std::vector<std::string> data(2);
		data[0] = "cube";
		data[1] = "MainShader";
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(6.f, 0.f, 0));
		modelMatrix = glm::rotate(modelMatrix, (float)(4 * M_PI / 3), glm::vec3(1, 0, 0));
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.f, 1.5f, 0.f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.25f, 3.f, 0.5f));
		rotors.push_back(std::make_tuple(data, glm::vec3(0.66f, 0.66f, 0.7f), modelMatrix));
	}

	angluar_speed = 20;
	oy_position = 210.f;
	angle = 0;
	plane_speed = 0;
	plane_angle = 0;
	start = false;
	colliding = false;
	lives = 3;
	fuel = 100.f;
	fuel_depletion_speed = 3.f;
	game_over = false;
}

Plane::~Plane() {

}

std::vector<std::tuple<std::vector<std::string>, glm::vec3, glm::mat4>> Plane::update(float deltaTimeSeconds, int mouseY, int mouseX, int screen_height, int screen_width) {

	std::vector<std::tuple<std::vector<std::string>, glm::vec3, glm::mat4>> out;
	float destination = 0;
	float ox_position = -20;

	fuel -= fuel_depletion_speed * deltaTimeSeconds;
	if (fuel > 100) {
		fuel = 100;
	}

	if (game_over) {
		oy_position -= fall_speed * deltaTimeSeconds;
		fall_angle -= fall_speed/5 * deltaTimeSeconds;
		fall_speed += 14.f * deltaTimeSeconds;
		if (fall_speed > 50.f) {
			fall_speed = 50.f;
		}
	}
	else {
		if (colliding && collision_time >= 3.f) {
			impact_time = Engine::GetElapsedTime();
			impact_oy = oy_position;
			last_pulse = 2.3f;
		}
		collision_time -= deltaTimeSeconds;

		if (colliding && collision_time > 2.4f) {
			float current_time = Engine::GetElapsedTime();
			ox_position = -20 + 10 * collision_direction.x * sin(M_PI * (current_time - impact_time) / 0.6f);
			oy_position = impact_oy + 10 * collision_direction.y * sin(M_PI * (current_time - impact_time) / 0.6f);

			destination = oy_position;
		}
		else {
			if (collision_time < 0) {
				colliding = false;
			}

			destination = 265.f - ((float)mouseY) / screen_height * 90.f;
			if (destination > 250.f) {
				destination = 250.f;
			}
			if (destination < 190.f) {
				destination = 190.f;
			}

			if (is_third_person) {
				oz_destination = (-1.f) * (20.f - ((float)mouseX) / screen_width * 40.f);
				cout << oz_destination << endl;
				if (oz_destination > 10.f) {
					oz_destination = 10.f;
				}
				if (oz_destination < -10.f) {
					oz_destination = -10.f;
				}
				oz_direction = (oz_destination > oz_position) ? 1 : -1;

				if (abs(oz_destination - oz_position) < .1f) {
					oz_position = oz_destination;
				}
				else {
					oz_position += (oz_destination - oz_position) * 2.5f * deltaTimeSeconds;
				}
			}

			direction = (destination > oy_position) ? 1 : -1;

			if (abs(destination - oy_position) < .1f) {
				oy_position = destination;
			}
			else {
				oy_position += (destination - oy_position) * 2.5f * deltaTimeSeconds;
			}

		}
	}
	float angle_destination = abs(destination - oy_position) * direction / 50;

	if (game_over) {
		angle_destination = -M_PI / 4;
	}

	int angle_dir = (angle_destination > plane_angle) ? 1 : -1;
	angle += deltaTimeSeconds *angluar_speed;

	
	if (start == false) {
		angle_destination = 0;
		start = true;
	}

	float k = 1;
	if (abs(angle_destination - plane_angle) < 0.2) {
		k = 0.2;
	}
	if (game_over) {
		k = 0.1f;
	}
	plane_angle += k* (angle_destination - plane_angle)* 15 * deltaTimeSeconds;

	if (colliding && last_pulse - collision_time > 0.5f) {
		last_pulse = collision_time;
	}

		glm::mat4 transform = glm::translate(glm::mat4(1), glm::vec3(ox_position, oy_position, oz_position));
		
		transform = glm::rotate(transform, plane_angle, glm::vec3(0, 0, 1));
		if (game_over) {
			transform = glm::rotate(transform, -fall_angle, glm::vec3(1, 0, 0));
		}
		transform = glm::scale(transform, glm::vec3(0.8f, 0.8f, 0.8f));

		for (auto& component : components) {
			vector<string> data;
			glm::vec3 color;
			glm::mat4 modelMatrix;

			std::tie(data, color, modelMatrix) = component;
			if (!colliding || colliding && last_pulse - collision_time > 0.15f || last_pulse - collision_time < 0) {

				
			}
			else {
				color = glm::vec3(0.2,0.2,0.2);
			}
			out.push_back(std::make_tuple(data, color, transform * modelMatrix));

		}

		transform = glm::rotate(transform, angle, glm::vec3(1, 0, 0));

		for (auto& component : rotors) {
			vector<string> data;
			glm::vec3 color;
			glm::mat4 modelMatrix;
			std::tie(data, color, modelMatrix) = component;
			if (!colliding || colliding && last_pulse - collision_time > 0.15f || last_pulse - collision_time < 0) {

				
			}
			else {
				color = glm::vec3(0.2,0.2,0.2);
			}
			out.push_back(std::make_tuple(data, color, transform * modelMatrix));

		}
	
	return out;
}


std::vector<std::tuple<std::vector<std::string>, glm::vec3, glm::mat4>> Plane::draw_here(glm::vec3 position, glm::vec3 scale, bool is_first_person) {
	std::vector<std::tuple<std::vector<std::string>, glm::vec3, glm::mat4>> out;

	glm::mat4 transform = glm::mat4(1);

	transform = glm::translate(transform, position);
	if (is_first_person) {
		transform = glm::rotate(transform, -(float)M_PI / 2, glm::vec3(0, 1, 0));
	}
	transform = glm::rotate(transform, (float)M_PI/2, glm::vec3(1, 0, 0));
	transform = glm::scale(transform, scale);

	for (auto& component : components) {
		vector<string> data;
		glm::vec3 color;
		glm::mat4 modelMatrix;
		std::tie(data, color, modelMatrix) = component;

		out.push_back(std::make_tuple(data, color, transform * modelMatrix));

	}

	for (auto& component : rotors) {
		vector<string> data;
		glm::vec3 color;
		glm::mat4 modelMatrix;
		std::tie(data, color, modelMatrix) = component;

		out.push_back(std::make_tuple(data, color, transform * modelMatrix));
	}

	return out;
}

std::vector<std::pair<glm::vec3, glm::vec3>> Plane::getBoundingBoxes() {
	std::vector<std::pair<glm::vec3, glm::vec3>> out;

	glm::mat4 transform = glm::translate(glm::mat4(1), glm::vec3(-20, oy_position, oz_position));
	transform = glm::scale(transform, glm::vec3(0.8f, 0.8f, 0.8f));

	glm::vec3 centre = transform * glm::vec4(0, 0, 0, 1);
	float x = 4.8f;
	float y = 0.88f;
	float z = 5.5f;

	if (is_first_person) {
		x = .01f;
		y = 0.2f;
	}
	out.push_back(std::make_pair(centre, glm::vec3(x, y, z)));
	return out;
}

float Plane::getOy() {
	return oy_position;
}

void Plane::fuel_up() {
	this->fuel += 8.f;
}

void Plane::collide(glm::vec3 obstacle_centre) {
	if (colliding == false) {
		colliding = true;
		collision_time = 3.f;
		collision_direction = glm::normalize(getBoundingBoxes().front().first - obstacle_centre);
		lives--;
	}
}

void Plane::crash() {
	game_over = true;
	fall_angle = 0;
	fall_speed = 0;
}


void Plane::first_person() {
	is_first_person = true;
	is_third_person = false;
	oz_position = 0;
}
void Plane::normal_mode() {

	is_first_person = false;
	is_third_person = false;
	oz_position = 0;
}

void Plane::third_person() {

	is_first_person = false;
	is_third_person = true;
}