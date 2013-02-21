#include "raycast.h"

// Constructor with parameters.
OrthographicCamera::OrthographicCamera(Vec3f centre, Vec3f direction, Vec3f up, float size)
: centre(centre), direction(direction), size(size) 
{
	this->direction.Normalize();

	
}


Ray OrthographicCamera::generateRay(Vec2f point)
{
	
}
