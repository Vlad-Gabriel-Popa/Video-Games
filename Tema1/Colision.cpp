#include "Colision.h"
#include <vector>
#include <iostream>
#include <Core/Engine.h>

/*
	This file implements the 2D GJK algorithm for collision detection
	It currently works only for rectangles
*/


glm::vec2 direction;
std::vector<glm::vec2> shapeA(5), shapeB(5);
enum class Status { StillEvolving, Intersection, NoIntersection };

glm::vec2 support(std::vector<glm::vec2> square, glm::vec2 dir){
	float max_distance = -999999999.0f;
	glm::vec2 max_vertex;

	for (int i = 0; i < 4; i++) {
		float distance = glm::dot(square[i], dir);
		if (distance > max_distance) {
			max_distance = distance;
			max_vertex = square[i];
		}
	}

	return max_vertex;
}

bool addSupport(glm::vec2 direction, std::vector<glm::vec2>& vertices) {
	glm::vec2 new_vertex = support(shapeA, direction) - support(shapeB, (-1.0f) * direction);
	vertices.push_back(new_vertex);
	return glm::dot(direction, new_vertex) > 0;
}

glm::vec2 triple_product(glm::vec2 aa, glm::vec2 bb, glm::vec2 cc) {
	glm::vec3 A(aa.x, aa.y, 0);
	glm::vec3 B(bb.x, bb.y, 0);
	glm::vec3 C(cc.x, cc.y, 0);

	glm::vec3 first = glm::cross(A, B);
	glm::vec3 second = glm::cross(first, C);

	return glm::vec2(second.x, second.y);
}


Status evolveSimplex(std::vector<glm::vec2>& vertices) {
	switch (vertices.size()) {
	case 0: {
		direction = shapeB[4] - shapeA[4];
	}
		break;
	case 1: {

		direction *= (-1.0f);

		break;
	}
	case 2: {
		glm::vec2 b, c, cb, c0;
		b = vertices[1];
		c = vertices[0];
		cb = b - c;
		c0 = c * (-1.0f);
		direction = triple_product(cb, c0, cb);
	}
		break;
	case 3: {
		glm::vec2 a, b, c, a0, ab, ac, abPrep, acPrep;

		a = vertices[2];
		b = vertices[1];
		c = vertices[0];

		
		
		a0 = a * (-1.0f);
		ab = b - a;
		ac = c - a;

		abPrep = triple_product(ac, ab, ab);
		acPrep = triple_product(ab, ac, ac);

		if (glm::dot(abPrep, a0) > 0) {
			
			vertices.erase(vertices.begin());
			direction = abPrep;
		}
		else if (glm::dot(acPrep, a0) > 0) {
			vertices.erase(vertices.begin() + 1);
			direction = acPrep;
		}
		else {
			return Status::Intersection;
		}
	}
		break;
	}
	if (addSupport(direction, vertices)) {
		return Status::StillEvolving;
	}
	else {
		return Status::NoIntersection;
	}

}

bool test() {
	std::vector<glm::vec2> vertices;
	Status status = Status::StillEvolving;
	while (status == Status::StillEvolving) {
		status = evolveSimplex(vertices);
	}
	return status == Status::Intersection;
}

//Function that calculates collision between rectangle bouding boxes using the 2D GJK algorithm
bool Colision::has_colided(std::vector<glm::vec3> source, std::vector<glm::vec3> target) {
		for (int i = 0; i < source.size(); i+= 5) {
		for (int j = 0; j < target.size(); j += 5) {
			shapeA[0] = glm::vec2(source[i].x, source[i].y);
			shapeA[1] = glm::vec2(source[i+1].x, source[i+1].y);
			shapeA[2] = glm::vec2(source[i+2].x, source[i+2].y);
			shapeA[3] = glm::vec2(source[i+3].x, source[i+3].y);
			shapeA[4] = glm::vec2(source[i+4].x, source[i+4].y);

			shapeB[0] = glm::vec2(target[j].x, target[j].y);
			shapeB[1] = glm::vec2(target[j+1].x, target[j+1].y);
			shapeB[2] = glm::vec2(target[j+2].x, target[j+2].y);
			shapeB[3] = glm::vec2(target[j+3].x, target[j+3].y);
			shapeB[4] = glm::vec2(target[j+4].x, target[j+4].y);

			if (test()) {
				return true;
			}
		}
	}
	return false;
}