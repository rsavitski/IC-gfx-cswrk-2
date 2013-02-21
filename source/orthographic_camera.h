// Orthographic camera class.

#ifndef ORTHOGRAPHIC_CAMERA_H_
#define ORTHOGRAPHIC_CAMERA_H_

#include "raycast.h"

class OrthographicCamera : public Camera
{
public:
  // Constructor.
  OrthographicCamera(Vec3f centre, Vec3f direction, Vec3f up, float size);

  // Concrete implementation of pure virtual function in the
  // parent class.
  virtual Ray generateRay(Vec2f point);

private:
	float size;
	Vec3f centre, direction, up, horizontal;
};

#endif /* ORTHOGRAPHIC_CAMERA_H_ */