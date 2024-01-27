#ifndef BOIDMANAGER_H
#define BOIDMANAGER_H

#include <SDL3/SDL.h>
#include <vector>
#include <utility>				

class SDL_Rect;
class BoidManager {
 public:
   void InitBoids(SDL_Rect fieldRect, int boidCount = 100);
   void MoveBoids();

  std::vector<class Boid> boids; // Move to private?
private:
  SDL_Rect fieldRect;
  std::pair<float, float> Separate(class Boid& boid, float distance, float power);
  std::pair<float, float> Align(class Boid& boid, float distance, float power);
  std::pair<float, float> Cohere(class Boid& boid, float distance, float power);
  float GetDistance(const class Boid& boid1, const class Boid& boid2);

  std::vector<const Boid*> GetNeighbors(const class Boid& boid, float distance);
 

  void HandleEdge(class Boid& boid);
 
};

#endif
