#include "BoidManager.h"
#include "Boid.h"
#include <random>
#include <SDL3/SDL.h>
#include <utility>

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
    boids.push_back(b);
  }
}

void BoidManager::MoveBoids(){
  for (Boid& boid : boids)
    {
      std::cout<<"Moving a boid...\n";
      // first = x, second = y.
      std::pair<float, float> separateVel = Separate(boid, 50, 0.0001f);
      std::cout<<"seperateVel = "<<separateVel.first<<'.'<<separateVel.second<<'\n';
      // std::pair<float, float> alignVel = Align(boid, 50, .01);
      // std::pair<float, float> cohereVel = Cohere(boid, 15, .001);
      // boid.xVel = separateVel.first + alignVel.first + cohereVel.first;
      // boid.yVel = separateVel.second+ alignVel.second+ cohereVel.second;
    }
}


std::pair<float, float> BoidManager::Separate(class Boid& boid, float distance, float power) {

  // Get neighbors
  std::vector<const Boid*> neighbors;
  for (const auto& other : boids) {
    float dist = GetDistance(boid, other);
    if (dist == 0)
      {
	continue;
      }
    else if (dist < distance)
      {
	neighbors.push_back(&other);
      }
  }

  float sumClosenessX, sumClosenessY = 0;
  for (const Boid* neighbor : neighbors)
    {
      float closeness = distance - GetDistance(boid, *neighbor);
      sumClosenessX += (boid.rect.x - neighbor->rect.x) * closeness;
      sumClosenessY += (boid.rect.y - neighbor->rect.y) * closeness;
    }


  return std::make_pair(sumClosenessX * power, sumClosenessY * power);
}

std::pair<float, float> BoidManager::Align(class Boid& boid, float distance, float power) {

  return std::make_pair(0.0f,0.0f); // Something went wrong
}

std::pair<float, float> BoidManager::Cohere(class Boid& boid, float distance, float power) {
  
  return std::make_pair(0.0f,0.0f); // Something went wrong
}

float BoidManager::GetDistance(const Boid& boid1, const Boid& boid2) {
  float diffX = boid1.rect.x - boid2.rect.x;
  float diffY = boid1.rect.y - boid2.rect.y;
  float dist = std::sqrt((diffY * diffY) + (diffX * diffX));

  // std::cout<<"Getting distance from Boid1 = "<<boid1.rect.x<<"x."<<boid1.rect.y<<"y and Boid2 = "<<boid2.rect.x<<"x."<<boid2.rect.y<<"y.\n";
  //  std::cout<<"Distance "<<dist<<'\n';

  return dist;
}
