#include "raycast.h"

// Constructor with parameters.
OrthographicCamera::OrthographicCamera(Vec3f centre, Vec3f direction, Vec3f up, float size)
: size(size), centre(centre), direction(direction)  
{
	//cout << "provided up: " << up << endl;
	//cout << "provided dir: " << direction << endl;
	
	// raw up vector, might need to be normalised and orthogonalised
	this->up = up;

	// construct horizontal vector, in xy plane of camera
	Vec3f::Cross3(this->horizontal, this->direction, this->up);

	// orthogonalise up vector if needed
	float dotProd = this->direction.Dot3(up);
	if (!dotProd) // up vector already orthogonal to direction
	{
		cout << "Already orthogonal up vector case" << endl;

		Vec3f::Cross3(this->horizontal, this->direction, this->up);
	}
	else
	{
		// reconstruct proper up vector (orthogonal to direction and horizontal)
		Vec3f::Cross3(this->up, this->horizontal, this->direction);
	}

	// normalise vectors
	this->direction.Normalize();
	this->horizontal.Normalize();
	this->up.Normalize();

	//cout << this->up << endl;
}


Ray OrthographicCamera::generateRay(Vec2f point)
{
	// generate ray with camera_x[0->1] and camera_y[0->1]
	Vec3f origin(centre);
	origin += horizontal*((point.x()-0.5)*size);
	origin += up*((point.y()-0.5)*size);

	return Ray(direction, origin);
}
