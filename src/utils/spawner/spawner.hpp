#pragma once
#include <vector>
#include <raylib.h>
#include "entity/enemy/enemy.hpp"

// Klasa spawnera
class Spawner
{
 public:
  Spawner() = default;
  ~Spawner() = default;

  // generowanie wielu obiektow
  template <typename T, typename... Args>
  std::vector<T> Spawn(int count, Args&&... args)
  {
    std::vector<T> entities;
    for (int i = 0; i < count; ++i)
    {
      entities.emplace_back(std::forward<Args>(args)...);
    }
    return entities;
  }

  // generowanie fali wrogow
  std::vector<Enemy> SpawnWave(int rows, int cols)
  {
    std::vector<Enemy> wave;
    float startX = (GetScreenWidth() - (cols * 50.0f)) / 2.0f;
    for (int r = 0; r < rows; r++)
    {
      for (int c = 0; c < cols; c++) {
        wave.emplace_back(Vector2{startX + c * 50.0f, 50.0f + r * 40.0f}, r, c);
      }
    }
    return wave;
  }
};
