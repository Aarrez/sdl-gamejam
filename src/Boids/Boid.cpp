#include "Boid.h"
#include <cmath>

Boid::Boid(float a_xPos, float a_yPos, float a_xVel, float a_yVel){
  rect.x = a_xPos;
  rect.y = a_yPos;
  yVel = a_yVel;
  xVel = a_xVel;

  rect.h = 15;
  rect.w = 15;
}

float Boid::GetSpeed() {
  return std::sqrt( std::pow(xVel, 2) + std::pow(yVel, 2) );
}

void Boid::MoveForward(float minSpeed, float maxSpeed) {
  rect.x += xVel;
  rect.y += yVel;

  float speed = GetSpeed();
  if (speed > maxSpeed) {
    xVel = (xVel / speed) * maxSpeed;
    yVel = (yVel / speed) * maxSpeed;
  } else if (speed < minSpeed) {
    xVel = (xVel / speed) * minSpeed;
    yVel = (yVel / speed) * minSpeed;
  }

  if (std::isnan(xVel))
    xVel = 0;
  if (std::isnan(yVel))
    yVel = 0;
} 
