#pragma once
#include <Component/SimpleScene.h>
#include <Component/Transform/Transform.h>
#include <Core/GPU/Mesh.h>
#include "CameraHW3.h"

class Tema3 : public SimpleScene
{
public:
	Tema3();
	~Tema3();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1 = NULL, Texture2D* texture2 = NULL);
	void RenderSkybox(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, GLuint textureID);
	GLuint LoadCubemap(std::vector<const GLchar* > faces);
	GLuint LoadTexture(GLchar* path);
	void reload_terrain(unsigned char* heightMap, GLuint terrain_id);
	void RenderTerrain(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, GLuint terrain_id, Texture2D* texture1, Texture2D* texture2);
	float calculate_oy(glm::vec3 position);

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;

	CameraHW3::Camera* camera;
	glm::mat4 projectionMatrix;
	float fov, width;
	bool renderCameraTarget;
	
	unsigned char* heightMap;
	int mapWidth, mapHeight;
	std::unordered_map<std::string, Texture2D*> mapTextures;
	GLuint skybox;
	GLuint randomTextureID;
	GLuint terrain_id;
	GLenum polygonMode;
	float reflection_factor = 0.25f;
	float refraction_factor = 0.75f;

	glm::vec3 lightPosition1;
	glm::vec3 lightPosition2;
	glm::vec3 lightPosition3;
	glm::vec3 lightDirection;
	unsigned int materialShininess;
	float materialKd;
	float materialKs;
	float angle;
	glm::vec3 player1;
	float angle_player1;
	float ox_angle_player1;
	glm::vec3 player2;
	float angle_player2;
	float ox_angle_player2;
	int current_player;
	float fuel;

	glm::vec3 projectile_position;
	float speed_ox;
	float speed_oy;
	float speed_oz;
	float power;
	int ok;
	bool free_mode;
};
