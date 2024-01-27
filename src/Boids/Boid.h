#ifndef BOID_H
#define BOID_H

#include <SDL3/SDL_rect.h>

class Boid {
public:
  Boid(float a_xPos, float a_yPos, float a_xVel, float a_yVel);
  void MoveForward(float a_minSpeed = 0.1f, float a_maxSpeed = 1);
  float xVel{};
  float yVel{};
  SDL_FRect rect;

private:
  float GetSpeed();
};

#endif
