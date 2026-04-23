#pragma once
#include <vector>
#include <algorithm>
#include <raylib.h>
#include <raymath.h>
#include "../projectile/projectile.hpp"
#include <entity/entity.hpp>

class Player : public Entity {
 private:
  Vector2 position =
      Vector2({ GetScreenWidth() / 2.0f, GetScreenHeight() - 24.0f });
  float speed = 4.0f;
  float hp = 4;
  std::vector<Projectile> projectile_s = {};
  int projectileCountMax = 1;

  int margin = 24.0f;

 public:
  Player(/* args */);
  ~Player();

  void Draw();
  void Shoot();
  std::vector<Projectile>& GetProjectiles();
  void RemoveProjectile(int index);
};