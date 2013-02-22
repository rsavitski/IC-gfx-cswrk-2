#include "raycast.h"

// Globals:

// File names
char *_inputName       = NULL;
char *_outputNameRGB   = NULL;
char *_outputNameDepth = NULL;

// Image parameters.
int _width      = 100;
int _height     = 100;
float _depthMin = 0;
float _depthMax = 1;

// Render a color image of objects in a scene.
void renderRGBImage(SceneParser &, Image &);

// Render an image showing the depth of objects from the camera.
void renderDepthImage(SceneParser &, Image &);

int main(int argc, char** argv) {

  int i;
  // sample command lines:
  // raycast -input input.txt -size 100 100 -output output.ppm
  // raycast -input input.txt -size 100 100 -depth 5.5 8.8 output.ppm

  for (i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-input") == 0) {
      i++;assert (i < argc);
      _inputName = argv[i];
    } else if (strcmp(argv[i], "-size") == 0) {
      i++;assert (i < argc);
      _width = atoi(argv[i]);
      i++;assert (i < argc);
      _height = atoi(argv[i]);
    } else if (strcmp(argv[i], "-output") == 0) {
      i++;assert (i < argc);
      _outputNameRGB = argv[i];
    } else if (strcmp(argv[i], "-depth") == 0) {
      i++;assert (i < argc);
      _depthMin = atof(argv[i]);
      i++;assert (i < argc);
      _depthMax = atof(argv[i]);
      i++;assert (i < argc);
      _outputNameDepth = argv[i];
    } else {
      printf(
          "Error with command line argument %d: '%s'\n",
          i, argv[i]);
      assert(0);
    }
  }

  // Read in the scene description file, parsing the objects,
  // camera details, etc.
  SceneParser scene(_inputName);

  // Color and depth images.
  Image rgbImage(_width, _height);
  Image depthImage(_width, _height);

  // Do the rendering.
  renderRGBImage(scene, rgbImage);
  renderDepthImage(scene, depthImage);

  // Write results if necessary.
  if (_outputNameRGB != NULL) {
    rgbImage.SavePPM(_outputNameRGB);
  }

  if (_outputNameDepth != NULL){
    depthImage.SavePPM(_outputNameDepth);
  }

}

// Render a color image of objects in a scene.
void renderRGBImage(SceneParser &scene, Image &image) 
{
  // camera properties, object info and bg color
  Group *objs = scene.getGroup();
  Camera *camera = scene.getCamera();
  Vec3f background = scene.getBackgroundColor();

  int imgW = image.Width();
  int imgH = image.Height();

  // iterate over x-y pixel bins, cast rays and push results into an image
  for (int x=0; x < imgW; x++)
  {
    for (int y=0; y < imgH; y++)
    {
      // calculate pixel's normalised parameters
      float x_indx = ((float) x)/imgW;
      float y_indx = ((float) y)/imgH;

      Hit hit(std::numeric_limits<float>::infinity(), Vec3f(0,0,0));
      bool intersect = false;

      // spawn ray
      Ray ray = camera->generateRay(Vec2f(x_indx, y_indx));
  
      // trace
      intersect = objs->intersect(ray, hit);

      if (intersect)
      {
        image.SetPixel(x, y, hit.getColor());
      }
      else
      {
        // no collisions -> background color
        image.SetPixel(x, y, background);
      }
    }
  }
}

// Render an image showing the depth of objects from the camera.
void renderDepthImage(SceneParser &scene, Image &image) 
{
  // camera properties and object info
  Group *objs = scene.getGroup();
  Camera *camera = scene.getCamera();

  int imgW = image.Width();
  int imgH = image.Height();
  
  // iterate over x-y pixel bins, cast rays and push results into an image
  for (int x=0; x < imgW; x++)
  {
    for (int y=0; y < imgH; y++)
    {
      // calculate pixel's normalised parameters
      float x_indx = ((float) x)/imgW;
      float y_indx = ((float) y)/imgH;

      Hit hit(std::numeric_limits<float>::infinity(), Vec3f(0,0,0));
      bool intersect = false;

      // spawn ray
      Ray ray = camera->generateRay(Vec2f(x_indx, y_indx));
  
      // trace
      intersect = objs->intersect(ray, hit);

      if (intersect)
      {
        float t = hit.getT();
        float intensity = 0;

        if (t <= _depthMin)
        {
          intensity = 1; // full intensity for channel (-> white)
        }
        else if (t >= _depthMax)
        {
          intensity = 0; // (-> black)
        }
        else
        {
          intensity = (_depthMax - t)/(_depthMax - _depthMin); // ratio (distance to far plane)/(depth range of image)
        }

        image.SetPixel(x, y, Vec3f(intensity,intensity,intensity));
      }
      else
      {
        // no collisions -> black
        image.SetPixel(x, y, Vec3f(0,0,0));
      }
    }
  }
}

