#include "raycast.h"

Sphere::Sphere() 
: Object3D(Vec3f()), centre(Vec3f()), radius(1) 
{}


Sphere::Sphere(Vec3f centre, float radius, Vec3f color) 
: Object3D(color), centre(centre), radius(radius) 
{}


bool Sphere::intersect(const Ray &r, Hit &h)
{
	// intersect ray and sphere (solve below for t)
	// returns true iff a smaller positive intersection to that stored is found (not the same as the provided spec)

	// ray.origin = p0
	// ray.direction = d
	// this->centre = pc
	// this->radius = rs

	// at^2 + bt + c = 0

	// a = d.d
	// b = 2d.(p0-pc)
	// c = (p0-pc).(p0-pc) - rs^2

	Vec3f p0 = r.getOrigin();
	Vec3f d = r.getDirection();
	Vec3f pc = this->centre;
	float rs = this->radius;

	//float t1 = std::numeric_limits<float>::infinity();
	//float t2 = std::numeric_limits<float>::infinity();

	float a = d.Dot3(d);
	float b = (d*2).Dot3(p0-pc);
	float c = (p0-pc).Dot3(p0-pc) - rs*rs;

	float det = b*b-4*a*c;

	if (det < 0)		// no intersections
	{
		return false;
	}
	else if (det == 0)	// tangental intersection
	{
		float t = -b/(2*a);

		if (t >= 0 && t < h.getT()) // if the intersection is +ve and at a smaller 
		{
			h.set(t, this->_color);
			return true;
		}

		return false; // do not count negative/worse intersects
		
	}
	else 	// det > 0; double intersection
	{
		float t1 = (-b+sqrt(det))/(2*a);
		float t2 = (-b-sqrt(det))/(2*a);

		float t = -1;

		// if else block to find smallest positive intersection
		if (t1 >= 0 && t2 >= 0)
		{
			t = (t1 < t2) ? t1 : t2;
		}
		else if (t1 >= 0 && t2 < 0)
		{
			t = t1;
		}
		else if (t1 < 0 && t2 >= 0)
		{
			t = t2;
		}
		else if (t1 < 0 && t2 < 0)
		{
			// keep t at default -ve
		}

		// update if better and +ve
		if (t > 0 && t < h.getT()) 
		{
			h.set(t, this->_color);
			return true;
		}

		return false; // do not count negative/worse intersects
	}
}