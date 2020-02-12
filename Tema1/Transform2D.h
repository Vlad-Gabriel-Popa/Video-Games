#pragma once

#include <include/glm.h>

namespace Transform2D
{
	// Translate matrix
	glm::mat3 Translate(float translateX, float translateY);

	// Scale matrix
	glm::mat3 Scale(float scaleX, float scaleY);

	// Rotate matrix
	glm::mat3 Rotate(float radians);
}
