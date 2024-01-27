#include "BoidManager.h"
#include "Boid.h"
#include <random>
#include <SDL3/SDL.h>

#include <iostream>

void BoidManager::InitBoids(SDL_Rect fieldRect, int boidCount) {
  this->fieldRect = fieldRect;
  std::random_device rd;
  std::mt19937 gen(rd());

  std::cout<<fieldRect.x<<" "<<fieldRect.y<<" fieldrect\n";

  // Random in range distribution
  std::uniform_int_distribution<> yDistr(fieldRect.x, fieldRect.x + fieldRect.w);
  std::uniform_int_distribution<> xDistr(fieldRect.y, fieldRect.y + fieldRect.h);
  
  for (int i = 0; i < boidCount; i++) {
    int xPos = xDistr(gen);
    int yPos = yDistr(gen);
    std::cout<<"Creating boid at "<<xPos<<"x. "<<yPos<<"y.\n";
    Boid b(xPos, yPos, 0, 1);
  }
}

void BoidManager::MoveBoids(){
  std::cout<<"Moving Boids \n";
}
