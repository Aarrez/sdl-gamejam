#ifndef BOIDMANAGER_H
#define BOIDMANAGER_H

#include <SDL3/SDL.h>
#include <vector>
#include <utility>				\

class SDL_Rect;
class BoidManager {
 public:
   void InitBoids(SDL_Rect fieldRect, int boidCount = 100);
   void MoveBoids();

private:
  SDL_Rect fieldRect;
  std::vector<class Boid> boids;
  std::pair<float, float> Separate(class Boid& boid, float distance, float power);
  std::pair<float, float> Align(class Boid& boid, float distance, float power);
  std::pair<float, float> Cohere(class Boid& boid, float distance, float power);
  float GetDistance(const class Boid& boid1, const class Boid& boid2);
};

#endif
