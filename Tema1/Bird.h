#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>
#include "Object.h"

class Bird : public Object
{
	public:
		Bird();
		float speed;
		bool started;
		float boost;
		~Bird();
		std::vector<std::pair<std::string, glm::mat3>> update(glm::ivec2 resolution, float deltaTimeSeconds);
		std::vector<glm::vec3> getBoundingBoxes();
		float get_position();
		void stop();
		void gangster();
	protected:
		std::vector<std::pair<std::string, glm::mat3>> components, sunglasses, wings;
		bool beating_up;
		int wing_index;
		float wait_time;

		bool game_over;
		bool gangster_mode;
		float position_oy;
		float angular_position;
		const float g = 300.0f;
		float position_ox;
		glm::mat3 transformation;
		std::vector<glm::vec3> bounding_boxes;
};
