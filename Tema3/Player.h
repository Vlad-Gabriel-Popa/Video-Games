#pragma once
#include <include/glm.h>
#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

class Player
{
public:
	Player(glm::vec3 position);
	~Player();
	std::vector<std::tuple<std::vector<std::string>, glm::vec3, glm::mat4>> update(float deltaTimeSeconds, int mouseY, int mouseX, int screen_height, int screen_width);
	std::vector<std::pair<glm::vec3, glm::vec3>> getBoundingBoxes();
	std::vector<std::tuple<std::vector<std::string>, glm::vec3, glm::mat4>> draw_here(glm::vec3 position, glm::vec3 scale, bool is_first_person);
	float getOy();
	void collide(glm::vec3 obstacle_centre);
	void fuel_up();
	void crash();
	void first_person();
	void normal_mode();
	void third_person();
	bool colliding;
	int lives;
	float fuel, fuel_depletion_speed;
	float oz_position;
private:
	std::vector<std::tuple<std::vector<std::string>, glm::vec3, glm::mat4>> components, rotors;
	float angluar_speed;
	float oy_position;
	float angle;
	float plane_speed;
	int direction;
	float plane_angle;
	bool start, game_over;

	float impact_time;
	float impact_oy;
	float last_pulse;
	float collision_time;
	float fall_speed;
	float fall_angle;
	glm::vec3 collision_direction;
	bool is_first_person = false;
	bool is_third_person = false;

	float oz_angle;
	float oz_direction;
	float oz_destination;
	float oz_plane_angle;
};