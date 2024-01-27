#ifndef BOID_H
#define BOID_H

#include <SDL3/SDL_rect.h>

class Boid {
public:
  Boid(float a_xPos, float a_yPos, float a_xVel, float a_yVel);
  void MoveForward(float a_minSpeed = 1, float a_maxSpeed = 5);

private:
  float GetSpeed();
  SDL_Rect rect;
  float xVel{};
  float yVel{};
};

#endif
