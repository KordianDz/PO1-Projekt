#include "enemy.hpp"

Enemy::Enemy() {}

Enemy::~Enemy() {}

void Enemy::Draw() {
  DrawRectangle(GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f, 80, 80,
                MAROON);
}