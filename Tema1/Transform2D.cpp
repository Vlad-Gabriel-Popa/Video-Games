#include "Transform2D.h"
#include <include/glm.h>

	// Translate matrix
	glm::mat3 Transform2D::Translate(float translateX, float translateY)
	{
		// TODO implement translate matrix
		return glm::transpose(
			glm::mat3(1, 0, translateX,
				0, 1, translateY,
				0, 0, 1)
		);
	}

	// Scale matrix
	glm::mat3 Transform2D::Scale(float scaleX, float scaleY)
	{
		// TODO implement scale matrix
		return glm::transpose(
			glm::mat3(scaleX, 0   , 0,
				         0 ,scaleY, 0,
				         0 ,  0   , 1)
		);
	}

	// Rotate matrix
	glm::mat3 Transform2D::Rotate(float radians)
	{
		// TODO implement rotate matrix
		return glm::transpose(
			glm::mat3(cos(radians), -sin(radians), 0,
				      sin(radians),  cos(radians), 0,
				               0, 0, 1)
		);
	}
