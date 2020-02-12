#include "Tema3.h"
#include "CreateObjects.h"
#include <vector>
#include <string>
#include <iostream>
#include <time.h>
#include <Core/Engine.h>
#include <stb/stb_image.h>
#include <stb/stb_image_write.h>

using namespace std;

Tema3::Tema3()
{
}

Tema3::~Tema3()
{
}

void Tema3::Init()
{
	current_player = 0;
	free_mode = false;
	renderCameraTarget = false;
	camera = new CameraHW3::Camera();
	camera->Set(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
	fov = 60;
	width = 1.5;
	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
	
	polygonMode = GL_FILL;
	const string textureLoc = "Source/Laboratoare/Tema3/Textures/";
	{
		vector<char const*> faces;
		faces.push_back("Source/Laboratoare/Tema3/Textures/ft.tga");
		faces.push_back("Source/Laboratoare/Tema3/Textures/bk.tga");
		faces.push_back("Source/Laboratoare/Tema3/Textures/up.tga");
		faces.push_back("Source/Laboratoare/Tema3/Textures/dn.tga");
		faces.push_back("Source/Laboratoare/Tema3/Textures/rt.tga");
		faces.push_back("Source/Laboratoare/Tema3/Textures/lf.tga");
		skybox = LoadCubemap(faces);
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "metal.jpg").c_str(), GL_REPEAT);
		mapTextures["metal"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "black_metal.jpg").c_str(), GL_REPEAT);
		mapTextures["bmetal"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "rock.jpg").c_str(), GL_MIRRORED_REPEAT);
		mapTextures["rock"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "dirt.png").c_str(), GL_REPEAT);
		mapTextures["dirt"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "grass.png").c_str(), GL_REPEAT);
		mapTextures["grass"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "earth.png").c_str(), GL_REPEAT);
		mapTextures["earth"] = texture;
	}

	

	{
		Mesh* mesh = new Mesh("cannon");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Characters/Cannon", "cannon.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D("Resources/Models/Characters/Cannon/cannon.jpg", GL_REPEAT);
		mapTextures["cannon"] = texture;
	}

	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}


	{
		Shader* shader = new Shader("Skybox");
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/VertexShaderSkybox.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/FragmentShaderSkybox.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shader = new Shader("Terrain");
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/VSTerrain.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/FSTerrain.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shader = new Shader("Reflection");
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/VertexShaderReflection.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/FragmentShaderReflection.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shader = new Shader("Refraction");
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/VertexShaderRefraction.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/FragmentShaderRefraction.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shader = new Shader("Normal");
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	int chn;
	heightMap = stbi_load((textureLoc + "heightmap.png").c_str(), &mapWidth, &mapHeight, &chn, STBI_grey);
	
	Mesh* terrain = Objects::generate_terrain(10.f, mapWidth, mapHeight);
	meshes[terrain->GetMeshID()] = terrain;
	glGenTextures(1, &terrain_id);
	reload_terrain(heightMap, terrain_id);

	{
		srand(time(NULL));
		lightPosition1 = glm::vec3(0, 10, 1);
		float x = -6.5f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 13.f));
		float z = -6.5f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 13.f));
		player1 = glm::vec3(x, 1, z);
		player1.y = calculate_oy(player1) + 0.085f;
		lightPosition2 = glm::vec3(0, 3.5f, 0) + player1;

		x = -6.5f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 13.f));
		z = -6.5f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 13.f));
		player2 = glm::vec3(x, 1, z);
		player2.y = calculate_oy(player2) + 0.085f;
		lightPosition3 = glm::vec3(0, 3.5f, 0) + player2;
		lightDirection = glm::vec3(0, -1, 0);
		materialShininess = 30;
		materialKd = 0.5;
		materialKs = 0.5;
		angle = 45.f;
		angle_player1 = 0;
		angle_player2 = 0;
		ox_angle_player1 = 0;
		power = 2.f;
	}
	ok = 0;
	fuel = 1.f;

}

void Tema3::reload_terrain(unsigned char* heightMap, GLuint terrain_id) {
	
	glBindTexture(GL_TEXTURE_2D, terrain_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, mapWidth, mapHeight, 0, GL_RED, GL_UNSIGNED_BYTE, (void*)heightMap);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

}

void Tema3::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0.5, 0.5, 0.3, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

float Tema3::calculate_oy(glm::vec3 position) {
	
	int x = (int)((position.x + 7.5f)/15.f * 255.f);
	int z = (int)((position.z + 7.5f)/15.f * 255.f);
	return ((float)heightMap[z * mapWidth + x] /255.f) * 2.f;
}

void Tema3::Update(float deltaTimeSeconds)
{
	glLineWidth(3);
	glPointSize(5);
	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

	if (current_player == 0 || current_player == 2) {
		float size = (power - 1.5f) / 2.f * 0.02;
		glm::vec3 position = camera->position + camera->forward * 0.1f + camera->right * 0.066f + camera->up * 0.046f;
		float angle_ox, angle_oy;
		if (current_player == 0) {
			angle_oy = angle_player1;
			angle_ox = ox_angle_player1;
		}
		if (current_player == 2) {
			angle_oy = angle_player2;
			angle_ox = ox_angle_player2;
		}
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, position);
			modelMatrix = glm::rotate(modelMatrix, angle_oy, glm::vec3(0, 1, 0));
			modelMatrix = glm::rotate(modelMatrix, -angle_ox, glm::vec3(1, 0, 0));
			modelMatrix = glm::rotate(modelMatrix, (float)(3*M_PI) / 4, glm::vec3(0, 1, 0));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.02, 0.005, 0.001));
			RenderSimpleMesh(meshes["box"], shaders["Reflection"], modelMatrix, mapTextures["metal"]);
		}

		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, position);
			modelMatrix = glm::rotate(modelMatrix, angle_oy, glm::vec3(0, 1, 0));
			modelMatrix = glm::rotate(modelMatrix, -angle_ox, glm::vec3(1, 0, 0));
			modelMatrix = glm::rotate(modelMatrix, (float)(3 * M_PI) / 4, glm::vec3(0, 1, 0));
			modelMatrix = glm::translate(modelMatrix, -glm::vec3((0.02f - size) / 2.f, 0, 0));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(size + 0.0005f, 0.00501, 0.00101));
			RenderSimpleMesh(meshes["box"], shaders["Reflection"], modelMatrix, mapTextures["bmetal"]);
		}
	}
	if (current_player == 0) {
		camera->distanceToTarget = 0.5f;
		camera->Set(player1 + glm::vec3(0, 0.2, -0.468), player1, glm::vec3(0, 1, 0));
		camera->RotateThirdPerson_OY(angle_player1);
		camera->RotateThirdPerson_OX(ox_angle_player1);
	}
	else if (current_player == 2) {

		camera->distanceToTarget = 0.5f;
		camera->Set(player2 + glm::vec3(0, 0.2, -0.468), player2, glm::vec3(0, 1, 0));
		camera->RotateThirdPerson_OY(angle_player2);
		camera->RotateThirdPerson_OX(ox_angle_player2);
	}
	else {
		if (ok == 0) {
			if (!free_mode) {
				camera->position.x += speed_ox * deltaTimeSeconds;
				camera->position.y += speed_oy * deltaTimeSeconds;
				camera->position.z += speed_oz * deltaTimeSeconds;
			}


			projectile_position.x += speed_ox * deltaTimeSeconds;
			projectile_position.y += speed_oy * deltaTimeSeconds;
			projectile_position.z += speed_oz * deltaTimeSeconds;
			speed_oy -= 2 * deltaTimeSeconds;

			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, projectile_position);
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
			RenderSimpleMesh(meshes["sphere"], shaders["Refraction"], modelMatrix, mapTextures["cannon"]);
		}
		if (ok == 0) {
			if (projectile_position.y < calculate_oy(projectile_position)) {
				cout << "KABOOOOMMM" << endl;

				int x = (int)((projectile_position.x + 7.5f) / 15.f * 255.f);
				int z = (int)((projectile_position.z + 7.5f) / 15.f * 255.f);

				int radius = power/0.5f;
				if (radius != 0) {
					for (int i = z - radius; i <= z + radius; i++) {
						for (int j = x - radius; j <= x + radius; j++) {
							float distance = sqrt(pow(z-i, 2) + pow(x-j, 2));
							if(distance < radius)
								heightMap[i * mapWidth + j] =  max(heightMap[i * mapWidth + j] - (int)((1 - distance / radius) * (10 + 8 * power)), 0);
						}
					}
					reload_terrain(heightMap, terrain_id);
					player1.y = calculate_oy(player1) + 0.085f;
					player2.y = calculate_oy(player2) + 0.085f;
				}

				ok = 1;
			}
		}
			//	current_player = (current_player + 1) % 4;
	}
		
	
	RenderTerrain(meshes["terrain"], shaders["Terrain"], glm::scale(glm::mat4(1), glm::vec3(15, 10, 15)), terrain_id, mapTextures["grass"], mapTextures["rock"]);

	
	{

		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, player1);
		modelMatrix = glm::rotate(modelMatrix, (float)M_PI + angle_player1, glm::vec3(0,1,0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.00015f));

		//modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
		RenderSimpleMesh(meshes["cannon"], shaders["Reflection"], modelMatrix, mapTextures["cannon"]);
	}

	{

		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, player2);
		modelMatrix = glm::rotate(modelMatrix, (float)M_PI + angle_player2, glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.00015f));
		//modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
		RenderSimpleMesh(meshes["cannon"], shaders["Reflection"], modelMatrix, mapTextures["cannon"]);
	}
	
	RenderSkybox(meshes["box"], shaders["Skybox"], glm::scale(glm::mat4(1), glm::vec3(100)), skybox);

	
}

void Tema3::FrameEnd()
{

	//DrawCoordinatSystem();
}

GLuint Tema3::LoadTexture(GLchar* path)
{
	//Generate texture ID and load texture data
	GLuint textureID;
	glGenTextures(1, &textureID);

	int imageWidth, imageHeight, chn;

	unsigned char* image = stbi_load(path, &imageWidth, &imageHeight, &chn, 0);

	// Assign texture to ID
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	return textureID;
}


GLuint Tema3::LoadCubemap(vector<char const*> faces)
{
	GLuint textureID;
	glGenTextures(1, &textureID);

	int imageWidth, imageHeight, chn;
	unsigned char* image;

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	for (GLuint i = 0; i < faces.size(); i++)
	{
		image = stbi_load(faces[i], &imageWidth, &imageHeight, &chn, 0);
		if (image == NULL) {
			cout << "ERROR " << faces[i] << endl;
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return textureID;
}

void Tema3::RenderSkybox(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, GLuint textureID) {

	if (!mesh || !shader || !shader->GetProgramID())
		return;

	glDepthFunc(GL_LEQUAL);
	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = glm::mat4(glm::mat3(camera->GetViewMatrix()));
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	//glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	//glActiveTexture(GL_TEXTURE2);
	//glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	int location = glGetUniformLocation(shader->program, "env_map");
	glUniform1i(location, 0);

	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);

	glDepthFunc(GL_LESS);
}

void Tema3::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1, Texture2D* texture2)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	glm::vec3 eyePosition = camera->position;
	GLint loc_eye_position = glGetUniformLocation(shader->program, "eye_position");
	glUniform3fv(loc_eye_position, 1, glm::value_ptr(eyePosition));

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	//glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));


	float timp = Engine::GetElapsedTime();
	int location = glGetUniformLocation(shader->GetProgramID(), "Time");
	glUniform1f(location, timp);

	location = glGetUniformLocation(shader->GetProgramID(), "reflection_factor");
	glUniform1f(location, reflection_factor);

	location = glGetUniformLocation(shader->GetProgramID(), "refraction_factor");
	glUniform1f(location, refraction_factor);

	if (texture1)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());

		int location = glGetUniformLocation(shader->program, "tex1");
		glUniform1i(location, 1);
	}

	if (texture2)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, texture2->GetTextureID());

		int location = glGetUniformLocation(shader->program, "tex2");
		glUniform1i(location, 2);
	}

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}



void Tema3::RenderTerrain(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, GLuint terrain_id, Texture2D* texture1, Texture2D* texture2)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);
	
	int light_position = glGetUniformLocation(shader->program, "light_position1");
	glUniform3f(light_position, lightPosition1.x, lightPosition1.y, lightPosition1.z);

	light_position = glGetUniformLocation(shader->program, "light_position2");
	glUniform3f(light_position, lightPosition2.x, lightPosition2.y, lightPosition2.z);

	light_position = glGetUniformLocation(shader->program, "light_position3");
	glUniform3f(light_position, lightPosition3.x, lightPosition3.y, lightPosition3.z);

	int light_direction = glGetUniformLocation(shader->program, "light_direction");
	glUniform3f(light_direction, lightDirection.x, lightDirection.y, lightDirection.z);

	int angle_pos = glGetUniformLocation(shader->program, "angle");
	glUniform1f(angle_pos, angle);

	// TODO: Set eye position (camera position) uniform
	glm::vec3 eyePosition = camera->position;
	GLint loc_eye_position = glGetUniformLocation(shader->program, "eye_position");
	glUniform3fv(loc_eye_position, 1, glm::value_ptr(eyePosition));

	// TODO: Set material property uniforms (shininess, kd, ks, object color) 
	int material_shininess = glGetUniformLocation(shader->program, "material_shininess");
	glUniform1i(material_shininess, materialShininess);

	int material_kd = glGetUniformLocation(shader->program, "material_kd");
	glUniform1f(material_kd, materialKd);

	int material_ks = glGetUniformLocation(shader->program, "material_ks");
	glUniform1f(material_ks, materialKs);


	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	//glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	GLint loc_mapSize = glGetUniformLocation(shader->program, "mapSize");
	glUniform2fv(loc_mapSize, 1, glm::value_ptr(glm::vec2(mapWidth, mapHeight)));


	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, terrain_id);
	int location = glGetUniformLocation(shader->program, "heightMap");
	glUniform1i(location, 1);

	if (texture1)
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());

		int location = glGetUniformLocation(shader->program, "tex1");
		glUniform1i(location, 2);
	}

	if (texture2)
	{
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, texture2->GetTextureID());

		int location = glGetUniformLocation(shader->program, "tex2");
		glUniform1i(location, 3);
	}


	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}





// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Tema3::OnInputUpdate(float deltaTime, int mods)
{
	float speed = 2;

	if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		glm::vec3 up = glm::vec3(0, 1, 0);
		glm::vec3 right = GetSceneCamera()->transform->GetLocalOXVector();
		glm::vec3 forward = GetSceneCamera()->transform->GetLocalOZVector();
		forward = glm::normalize(glm::vec3(forward.x, 0, forward.z));
	}

	if (window->KeyHold(GLFW_KEY_R)) {
		reflection_factor += deltaTime / 2;
		if (reflection_factor > 1.0f) {
			reflection_factor = 1.0f;
		}
	}
	if (window->KeyHold(GLFW_KEY_T)) {
		reflection_factor -= deltaTime / 2;
		if (reflection_factor < 0.f) {
			reflection_factor = 0.f;
		}
	}

	if (window->KeyHold(GLFW_KEY_F)) {
		refraction_factor += deltaTime / 2;
		if (refraction_factor > 1.0f) {
			refraction_factor = 1.0f;
		}
	}
	if (window->KeyHold(GLFW_KEY_G)) {
		refraction_factor -= deltaTime / 2;
		if (refraction_factor < 0.f) {
			refraction_factor = 0.f;
		}
	}

	if (current_player == 0 || current_player == 2) {
		if (window->KeyHold(GLFW_KEY_1)) {
			power += deltaTime;
			if (power > 3.5f) {
				power = 3.5f;
			}
			cout << "Power: " << power<<endl;
		}

		if (window->KeyHold(GLFW_KEY_2)) {
			power -= deltaTime;
			if (power < 1.5f) {
				power = 1.5f;
			}
			cout << "Power: " << power << endl;
		}
	}

	float cameraSpeed = 2.0f;

	if (window->KeyHold(GLFW_KEY_W)) {
		// TODO : translate the camera forward
		camera->TranslateForward(cameraSpeed * deltaTime);
		if (current_player == 0 && fuel > 0) {
			fuel -= fabs(glm::dot(camera->forward*deltaTime, glm::vec3(1)));
			player1 += camera->forward * deltaTime;
			player1.y = calculate_oy(player1) + 0.085f;
			lightPosition2 = glm::vec3(0, 3.5f, 0) + player1;
		}
		if (current_player == 2 && fuel > 0) {
			fuel -= fabs(glm::dot(camera->forward * deltaTime, glm::vec3(1)));
			player2 += camera->forward * deltaTime;
			player2.y = calculate_oy(player2) + 0.085f;
			lightPosition3 = glm::vec3(0, 3.5f, 0) + player2;
		}
	}

	if (window->KeyHold(GLFW_KEY_A)) {
		// TODO : translate the camera to the left
		camera->TranslateRight(-cameraSpeed * deltaTime);
		if (current_player == 0 && fuel > 0) {
			fuel -= fabs(glm::dot(camera->right * deltaTime, glm::vec3(1)));
			player1 -= camera->right * deltaTime;
			player1.y = calculate_oy(player1) + 0.085f;
			lightPosition2 = glm::vec3(0, 3.5f, 0) + player1;
		}
		if (current_player == 2 && fuel > 0) {
			fuel -= fabs(glm::dot(camera->right * deltaTime, glm::vec3(1)));
			player2 -= camera->right * deltaTime;
			player2.y = calculate_oy(player2) + 0.085f;
			lightPosition3 = glm::vec3(0, 3.5f, 0) + player2;
		}
	}

	if (window->KeyHold(GLFW_KEY_S)) {
		// TODO : translate the camera backwards
		camera->TranslateForward(-cameraSpeed * deltaTime);
		if (current_player == 0 && fuel > 0) {
			fuel -= fabs(glm::dot(camera->forward * deltaTime, glm::vec3(1)));
			player1 -= camera->forward * deltaTime;
			player1.y = calculate_oy(player1) + 0.085f;
			lightPosition2 = glm::vec3(0, 3.5f, 0) + player1;
		}
		if (current_player == 2 && fuel > 0) {
			fuel -= fabs(glm::dot(camera->forward * deltaTime, glm::vec3(1)));
			player2 -= camera->forward * deltaTime;
			player2.y = calculate_oy(player2) + 0.085f;
			lightPosition3 = glm::vec3(0, 3.5f, 0) + player2;
		}
	}

	if (window->KeyHold(GLFW_KEY_D)) {
		// TODO : translate the camera to the right
		camera->TranslateRight(cameraSpeed * deltaTime);
		if (current_player == 0 && fuel > 0) {
			fuel -= fabs(glm::dot(camera->right * deltaTime, glm::vec3(1)));
			player1 += camera->right * deltaTime;
			player1.y = calculate_oy(player1) + 0.085f;
			lightPosition2 = glm::vec3(0, 3.5f, 0) + player1;
		}
		if (current_player == 2 && fuel > 0) {
			fuel -= fabs(glm::dot(camera->right * deltaTime, glm::vec3(1)));
			player2 += camera->right * deltaTime;
			player2.y = calculate_oy(player2) + 0.085f;
			lightPosition3 = glm::vec3(0, 3.5f, 0) + player2;
		}
	}

	if (window->KeyHold(GLFW_KEY_Q)) {
		// TODO : translate the camera down
		camera->TranslateUpword(-cameraSpeed * deltaTime);
	}

	if (window->KeyHold(GLFW_KEY_E)) {
		// TODO : translate the camera up
		camera->TranslateUpword(cameraSpeed * deltaTime);
	}

}

void Tema3::OnKeyPress(int key, int mods)
{
	// add key press event

	if (key == GLFW_KEY_SPACE)
	{
		ok = 0;
		fuel = 1.f;
		if (current_player == 0 || current_player == 2) {
			projectile_position = current_player == 0 ? player1 : player2;
			current_player = (current_player + 1) % 4;
			glm::vec3 direction = glm::vec3(camera->forward.x, 0, camera->forward.z);
			speed_ox = power * direction.x;
			speed_oy = 1.f + 0.8f * (power-1.5f)/2.f;
			speed_oz = power * direction.z;
			if(!free_mode)
				camera->Set(camera->position - camera->forward + 0.5f*camera->up, projectile_position, camera->up);
				camera->distanceToTarget = glm::distance(camera->position, projectile_position);
			
		}
		else {
			current_player = (current_player + 1) % 4;
		}

	}

	if (key == GLFW_KEY_P) {
		player1 = glm::vec3(-0.6f, 0, -5.f);
		player1.y = calculate_oy(player1) + 0.085f;
		lightPosition2 = glm::vec3(0, 3.5f, 0) + player1;
		angle_player1 = 0;

		player2 = glm::vec3(0.74f, 0, -0.83f);
		player2.y = calculate_oy(player2) + 0.085f;
		lightPosition3 = glm::vec3(0, 3.5f, 0) + player2;
		angle_player2 = M_PI;

	}
	if (key == GLFW_KEY_C) {
		free_mode = !free_mode;
	}
}

void Tema3::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	
	float sensivityOX = 0.0035f;
	float sensivityOY = 0.002f;
	if (free_mode && (current_player == 1 || current_player == 3)) {
		if (window->GetSpecialKeyState() == 0) {
			renderCameraTarget = false;
			camera->RotateFirstPerson_OX(-deltaY * sensivityOY);
			camera->RotateFirstPerson_OY(-deltaX * sensivityOX);
		}
	}
	else {

		renderCameraTarget = true;
		camera->RotateThirdPerson_OX(deltaY * sensivityOY);
		camera->RotateThirdPerson_OY(deltaX * sensivityOX);
		if (current_player == 0) {
			angle_player1 += deltaX * sensivityOX;
			ox_angle_player1 += deltaY * sensivityOY;
		}
		if (current_player == 2) {
			angle_player2 += deltaX * sensivityOX;
			ox_angle_player2 += deltaY * sensivityOY;
		}
	}
	

	
}

void Tema3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema3::OnWindowResize(int width, int height)
{
}


