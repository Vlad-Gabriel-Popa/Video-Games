#include "Bird.h"
#include "Transform2D.h"
#include <vector>
#include <iostream>
#include<string>

using namespace std;

Bird::Bird() {

	// Bird bounding boxes
	// 2 rectangles. The 5th coordinate is the center
	bounding_boxes.resize(10);

	bounding_boxes[0] = glm::vec3(71.0f, 39.0f, 1);
	bounding_boxes[1] = glm::vec3(150.0f, 39.0f, 1);
	bounding_boxes[2] = glm::vec3(150.0f, 95.0f, 1);
	bounding_boxes[3] = glm::vec3(71.0f, 95.0f, 1);
	bounding_boxes[4] = glm::vec3((71.0f + 150.0f)/2.0f, (39.0f + 95.0f)/2.0f, 1);

	bounding_boxes[5] = glm::vec3(10.0f, 6.0f, 1);
	bounding_boxes[6] = glm::vec3(110.0f, 6.0f, 1);
	bounding_boxes[7] = glm::vec3(110.0f, 70.0f, 1);
	bounding_boxes[8] = glm::vec3(10.0f, 70.0f, 1);
	bounding_boxes[9] = glm::vec3((10.0f + 110.0f) / 2.0f, (6.0f + 70.0f) / 2.0f, 1);


	//Calculate the bird's coordinates in a local coordinate system
	components.resize(12);

	components[0].first = "yellow_circle";
	components[1].first = "black_circle";
	components[2].first = "white_circle";
	components[3].first = "black_circle";
	components[4].first = "orange_square";
	components[5].first = "black_square";
	components[6].first = "orange_square";
	components[7].first = "black_square";
	components[8].first = "yellow_square";
	components[9].first = "black_square";
	components[10].first = "yellow_circle";
	components[11].first = "black_circle";


	glm::mat3 modelMatrix;

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(41, 54) * Transform2D::Scale(33.0f, 17.0f);
	components[0].second = modelMatrix;

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(41, 54) * Transform2D::Scale(33.0f  + 3.0f, 17.0f  + 3.0f);
	components[1].second = modelMatrix;

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(124, 80) * Transform2D::Scale(7.0f, 4.0f);
	components[2].second = modelMatrix;

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(124, 80) * Transform2D::Scale(7.0f + 3.0f, 4.0f + 3.0f);
	components[3].second = modelMatrix;

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(145, 66) * Transform2D::Scale(24.0f, 9.0f) * Transform2D::Translate(-0.5f, -0.5f);
	components[4].second = modelMatrix;

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(145, 66) * Transform2D::Scale(24.0f + 3.0f, 9.0f + 3.0f) * Transform2D::Translate(-0.5f, -0.5f);
	components[5].second = modelMatrix;


	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(145, 55) * Transform2D::Scale(24.0f, 9.0f) * Transform2D::Translate(-0.5f, -0.5f);
	components[6].second = modelMatrix;

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(145, 55) * Transform2D::Scale(24.0f + 3.0f, 9.0f + 3.0f) * Transform2D::Translate(-0.5f, -0.5f);
	components[7].second = modelMatrix;


	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(103, 66) * Transform2D::Scale(55.0f, 55.0f) * Transform2D::Translate(-0.5f, -0.5f);
	components[8].second = modelMatrix;

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(103, 66) * Transform2D::Scale(55.0f + 5.0f, 55.0f + 5.0f) * Transform2D::Translate(-0.5f, -0.5f);
	components[9].second = modelMatrix;


	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(60, 38) * Transform2D::Scale(50.0f, 34.0f);
	components[10].second = modelMatrix;

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(60, 38) * Transform2D::Scale(50.0f + 3.0f, 34.0f + 3.0f);
	components[11].second = modelMatrix;



	//Calculate sunglasess
	sunglasses.resize(2);
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(128, 80) * Transform2D::Scale(14.0f + 3.0f, 18.0f + 3.0f) * Transform2D::Translate(-0.5f, -0.5f);
	sunglasses[0].second = modelMatrix;
	sunglasses[0].first = "black_square";
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(104, 80) * Transform2D::Scale(35.0f, 10.0f) * Transform2D::Translate(-0.5f, -0.5f);
	sunglasses[1].second = modelMatrix;
	sunglasses[1].first = "black_square";

	//Calculate 5 possible positions for the wings
	wings.resize(10);
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(41, 54) * Transform2D::Scale(33.0f, 17.0f);
	wings[0].second = modelMatrix;

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(41, 54) * Transform2D::Scale(33.0f + 3.0f, 17.0f + 3.0f);
	wings[1].second = modelMatrix;
	
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(47, 47) * Transform2D::Scale(45.0f, 23.0f);
	wings[2].second = modelMatrix;

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(47, 47) * Transform2D::Scale(45.0f + 3.0f, 23.0f + 3.0f);
	wings[3].second = modelMatrix;

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(41, 54) * Transform2D::Scale(33.0f, 17.0f);
	wings[4].second = modelMatrix;

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(41, 54) * Transform2D::Scale(33.0f + 3.0f, 17.0f + 3.0f);
	wings[5].second = modelMatrix;

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(42, 68) * Transform2D::Scale(32.0f, 3.0f);
	wings[6].second = modelMatrix;

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(42, 68) * Transform2D::Scale(32.0f + 3.0f, 3.0f + 3.0f);
	wings[7].second = modelMatrix;

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(43, 81) * Transform2D::Scale(34.0f, 8.0f);
	wings[8].second = modelMatrix;

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(43, 81) * Transform2D::Scale(34.0f + 3.0f, 8.0f + 3.0f);
	wings[9].second = modelMatrix;

	wing_index = 0;

	position_ox = 40.0f;
	position_oy = 50.0f;
	angular_position = 0.0f;
	game_over = false;
}

Bird::~Bird() {

}

float Bird::get_position() {
	return position_ox;
}

std::vector<std::pair<std::string, glm::mat3>>  Bird::update(glm::ivec2 resolution, float deltaTimeSeconds) {
	if (!game_over) {
		//Update bird position and rotation
		if (started) {
			position_oy += speed * deltaTimeSeconds;
			angular_position += speed / 25.0f * deltaTimeSeconds + boost * deltaTimeSeconds;
			speed -= g * deltaTimeSeconds;

		}
		if (angular_position > M_PI / 8) {
			angular_position = M_PI / 8;
			boost = 0;
		}
		if (angular_position < -M_PI / 2) angular_position = -M_PI / 2;
		if (speed < -90.0f) speed = -90.0f;

		wait_time += deltaTimeSeconds;

		if (angular_position < 0 && (wing_index == 0 || wing_index == 2)) {
			wait_time = 0;
		}

		//Change wing matrix at every 0.1 seconds
		if (wait_time > 0.1f) {
			wing_index = (wing_index + 1) % 5;
			wait_time = 0;
		}
	}

	components[0].second = wings[2 * wing_index].second;
	components[1].second = wings[2 * wing_index + 1].second;


	//Calculate position in world space and return matrices
	float ox = ((float)resolution.x) / 100 * position_ox;
	float oy = ((float)resolution.y) / 100 * position_oy;
	float scale_factor = resolution.y / 1000.0f;
	std::vector<std::pair<std::string, glm::mat3>> output;
	transformation = glm::mat3(1);
	transformation *= Transform2D::Translate(ox, oy)* Transform2D::Scale(scale_factor, scale_factor)* Transform2D::Rotate(angular_position)* Transform2D::Translate(-64, -47);
	
	for (auto& component : components) {
		output.push_back(make_pair(component.first, transformation * component.second));
	}

	return output;
}

// Calculate bounding boxes coordinates in world space
std::vector<glm::vec3> Bird::getBoundingBoxes() {
	vector<glm::vec3> out;
	for (auto& point : bounding_boxes) {
		out.push_back(transformation * point);
	}
	return out;
}

void Bird::stop() {
	game_over = true;
}
// Activate gangster mode
void Bird::gangster() {
	if (!game_over) {
		std::swap(components[2], sunglasses[0]);
		std::swap(components[3], sunglasses[1]);
	}
}