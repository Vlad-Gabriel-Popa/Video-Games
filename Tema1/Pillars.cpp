#include "Pillars.h"
#include "Transform2D.h"
#include <vector>
#include<string>
#include <iostream>
#include <random>
#include <time.h>

using namespace std;

Pillars::~Pillars()
{
}

Pillars::Pillars(std::mt19937 gen, float ox_position, float previous_hole_position, float width, float pillar_speed,bool gangster_mode, bool move, float pillar_width, float brick_width, float brick_length) {

	hole_width = width;
	this->ox_position = ox_position;
	this->pillar_speed = pillar_speed;
	this->pillar_width = pillar_width;
	this->brick_width = brick_width;
	this->brick_length = brick_length;
	this->gangster_mode = gangster_mode;
	this->move = move;
	
	if (gangster_mode) hole_width += 5;
	std::random_device rd;
	std::mt19937 gen2(rd());
	std::normal_distribution<float> d(previous_hole_position, 200.0f);
	
	//calculate a random hole position based on the value of the previous one
	int count = 0;
	do
	{	
		count++;
		if (count == 100) {
			hole_position = 50.0f;
			break;
		}
		hole_position = d(gen2);
	} while (hole_position < hole_width/2.0f  + brick_length * 2.0f || hole_position > 100.0f - hole_width/2.0f - brick_length);

	//Calculate postion of a pillar in local space
	glm::mat3 modelMatrix;
	float up_brick_oy = hole_position + hole_width / 2.0f + brick_length / 2.0f;

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(0, up_brick_oy) * Transform2D::Scale(brick_width, brick_length) * Transform2D::Translate(-0.5f, -0.5f);
	up_pillar.push_back(make_pair(std::string("green_square"), modelMatrix));


	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(0, up_brick_oy) * Transform2D::Scale(brick_width * 1.1f, brick_length * 1.1f) * Transform2D::Translate(-0.5f, -0.5f);
	up_pillar.push_back(make_pair(std::string("black_square"), modelMatrix));


	float up_pillar_length = 120.0f - (hole_position + hole_width / 2.0f + brick_length);
	float up_pillar_oy = (120.0f + (hole_position + hole_width / 2.0f + brick_length)) / 2.0f;

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(0, up_pillar_oy) * Transform2D::Scale(pillar_width,up_pillar_length) * Transform2D::Translate(-0.5f, -0.5f);
	up_pillar.push_back(make_pair(std::string("green_square"), modelMatrix));

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(0, up_pillar_oy) * Transform2D::Scale(pillar_width * 1.1f, up_pillar_length) * Transform2D::Translate(-0.5f, -0.5f);
	up_pillar.push_back(make_pair(std::string("black_square"), modelMatrix));


	float down_brick_oy = hole_position - hole_width / 2.0f - brick_length / 2.0f;

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(0, down_brick_oy) * Transform2D::Scale(brick_width,brick_length) * Transform2D::Translate(-0.5f, -0.5f);
	down_pillar.push_back(make_pair(std::string("green_square"), modelMatrix));

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(0, down_brick_oy) * Transform2D::Scale( brick_width * 1.1f, brick_length * 1.1f) * Transform2D::Translate(-0.5f, -0.5f);
	down_pillar.push_back(make_pair(std::string("black_square"), modelMatrix));


	float down_pillar_length = hole_position - hole_width / 2.0f - brick_length + 20.f;
	float down_pillar_oy = down_pillar_length / 2.0f - 20.f;


	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(0,  down_pillar_oy) * Transform2D::Scale( pillar_width, down_pillar_length) * Transform2D::Translate(-0.5f, -0.5f);
	down_pillar.push_back(make_pair(std::string("green_square"), modelMatrix));


	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(0,  down_pillar_oy) * Transform2D::Scale(pillar_width * 1.1f, down_pillar_length) * Transform2D::Translate(-0.5f, -0.5f);
	down_pillar.push_back(make_pair(std::string("black_square"), modelMatrix));


	//Calculate bounding boxes
	float val1 = 0.f, val2 = 0.f;
	bounding_boxes.resize(20);
	bounding_boxes[0] = glm::vec3(-pillar_width / 2.0f + val1, -20.f, 1);
	bounding_boxes[1] = glm::vec3(pillar_width / 2.0f - val1, -20.f, 1);
	bounding_boxes[2] = glm::vec3(pillar_width / 2.0f - val1, down_brick_oy - brick_length/2.0f, 1);
	bounding_boxes[3] = glm::vec3(-pillar_width / 2.0f + val1 , down_brick_oy - brick_length / 2.0f, 1);
	bounding_boxes[4] = glm::vec3(0, down_pillar_oy, 1);

	bounding_boxes[5] = glm::vec3(-brick_width / 2.0f + val2, down_brick_oy - brick_length / 2.0f, 1);
	bounding_boxes[6] = glm::vec3(brick_width / 2.0f - val2 , down_brick_oy - brick_length / 2.0f, 1);
	bounding_boxes[7] = glm::vec3(brick_width / 2.0f - val2, down_brick_oy + brick_length / 2.0f - 3.f, 1);
	bounding_boxes[8] = glm::vec3(-brick_width / 2.0f + val2, down_brick_oy + brick_length / 2.0f - 3.f, 1);
	bounding_boxes[9] = glm::vec3(0, down_brick_oy, 1);

	bounding_boxes[10] = glm::vec3(-brick_width / 2.0f + val2, up_brick_oy - (brick_length / 2.0f) + 3.f , 1);
	bounding_boxes[11] = glm::vec3(brick_width / 2.0f - val2, up_brick_oy - (brick_length / 2.0f) + 3.f, 1);
	bounding_boxes[12] = glm::vec3(brick_width / 2.0f - val2, up_brick_oy + brick_length / 2.0f, 1);
	bounding_boxes[13] = glm::vec3(-brick_width / 2.0f + val2, up_brick_oy + brick_length / 2.0f, 1);
	bounding_boxes[14] = glm::vec3(0, up_brick_oy, 1);

	bounding_boxes[15] = glm::vec3(-pillar_width / 2.0f + val1, up_brick_oy + brick_length / 2.0f, 1);
	bounding_boxes[16] = glm::vec3(pillar_width / 2.0f - val1, up_brick_oy + brick_length / 2.0f, 1);
	bounding_boxes[17] = glm::vec3(pillar_width / 2.0f - val1, 100.0f, 1);
	bounding_boxes[18] = glm::vec3(-pillar_width / 2.0f + val1, 100.0f, 1);
	bounding_boxes[19] = glm::vec3(0, up_pillar_oy, 1);

	game_over = false;
	//random angle for pillars when gangster mode is active
	gangster_angle  = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5f;

	colors[0] = "green_square";
	colors[1] = "yellow_square";
	colors[2] = "blue_square";
	colors[3] = "orange_square";
	colors[4] = "magenta_square";

	//random pillar colors if ganster mode is active
	if (gangster_mode) {
		up_color = colors[rand() % 5];
		down_color = colors[rand() % 5];
	}
	wait_time = 0;

	move_distance = 8;
	current_move = (float)(rand() % 5) * pow(-1, rand()%2);
	moving_up = true;
	counted = false;
}

void Pillars::stop() {
	game_over = true;
}

void Pillars::gangster() {

}

std::vector<std::pair<std::string, glm::mat3>>  Pillars::update(glm::ivec2 resolution, float deltaTimeSeconds) {
	//Update position
	if (!game_over)
		ox_position -= pillar_speed * deltaTimeSeconds;

	float ox_unit = (float)resolution.x / 100.0f;
	float oy_unit = (float)resolution.y / 100.0f;
	vector<std::pair<std::string, glm::mat3>> output;

	//Transformation matrix if gangster mode is disabled
	if (!gangster_mode) {
		transformation1 = glm::mat3(1);
		transformation1 *= Transform2D::Translate(ox_position * ox_unit, hole_position * oy_unit) * Transform2D::Scale(ox_unit, oy_unit) * Transform2D::Translate(0, -hole_position);
		transformation2 = transformation1;
		up_color = "green_square";
		down_color = "green_square";
	}
	//Gangster mode active
	else {
		// If the pillars are moving update movement
		if (move) {
			if (moving_up) {
				current_move += deltaTimeSeconds * pillar_speed/2;
			}
			else {
				current_move -= deltaTimeSeconds * pillar_speed/2;
			}

			if (current_move > move_distance) moving_up = false;
			if (current_move < -5.f) moving_up = true;
		}
		else {
			current_move = 0;
		}
		// Calculate matrices for the two diffrent pillars
		transformation1 = glm::mat3(1);
		transformation1 *= Transform2D::Translate(ox_position * ox_unit, (hole_position ) * oy_unit) * Transform2D::Scale(ox_unit, oy_unit) * Transform2D::Rotate(gangster_angle) * Transform2D::Translate(0, -hole_position - current_move);
		
		transformation2 = glm::mat3(1);
		transformation2 *= Transform2D::Translate(ox_position * ox_unit, (hole_position ) * oy_unit) * Transform2D::Scale(ox_unit, oy_unit) * Transform2D::Rotate(gangster_angle) * Transform2D::Translate(0, -hole_position + current_move);

		wait_time += deltaTimeSeconds;
		// Change pillar color every 0.5 seconds
		if (wait_time > 0.5f) {
			up_color = colors[rand() % 5];
			down_color = colors[rand() % 5];
			wait_time = 0;
		}
	}

	if (!gangster_mode) {
		up_color = "green_square";
		down_color = "black_square";
	}
	// Apply world space transformations
	int i = 0;
	for (auto& component : up_pillar) {
		if(i % 2 ==0)
			output.push_back(make_pair(up_color, transformation2 * component.second));
		else
			output.push_back(make_pair(down_color, transformation2 * component.second));
		i++;
	}

	if (!gangster_mode) {
		down_color = "green_square";
		up_color = "black_square";
	}
	i = 0;
	for (auto& component : down_pillar) {
		if (i % 2 == 0)
			output.push_back(make_pair(down_color, transformation1 * component.second));
		else
			output.push_back(make_pair(up_color, transformation1 * component.second));
		i++;
	}

	return output;

}

std::vector<glm::vec3> Pillars::getBoundingBoxes() {
	vector<glm::vec3> out;
	int i = 0;
	for (auto& point : bounding_boxes) {
		if(i < 10)
			out.push_back(transformation1 * point);
		else
			out.push_back(transformation2 * point);
		i++;
	}
	return out;
}