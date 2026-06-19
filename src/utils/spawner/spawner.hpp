#pragma once
#include <vector>
#include <raylib.h>
#include "entity/enemy/enemy.hpp"


// TODO: Niech używa template i służy również do spawnowania pocisków
class Spawner
{
 public:
  Spawner();
  ~Spawner();
  std::vector<Enemy> SpawnWave(int rows, int cols);
};
