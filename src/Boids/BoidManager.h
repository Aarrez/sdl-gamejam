#ifndef BOIDMANAGER_H
#define BOIDMANAGER_H

#include <SDL3/SDL.h>
#include <vector>

class SDL_Rect;
class BoidManager {
 public:
   void InitBoids(SDL_Rect fieldRect, int boidCount = 100);
   void MoveBoids();

private:
  SDL_Rect fieldRect;
  std::vector<class Boid> boids;
  void Separate(class boid&, float distance, float power);
  void Align(class boid&, float distance, float power);
  void Cohere(class boid &, float distance, float power);
};

#endif
