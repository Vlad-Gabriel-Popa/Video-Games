#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>
#include "PillarManager.h"
#include "Bird.h"
class Tema1 : public SimpleScene
{
	public:
		Tema1();
		~Tema1();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;
		void RenderObject(Object* object, glm::ivec2 resolution, float deltaTimeSeconds);
		void draw_sky(glm::ivec2 resolution, float deltaTimeSeconds);

	protected:
		glm::mat3 modelMatrix, modelMatrix2;
		std::vector<std::pair<glm::vec2, glm::mat3>> stars;
		std::vector<std::string> star_color;
		std::vector<std::string> cloud_color;
		std::vector<std::string> random_square, random_circle;
		float time_of_day;
		float next_change;
		std::string sky_color;
		bool is_rotating;
		int score;
		PillarManager* pillar_manager;
		Bird* bird;
		bool game_over;
		bool gangster_mode;
		bool show_bb;
};		
