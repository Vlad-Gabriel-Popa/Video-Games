#pragma once
#include <Component/SimpleScene.h>
#include <Component/Transform/Transform.h>
#include <Core/GPU/Mesh.h>
#include "Camera.h"
#include "Component.h"
#include "Plane.h"
#include "Fuel.h"
#include "Obstacle.h"
#include "Cloud.h"
#include "Manager.h"

class Tema2 : public SimpleScene
{
	public:
		Tema2();
		~Tema2();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix, const glm::vec3 &color = glm::vec3(1));

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;
		void draw_fuel();
		void draw_health();

		void RenderObject(std::vector<std::tuple<std::vector<std::string>, glm::vec3, glm::mat4>> object);
		void RenderUI(std::vector<std::tuple<std::vector<std::string>, glm::vec3, glm::mat4>> object);

		glm::vec3 lightPosition;
		unsigned int materialShininess;
		float materialKd;
		float materialKa;
		float materialKs;
		Camera::Camera* camera;
		glm::mat4 projectionMatrix;
		float fov, width;
		bool renderCameraTarget;
		float angle;
		int mouseY, deltaY, mouseX;
		Plane* plane;
		Fuel* fuel;
		Obstacle* obstacle;
		Cloud* cloud;
		Manager* manager;
		float camera_speed;
		bool game_over;
		float game_over_time;
		float sea_speed;
		bool is_first_person = false;
		bool is_third_person = false;
		std::vector<glm::vec3> sky_colors;
		std::vector<glm::vec3> steps;
		int periods_of_time = 6;
		float time_period = 6.f;
		float current_time = 0;
		int current_period = 0;
		float ka_step;
		float kd_step;
		float oy_light_step;
		int spot_active = 0;
		glm::vec3 spotPosition;
		glm::vec3 lightDirection;
		float spot_angle;
		float counter = 15;
};
