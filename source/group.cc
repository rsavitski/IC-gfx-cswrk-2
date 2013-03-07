#include "raycast.h"

// Constructor for a group of n objects.
Group::Group(int n) 
{
  this->_object = new Object3D*[n];
  for(int i = 0; i < n; ++i) 
  {
    this->_object[i] = NULL;
  }
  this->_count  = n;
}

// Destructor.
Group::~Group() 
{
  if (this->_object == NULL) 
  {
    return;
  }

  for (int i = 0; i < this->_count; i++) 
  {
    if(this->_object[i] != NULL) 
    {
      delete this->_object[i];
    }
  }

  delete[] this->_object;
}

// Insert an object into the array.
void Group::addObject(int index, Object3D *obj) 
{
  _object[index] = obj;
}


bool Group::intersect(const Ray &r, Hit &h)
{
  bool foundBetterIntersect = false;

  // loop over all objects in the group and see if there is a better intersection
  // better -> closer to camera and positive
  for (int i=0; i<_count; i++)
  {
    if ((*_object[i]).intersect(r, h) == true)
    {
      foundBetterIntersect = true;
    }
  }
  return foundBetterIntersect;
}