#include "Tema1.h"
#include "Transform2D.h"
#include "Object2D.h"
#include "Colision.h"
#include <vector>
#include <iostream>
#include <chrono>
#include <time.h>
#include <Core/Engine.h>


using namespace std;



Tema1::Tema1()
{

}

Tema1::~Tema1()
{
}

void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glm::vec3 corner = glm::vec3(0, 0, 0);
	float squareSide = 1;

	game_over = false;
	srand(time(0));

	score = 0;
	
	time_of_day = 20.f;
	next_change = time_of_day - 1;
	show_bb = false;

	cout << "Welcome to Flappy Bird" << endl;
	cout << "Press G to activate gangster mode" << endl;
	cout << "Press R to restart game"<<endl;
	
	pillar_manager = new PillarManager();
	bird = new Bird();

	Mesh* sky_square = Object2D::CreateSquare("sky_square", glm::vec3(0, 0, 0), squareSide, glm::vec3(0.2f, 0.8f, 1), true);
	AddMeshToList(sky_square);

	Mesh* ground_square = Object2D::CreateSquare("ground_square", glm::vec3(0, 0, 0.5f), squareSide, glm::vec3(1, 0.7f, 0.3f), true);
	AddMeshToList(ground_square);

	Mesh* yellow_circle = Object2D::CreateCircle("yellow_circle", glm::vec3(0, 0, 0), 1, glm::vec3(1, 0.82f, 0));
	AddMeshToList(yellow_circle);

	yellow_circle = Object2D::CreateCircle("moon_circle", glm::vec3(0, 0, 0), 1, glm::vec3(0.95f, 0.94f, 0.79f));
	AddMeshToList(yellow_circle);

	Mesh* white_circle = Object2D::CreateCircle("white_circle", glm::vec3(0, 0, 0), 1, glm::vec3(1, 1, 1));
	AddMeshToList(white_circle);

	Mesh* magenta_circle = Object2D::CreateCircle("magenta_circle", glm::vec3(0, 0, 0), 1, glm::vec3(1, 0, 1));
	AddMeshToList(magenta_circle);
	
	Mesh* red_circle = Object2D::CreateCircle("red_circle", glm::vec3(0, 0, 0), 1, glm::vec3(1,0,0));
	AddMeshToList(red_circle);

	Mesh* green_circle = Object2D::CreateCircle("green_circle", glm::vec3(0, 0, 0), 1, glm::vec3(0.3f, 0.73f, 0.09f));
	AddMeshToList(green_circle);

	Mesh* black_circle = Object2D::CreateCircle("black_circle", glm::vec3(0, 0, 0), 1, glm::vec3(0, 0, 0));
	AddMeshToList(black_circle);

	Mesh* black_square = Object2D::CreateSquare("black_square", glm::vec3(0, 0, 0), squareSide, glm::vec3(0, 0, 0), true);
	AddMeshToList(black_square);

	Mesh* orange_square = Object2D::CreateSquare("orange_square", glm::vec3(0, 0, 0), squareSide, glm::vec3(1, 0.4f, 0), true);
	AddMeshToList(orange_square);

	Mesh* green_square = Object2D::CreateSquare("green_square", corner, squareSide, glm::vec3(0.3f, 0.73f, 0.09f), true);
	AddMeshToList(green_square);

	Mesh* blue_square = Object2D::CreateSquare("blue_square", corner, squareSide, glm::vec3(0.06f, 0.12f, 0.42f), true);
	AddMeshToList(blue_square);

	blue_square = Object2D::CreateSquare("night_square", glm::vec3(0, 0, 0), squareSide, glm::vec3(0.075f, 0.094f, 0.384f), true);
	AddMeshToList(blue_square);

	Mesh* magenta_square = Object2D::CreateSquare("magenta_square", corner, squareSide, glm::vec3(1, 0, 1), true);
	AddMeshToList(magenta_square);

	Mesh* yellow_square = Object2D::CreateSquare("yellow_square", corner, squareSide, glm::vec3(1, 0.82f, 0), true);
	AddMeshToList(yellow_square);

	//vectori pentru alegerea random a culorii
	random_square.resize(5);
	random_square[0] = "green_square";
	random_square[1] = "orange_square";
	random_square[2] = "magenta_square";
	random_square[3] = "yellow_square";
	random_square[4] = "blue_square";
	random_circle.resize(5);
	random_circle[0] = "yellow_circle";
	random_circle[1] = "magenta_circle";
	random_circle[2] = "green_circle";
	random_circle[3] = "white_circle";
	random_circle[4] = "red_circle";

	cloud_color.resize(4, "white_circle");

}

void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}


// Aceasta functie randeaza orice obiect care implementeaza "interfata" Object definita in Object.h
void Tema1::RenderObject(Object* object, glm::ivec2 resolution, float deltaTimeSeconds) {
	std::vector<std::pair<std::string, glm::mat3>> output = object->update(resolution, deltaTimeSeconds);
	
	for (std::pair<std::string, glm::mat3>& shape : output) {
		RenderMesh2D(meshes[shape.first], shaders["VertexColor"], shape.second);
	}
	
}


void Tema1::Update(float deltaTimeSeconds)
{

	// afisaeaza bounding boxurile la apasarea tastei B pentru debug
	if (show_bb) {
		vector<glm::vec3> bb = pillar_manager->getBoundingBoxes();
		if (bb.size() > 3) {
			for (int i = 0; i < bb.size(); i += 1) {
				modelMatrix = glm::mat3(1);
				modelMatrix *= Transform2D::Translate(bb[i].x, bb[i].y) * Transform2D::Scale(20, 20) * Transform2D::Translate(-0.5f, -0.5f);
				RenderMesh2D(meshes["black_square"], shaders["VertexColor"], modelMatrix);
			}
		}

		bb = bird->getBoundingBoxes();

		for (int i = 0; i < 10; i++) {
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(bb[i].x, bb[i].y) * Transform2D::Scale(5, 5) * Transform2D::Translate(-0.5f, -0.5f);
			RenderMesh2D(meshes["black_square"], shaders["VertexColor"], modelMatrix);
		}
	}


	//
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);


	// Render bird
	RenderObject(bird, resolution, deltaTimeSeconds);

	//Render ground
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Scale((float)resolution.x, (float)resolution.y / 14.0f);

	modelMatrix2 = glm::mat3(1);
	modelMatrix2 *= Transform2D::Scale((float)resolution.x, (float)resolution.y / 14 * 1.1f);

	RenderMesh2D(meshes["ground_square"], shaders["VertexColor"], modelMatrix);
	RenderMesh2D(meshes["black_square"], shaders["VertexColor"], modelMatrix2);


	//Render pillars
	RenderObject(pillar_manager, resolution, deltaTimeSeconds);

	//Render sky
	draw_sky(resolution, deltaTimeSeconds);


	//Check for collison with pillars
	if (Colision::has_colided(bird->getBoundingBoxes(), pillar_manager->getBoundingBoxes())) {
		
		pillar_manager->stop();
		if(!game_over)
			cout << "GAME OVER" << endl << "Final score: " << score<<endl<<"Press R to restart"<<endl;
		game_over = true;
	}

	//Check for colision with ground
	vector<glm::vec3> ground(5);
	ground[0] = glm::vec3((float)resolution.x * 1.7f /5.0f,1,1);
	ground[1] = glm::vec3((float)resolution.x * 2.3f / 5.0f, 1, 1);
	ground[2] = glm::vec3((float)resolution.x * 2.3f / 5.0f, (float)resolution.y / 14.0f, 1);
	ground[3] = glm::vec3((float)resolution.x * 1.7f / 5.0f, (float)resolution.y / 14.0f, 1);
	ground[4] = glm::vec3((float)resolution.x * 2.0f / 5.0f , (float)resolution.y / 28.0f, 1);

	if (Colision::has_colided(bird->getBoundingBoxes(), ground)) {
		bird->stop();
		pillar_manager->stop();
		if(!game_over)
		cout << "GAME OVER" << endl << "Final score: " << score << endl << "Press R to restart" << endl;
		game_over = true;
	}


	// Print score
	int diff = pillar_manager->get_score(bird->get_position());
	score += diff;
	if(diff)
		cout << "Current score: " << score<<endl;

	
}

//Function that renders the sky
void Tema1::draw_sky(glm::ivec2 resolution, float deltaTimeSeconds) {
	
	//Time of day decreases from 20 to 0. From 20 to 10 it's day, and from 10 to 0 it's night
	float aux = time_of_day;
	time_of_day -= deltaTimeSeconds;

	if (time_of_day < next_change) {
		next_change = time_of_day - 0.3f;

		for (auto& color : star_color) {
			color = random_circle[rand() % 5];
		}

		if (gangster_mode) {
			for (auto& color : cloud_color) {
				color = random_circle[rand() % 5];
			}
		}

	}

	// If it's about to get night calculate calculate random star positions
	if (time_of_day <= 10.f && aux > 10.f) {
		stars.clear();
		star_color.clear();
		
		for (int i = 0; i < rand() % 50 + 35; i++) {
			int x = rand() % 1000;
			int y = rand() % 1000;
			int size = rand() % 5 + 2.f;

			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Scale(size, size);

			stars.push_back(make_pair(glm::vec2(x, y), modelMatrix));
			star_color.push_back(random_circle[rand() % 5]);

		}

	}
	// Reset time at 0
	if (time_of_day <= 0.f) {
		time_of_day = 20.f;
		next_change = time_of_day - 0.3f;
	}

	if (time_of_day > 10.f) {

		sky_color = "sky_square";
		//Render cloud
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate((float)resolution.x * 1.4f * (20.f - time_of_day) / 10.f - (float)resolution.x * 0.1f, (float)resolution.y * 2.f / 3.f) * Transform2D::Scale(40.f, 40.f);
		RenderMesh2D(meshes[cloud_color[0]], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate((float)resolution.x * 1.4f * (20.f - time_of_day) / 10.f - (float)resolution.x * 0.1f, (float)resolution.y * 2.f / 3.f) * Transform2D::Translate(-40.f, 0.f) * Transform2D::Scale(60.f, 60.f);
		RenderMesh2D(meshes[cloud_color[1]], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate((float)resolution.x * 1.4f * (20.f - time_of_day) / 10.f - (float)resolution.x * 0.1f, (float)resolution.y * 2.f / 3.f) * Transform2D::Translate(-80.f, 0.f) * Transform2D::Scale(60.f, 60.f);
		RenderMesh2D(meshes[cloud_color[2]], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate((float)resolution.x * 1.4f * (20.f - time_of_day) / 10.f - (float)resolution.x * 0.1f, (float)resolution.y * 2.f / 3.f) * Transform2D::Translate(-120.f, 0.f) * Transform2D::Scale(40.f, 40.f);
		RenderMesh2D(meshes[cloud_color[3]], shaders["VertexColor"], modelMatrix);


		//Render sun
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate((float)resolution.x * 3.f / 4.f, (float)resolution.y * 1.4f * (time_of_day - 10.f) / 10.f - (float)resolution.y * 0.1f) * Transform2D::Scale(100.f, 100.f);
		RenderMesh2D(meshes["yellow_circle"], shaders["VertexColor"], modelMatrix);
	}
	else {
		sky_color = "night_square";

		//Render moon
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate((float)resolution.x * 3.f / 4.f, (float)resolution.y * 1.3f * time_of_day / 10.f - (float)resolution.y * 0.1f) * Transform2D::Scale(50.f, 50.f);
		RenderMesh2D(meshes["moon_circle"], shaders["VertexColor"], modelMatrix);

		//Render stars
		for (int i = 0; i < stars.size(); i++) {
			modelMatrix = Transform2D::Translate((float)resolution.x / 1000.f * stars[i].first.x, (float)resolution.y / 1000.f  * stars[i].first.y) * stars[i].second;
			
			if(gangster_mode)
			RenderMesh2D(meshes[star_color[i]], shaders["VertexColor"], modelMatrix);
			else {
				RenderMesh2D(meshes["yellow_circle"], shaders["VertexColor"], modelMatrix);
			}

		}

	}

	//Render sky color
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Scale((float)resolution.x, (float)resolution.y);
	RenderMesh2D(meshes[sky_color], shaders["VertexColor"], modelMatrix);

}

void Tema1::FrameEnd()
{

}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	
}

void Tema1::OnKeyPress(int key, int mods)
{
	// On space
	if (!game_over && key == GLFW_KEY_SPACE)
	{

		bird->started = true;
		bird->speed = 90.0f;
		bird->boost = 10.0f;

		pillar_manager->started = true;
		
	}
	//Restarts game
	if (key == GLFW_KEY_R)
	{
		delete bird;
		delete pillar_manager;
		game_over = false;
		score = 0;
		bird = new Bird();
		pillar_manager = new PillarManager();
		gangster_mode = false;
		cloud_color[0] = "white_circle";
		cloud_color[1] = "white_circle";
		cloud_color[2] = "white_circle";
		cloud_color[3] = "white_circle";

	}

	// Toggle/Disable gangster mode
	if (key == GLFW_KEY_G)
	{
		gangster_mode = !gangster_mode;
		cloud_color[0] = "white_circle";
		cloud_color[1] = "white_circle";
		cloud_color[2] = "white_circle";
		cloud_color[3] = "white_circle";
		bird->gangster();
		pillar_manager->gangster();

	}

	//Show bounding boxes
	if (key == GLFW_KEY_B)
	{
		show_bb = !show_bb;
	}
}

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}
