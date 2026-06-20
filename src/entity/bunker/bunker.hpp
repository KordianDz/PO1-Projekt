#pragma once
#include <raylib.h>
#include <entity/entity.hpp>

class Bunker : public Entity
{
 private:
  int hp = 1;
  int maxHp = 1;
  float width = 10.0f;
  float height = 10.0f;

 public:
  Bunker(Vector2 position);
  ~Bunker() = default;

  void Update() override;
  void Draw() override;

  Rectangle GetBounds() const;
  void TakeDamage();
  bool IsDead() const;
};
