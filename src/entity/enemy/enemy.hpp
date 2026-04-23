#pragma once
#include <vector>
#include <raylib.h>
#include <raymath.h>
#include "../projectile/projectile.hpp"
#include <entity/entity.hpp>

class Enemy : public Entity {
 private:
  Vector2 position =
      Vector2({ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f });
  float speed = 4.0f;
  float hp = 3;
  std::vector<Color> color_s = { RED, ORANGE, BLUE };
  std::vector<Projectile> projectile_s = {};
  int projectileCountMax = 1;

  int margin = 24.0f;
  float width = 80.0f;
  float height = 80.0f;

 public:
  Enemy(/* args */);
  ~Enemy();

  void Draw();

  Vector2 GetPosition() const;
  float GetRadius() const;
  Rectangle GetBounds() const;
  void TakeDamage();
  bool IsDead() const;
};