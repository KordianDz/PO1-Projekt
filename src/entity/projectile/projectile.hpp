#pragma once
#include "raylib.h"

class Projectile {
 private:
  Vector2 position = {};
  float speed = 4.0f;
  bool active = true;

 public:
  Projectile(Vector2 position);
  ~Projectile();

  void Draw();
  bool IsOutOfBounds() const;
  bool IsActive() const;
};