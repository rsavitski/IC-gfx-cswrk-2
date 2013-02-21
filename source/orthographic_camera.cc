#include "raycast.h"

// Constructor with parameters.
OrthographicCamera::OrthographicCamera(Vec3f centre, Vec3f direction, Vec3f up, float size)
: centre(centre), direction(direction), size(size) 
{
	this->direction.Normalize();


}


Ray OrthographicCamera::generateRay(Vec2f point)
{
	// generate ray with camera_x[0->1] and camera_y[0->1]
	Vec3f origin(centre);
	origin += horizontal*((point.x()-0.5)*size);
	origin += up*((point.y()-0.5)*size);

	return Ray(direction, origin);
}
