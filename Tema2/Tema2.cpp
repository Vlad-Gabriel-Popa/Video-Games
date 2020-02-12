#include "Tema2.h"
#include "CreateShape.h"
#include <time.h>
#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

Tema2::Tema2()
{
}

Tema2::~Tema2()
{
}

void Tema2::Init()
{

	srand(time(NULL));

	camera = new Camera::Camera();
	camera->Set(glm::vec3(0, 190.f, 50.f), glm::vec3(0, 190.f, 0), glm::vec3(0, 1.f, 0));
	is_first_person = false;
	camera_speed = 0;
	std::cout << camera->forward << " " << camera->right << " " << camera->up << std::endl;


	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("plane_body");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "plane_body.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("nose");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "nose.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("game_over");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "game_over.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* cyilinder = Object3D::create_cylinder();
		meshes[cyilinder->GetMeshID()] = cyilinder;
		angle = 0;
		sea_speed =  0.2f;

		Mesh* pyramid_base = Object3D::pyramid_base("base");
		meshes[pyramid_base->GetMeshID()] = pyramid_base;

		{
			Mesh* mesh = new Mesh("cube");
			mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
			meshes[mesh->GetMeshID()] = mesh;
		}

		{
			Mesh* mesh = new Mesh("window");
			mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "window.obj");
			meshes[mesh->GetMeshID()] = mesh;
		}

		Mesh* cube_up = Object3D::cube_up("cube_up");
		meshes[cube_up->GetMeshID()] = cube_up;

		Mesh* gas_tank = Object3D::gas_tank("gas_tank");
		meshes[gas_tank->GetMeshID()] = gas_tank;

		Mesh* star = Object3D::star("star");
		meshes[star->GetMeshID()] = star;

		plane = new Plane(window->GetCursorPosition().y, window->GetResolution().y);
		mouseY = 0;

		fuel = new Fuel(0, 0, 200, 10);

		obstacle = new Obstacle(0, 200, 10);

		cloud = new Cloud(-30, 240, 10);
		
		manager = new Manager(192, 230, -10, 30);

		game_over_time = 0;
	}

	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader *shader = new Shader("MainShader");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader2.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader2.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shader = new Shader("SeaShader");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShaderSea.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShaderSea.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shader = new Shader("UIShader");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shader = new Shader("NoLight");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShaderNoLight.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShaderNoLight.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	//Light & material properties
	{
		lightPosition = glm::vec3(40,400,66);
		materialShininess = 30;
		materialKa = 0.75;
		materialKd = 0.5;
		materialKs = 0.5;
	}

	
	fov = 60.0f;
	width = 1.5;

	game_over = false;
	projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, 0.1f, 1000.0f);

	sky_colors.push_back(glm::vec3(145.f / 255.f, 240.f / 255.f, 242.f / 255.f));
	sky_colors.push_back(glm::vec3(255.f / 255.f, 219.f / 255.f, 100.f / 255.f));
	sky_colors.push_back(glm::vec3(1.f / 255.f, 79.f / 255.f, 148.f / 255.f));
	sky_colors.push_back(glm::vec3(0, 0, 40.f / 255.f));
	sky_colors.push_back(glm::vec3(1.f / 255.f, 79.f / 255.f, 148.f / 255.f));
	sky_colors.push_back(glm::vec3(255.f / 255.f, 219.f / 255.f, 100.f / 255.f));

	for (int i = 0; i < periods_of_time; i++) {
		steps.push_back((sky_colors[(i + 1) % periods_of_time] - sky_colors[i]) / time_period);
	}

	ka_step = (0.75f - 0.05f) / (2.f * time_period);
	kd_step = (0.5f - 0.15f) / (2.f * time_period);
	oy_light_step = (750.f - 400.f) / (2.f*time_period);

	{
		spotPosition = glm::vec3(-27, plane->getOy(), 0);
		lightDirection = glm::normalize(glm::vec3(1, 0, 0));
		spot_angle = 30.f;
	}
}

void Tema2::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glm::vec3 color = sky_colors[current_period] + current_time * steps[current_period];
	glClearColor(color.x, color.y, color.z, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);	
}

void Tema2::Update(float deltaTimeSeconds)
{
	if (game_over) {
		sea_speed -= 0.02f * deltaTimeSeconds;
		if (sea_speed < 0) {
			sea_speed = 0;
		}
	}
	
	if (spot_active && counter < 13) {
		counter += deltaTimeSeconds;
		
		if (game_over && counter < 7.f) {
			counter = 7.f;
		}

		if (counter >= 7.f) {
			current_time += deltaTimeSeconds;
			lightPosition.y -= oy_light_step * deltaTimeSeconds;
			materialKa += ka_step * deltaTimeSeconds;
			materialKd += kd_step * deltaTimeSeconds;
		}
	}
	else {

		current_time += deltaTimeSeconds;
		if (current_period == 3 || current_time > time_period) {
			current_time = 0;
			current_period = (current_period + 1) % 6;
		}
		if (current_period == 0 || current_period == 1 || current_period == 4 || current_period == 5) {
			spot_active = 0;
		}
		else {
			spot_active = 1;
		}
		if (current_period == 3) {
			spot_active = 1;
			counter = 0;
		}

		if (current_period == 0 || current_period == 5) {
			lightPosition.y = 400;
			materialKa = 0.75f;
			materialKd = 0.5f;
		}
		else if (current_period == 1 || current_period == 2) {
			lightPosition.y += oy_light_step * deltaTimeSeconds;
			materialKa -= ka_step * deltaTimeSeconds;
			materialKd -= kd_step * deltaTimeSeconds;
		}
		else if(current_period == 4) {
			lightPosition.y -= oy_light_step * deltaTimeSeconds;
			materialKa += ka_step * deltaTimeSeconds;
			materialKd += kd_step * deltaTimeSeconds;
		}

	}

	if (is_third_person) {
		spotPosition = glm::vec3(-22, plane->getOy(), plane->oz_position);
	}
	else {
		spotPosition = glm::vec3(-22, plane->getOy(), 0);
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::scale(modelMatrix, glm::vec3(180, 180, 400));
		modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(0, 0, 1));
		RenderSimpleMesh(meshes["cylinder"], shaders["SeaShader"], modelMatrix, glm::vec3(0.26f, 0.64f, 0.87f));
		
		angle += deltaTimeSeconds * sea_speed;
	}

	float prev_oy = plane->getOy();
	RenderObject(plane->update(deltaTimeSeconds, mouseY, mouseX, window->GetResolution().y, window->GetResolution().x));

	
	RenderObject(manager->update(deltaTimeSeconds));

	if (game_over) {
		game_over_time += deltaTimeSeconds;
		if (game_over_time > 3.7f) {
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, camera->position + camera->forward * 150.f);
			if (is_first_person || is_third_person) {
				modelMatrix = glm::rotate(modelMatrix, -(float)M_PI / 2, glm::vec3(0, 1, 0));
			}
			modelMatrix = glm::rotate(modelMatrix, (float)M_PI / 2, glm::vec3(1, 0, 0));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(20.f));
			RenderSimpleMesh(meshes["game_over"], shaders["MainShader"], modelMatrix, glm::vec3(1, 0.15f, 0.15f));
		}
	}

	if (!game_over && (plane->fuel <= 0 || plane->lives <= 0)) {
		game_over = true;
		plane->crash();
		manager->set_game_over();
	}
	if (!game_over) {
		draw_fuel();
		draw_health();

		int collision_result = manager->detect_collision(plane->getBoundingBoxes(), plane->colliding);
		if (collision_result == -1) {
			plane->collide(manager->get_collided());
		}
		else if (collision_result == 1) {
			plane->fuel_up();
		}
	}


	if (!is_first_person) {
		float plane_oy = plane->getOy();
		int direction = (plane_oy > camera->position.y) ? 1 : -1;

		if (abs(plane_oy - 250.f) < 4) {
			plane_oy = 250.f;
		}
		if (plane_oy - 190.f < 4) {
			plane_oy = 190.f;
		}
		if (camera->position.y > 250.f) {
			camera->position.y = 250.f;
			camera_speed = 0;
		}
		else if (camera->position.y < 190.f) {
			camera->position.y = 190.f;
		}
		else if (abs(plane_oy - camera->position.y) < 10 && !is_third_person ) {
			camera_speed = 0;

		}
		else {
			int k = 1;
			if (is_third_person) {
				k = 2;
			}
			camera->position.y += k* (plane_oy - camera->position.y) * deltaTimeSeconds;
		}

	}
	else {
		camera->position.y = plane->getOy() ;
		if (camera->position.y < 190.f) {
			camera->position.y = 190.f;
		}
	}

	/*
	if(camera->position.y + camera_speed * deltaTimeSeconds)
	camera->position.y += camera_speed * deltaTimeSeconds;
	if(camera->position.y)
	*/

}

void Tema2::draw_fuel() {

	float size = plane->fuel/100.f * 6;
	glm::vec3 position = camera->position + camera->forward * 15.f + camera->right * 10.f + camera->up * 7.f;

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, position);
		if (is_first_person || is_third_person) {
			modelMatrix = glm::rotate(modelMatrix, -(float)M_PI / 2, glm::vec3(0, 1, 0));
		}
		modelMatrix = glm::scale(modelMatrix, glm::vec3(6,1.5,0.3));
		RenderSimpleMesh(meshes["cube"], shaders["UIShader"], modelMatrix, glm::vec3(0, 0, 0));
	}
	
	if (!is_first_person) {
		position.z += 0.001f;
		position.y -= 0.0001f;
	}
	else {
		position.z += 0.001f;
		position.x += 0.01f;
		position.y -= 0.0001f;
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, position);
		if (is_first_person || is_third_person) {
			modelMatrix = glm::rotate(modelMatrix, -(float)M_PI / 2, glm::vec3(0, 1, 0));	
		}
		modelMatrix = glm::translate(modelMatrix, -glm::vec3((6.f - size) / 2.f, 0, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(size+0.01f, 1.51, 0.35));
		RenderSimpleMesh(meshes["cube"], shaders["UIShader"], modelMatrix, glm::vec3(1, 0.15f, 0.15f));
	}

}

void Tema2::draw_health() {

	for (int i = 0; i < plane->lives; i++) {
		glm::vec3 position = camera->position + camera->forward * 15.f - camera->right * (13.f - 3 * i) + camera->up * 7.f;
		RenderUI(plane->draw_here(position, glm::vec3(0.15f, 0.15f, 0.15f), is_first_person || is_third_person));

	}
}



void Tema2::RenderObject(std::vector<std::tuple<std::vector<std::string>, glm::vec3, glm::mat4>> object) {

	for (auto& component : object) {
		vector<string> data;
		glm::vec3 color;
		glm::mat4 modelMatrix;
		std::tie(data, color, modelMatrix) = component;

		RenderSimpleMesh(meshes[data[0]], shaders[data[1]], modelMatrix, color);
	}
}

void Tema2::RenderUI(std::vector<std::tuple<std::vector<std::string>, glm::vec3, glm::mat4>> object) {

	for (auto& component : object) {
		vector<string> data;
		glm::vec3 color;
		glm::mat4 modelMatrix;
		std::tie(data, color, modelMatrix) = component;

		RenderSimpleMesh(meshes[data[0]], shaders["UIShader"], modelMatrix, color);
	}
}

void Tema2::FrameEnd()
{
}

void Tema2::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, const glm::vec3 &color)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// Set shader uniforms for light & material properties
	// TODO: Set light position uniform
	glm::vec3 pos = lightPosition;
	if (meshes[mesh->GetMeshID()] == meshes["cylinder"]) {
		pos = glm::vec3(40, lightPosition.y + 50, 0);
	}
	if (shaders[shader->GetName()] == shaders["UIShader"]) {
		pos = camera->position;
	}
	GLint loc_light_position = glGetUniformLocation(shader->program, "light_position");
	glUniform3fv(loc_light_position, 1, glm::value_ptr(pos));

	// TODO: Set eye position (camera position) uniform
	glm::vec3 eyePosition = camera->position;
	GLint loc_eye_position = glGetUniformLocation(shader->program, "eye_position");
	glUniform3fv(loc_eye_position, 1, glm::value_ptr(eyePosition));
	// TODO: Set material property uniforms (shininess, kd, ks, object color) 


	GLint loc_material_shininess = glGetUniformLocation(shader->program, "material_shininess");
	glUniform1ui(loc_material_shininess, materialShininess);

	GLint loc_material_ka = glGetUniformLocation(shader->program, "material_ka");
	glUniform1f(loc_material_ka, materialKa);

	GLint loc_material_kd = glGetUniformLocation(shader->program, "material_kd");
	glUniform1f(loc_material_kd, materialKd);

	GLint loc_material_ks = glGetUniformLocation(shader->program, "material_ks");
	glUniform1f(loc_material_ks, materialKs);

	GLint loc_object_color = glGetUniformLocation(shader->program, "object_color");
	glUniform3fv(loc_object_color,1, glm::value_ptr(color));

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

	float time = Engine::GetElapsedTime();
	int location = glGetUniformLocation(shader->GetProgramID(), "Time");
	glUniform1f(location, time);

	int light_pos = glGetUniformLocation(shader->program, "spot_position");
	glUniform3f(light_pos, spotPosition.x, spotPosition.y, spotPosition.z);

	int light_direction = glGetUniformLocation(shader->program, "light_direction");
	glUniform3f(light_direction, lightDirection.x, lightDirection.y, lightDirection.z);

	int angle_pos = glGetUniformLocation(shader->program, "angle");
	glUniform1f(angle_pos, spot_angle);

	int spot_active_pos = glGetUniformLocation(shader->program, "spot_active");
	glUniform1i(spot_active_pos, spot_active);

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}




// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Tema2::OnInputUpdate(float deltaTime, int mods)
{

}

void Tema2::OnKeyPress(int key, int mods)
{
	// add key press event

	if (key == GLFW_KEY_C) {
		bool aux = is_first_person;
		is_first_person = !is_first_person && !is_third_person;
		is_third_person = aux;

		if (is_first_person) {
			camera->Set(glm::vec3(-12, plane->getOy(), 0), glm::vec3(0, plane->getOy(), 0), glm::vec3(0, 1.f, 0));
			plane->first_person();
			manager->first_person = true;
			manager->third_person = false;
		}
		else if (is_third_person){
			camera->Set(glm::vec3(-42, plane->getOy(), 0), glm::vec3(0, plane->getOy(), 0), glm::vec3(0, 1.f, 0));
			plane->third_person();
			manager->first_person = false;
			manager->third_person = true;
		}
		else {
			camera->Set(glm::vec3(0, 190.f, 50.f), glm::vec3(0, 190.f, 0), glm::vec3(0, 1.f, 0));
			plane->normal_mode();
			manager->first_person = false;
			manager->third_person = false;
		}
	}
}

void Tema2::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event

	float sensivityOX = 0.001f;
	float sensivityOY = 0.001f;

	this->mouseY = mouseY;
	this->deltaY = deltaY;
	this->mouseX = mouseX;
	/*if (window->GetSpecialKeyState() == 0) {
		renderCameraTarget = true;
		// TODO : rotate the camera in Third-person mode around OX and OY using deltaX and deltaY
		// use the sensitivity variables for setting up the rotation speed
		
		camera->TranslateUpword(-deltaY * sensivityOY*100);
		if (camera->position.y < 75.f) {
			camera->position.y = 75.f;
		}

		if (camera->position.y > 120.f) {
			camera->position.y = 120.f;
		}


	}
	if (window->GetSpecialKeyState() && GLFW_MOD_CONTROL) {
		renderCameraTarget = true;
		// TODO : rotate the camera in Third-person mode around OX and OY using deltaX and deltaY
		// use the sensitivity variables for setting up the rotation speed
		camera->RotateThirdPerson_OX(deltaY * sensivityOY);
		camera->RotateThirdPerson_OY(deltaX * sensivityOX);
	}
	*/
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
}

