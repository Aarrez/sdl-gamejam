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

  // Random in range distribution
  std::uniform_int_distribution<> xDistr(fieldRect.x, fieldRect.x + fieldRect.w);
  std::uniform_int_distribution<> yDistr(fieldRect.y, fieldRect.y + fieldRect.h);
  std::uniform_real_distribution<> speed(-1, 1);
  
  
  for (int i = 0; i < boidCount; i++) {
    int xPos = xDistr(gen);
    int yPos = yDistr(gen);

    Boid b(xPos, yPos, speed(gen), speed(gen));
    boids.push_back(b);
  }
}

void BoidManager::MoveBoids(){
  for (Boid& boid : boids)
    {
      // first = x, second = y.
      std::pair<float, float> separateVel = Separate(boid, 50, 0.0001f);
      std::pair<float, float> alignVel = Align(boid, 50, .01);
      std::pair<float, float> cohereVel = Cohere(boid, 15, .0001);

      // std::cout<<"seperateVel = "<<separateVel.first<<'.'<<separateVel.second<<'\n';
      // std::cout<<"alignVel = "<<alignVel.first<<'.'<<alignVel.second<<'\n';
      // std::cout<<"cohereVel = "<<cohereVel.first<<'.'<<cohereVel.second<<'\n';

      boid.xVel += separateVel.first + alignVel.first + cohereVel.first;
      boid.yVel += separateVel.second + alignVel.second + cohereVel.second;
    }

  // Move each boid forward
  for (Boid& boid : boids) {
    boid.MoveForward();
    HandleEdge(boid);
  }
}


std::pair<float, float> BoidManager::Separate(class Boid& boid, float distance, float power) {

  // Get neighbors
  std::vector<const Boid*> neighbors = GetNeighbors(boid, distance);

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
  auto neighbors = GetNeighbors(boid, distance);
  // Does this return work?
  if (neighbors.empty())
  {
    return std::make_pair(0.0f,0.0f);
  }

  float sumVelX = 0;
  float sumVelY = 0;
  for (auto n : neighbors) {
    sumVelX += n->xVel;
    sumVelY += n->yVel;
  }

  float meanVelX = sumVelX / neighbors.size();
  float meanVelY = sumVelY / neighbors.size();

  float xVel = meanVelX - boid.xVel;
  float yVel = meanVelY - boid.yVel;
  return std::make_pair(xVel * power, yVel * power);

}

std::pair<float, float> BoidManager::Cohere(class Boid& boid, float distance, float power) {
  auto neighbors = GetNeighbors(boid, distance);
  if (neighbors.empty())
  {
    return std::make_pair(0.0f,0.0f);
  }
  float sumX, sumY = 0;
  for (auto n : neighbors) {
    sumX += n->rect.x;
    sumY += n->rect.y;
  }

  float meanX, meanY = 0;
  float deltaCenterX = meanX - boid.rect.x;
  float deltaCenterY = meanY - boid.rect.y;
  return std::make_pair(deltaCenterX * power, deltaCenterY * power);
}

float BoidManager::GetDistance(const Boid& boid1, const Boid& boid2) {
  float diffX = boid1.rect.x - boid2.rect.x;
  float diffY = boid1.rect.y - boid2.rect.y;
  float dist = std::sqrt((diffY * diffY) + (diffX * diffX));

  // std::cout<<"Getting distance from Boid1 = "<<boid1.rect.x<<"x."<<boid1.rect.y<<"y and Boid2 = "<<boid2.rect.x<<"x."<<boid2.rect.y<<"y.\n";
  //  std::cout<<"Distance "<<dist<<'\n';

  return dist;
}

std::vector<const Boid*> BoidManager::GetNeighbors(const Boid& boid, float distance) {
  
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

  return neighbors;
}

void BoidManager::HandleEdge(class Boid& boid) {

  // Smooth turn away when near walls
  float pad = 10.0f;
  float turn = 0.5f;
  if (boid.rect.x < fieldRect.x + pad)
    boid.xVel += turn;
  if (boid.rect.x > fieldRect.w - pad)
    boid.xVel -= turn;
  if (boid.rect.y < fieldRect.y + pad)
    boid.yVel += turn;
  if (boid.rect.y > fieldRect.h - pad)
    boid.yVel -= turn;

  // WrapAround
  /*
  if (boid.rect.x < fieldRect.x){
    boid.rect.x += fieldRect.w;
  }
  if (boid.rect.x > (fieldRect.x + fieldRect.w)){
    boid.rect.x -= fieldRect.w;
  }
  if (boid.rect.y < fieldRect.y){
    boid.rect.y += fieldRect.h;
  }
  if (boid.rect.y > (fieldRect.y + fieldRect.h)){
    boid.rect.y -= fieldRect.h;
  }
  */
}
