#include "enemy.hpp"

Enemy::Enemy() {}

Enemy::~Enemy() {}

void Enemy::Draw() {
  DrawRectangle(position.x, position.y, width, height, color_s.at(hp - 1));
}

float Enemy::GetRadius() const { return width; }

Rectangle Enemy::GetBounds() const {
  return Rectangle{ position.x, position.y, width, height };
}

void Enemy::TakeDamage() { hp -= 1; }

bool Enemy::IsDead() const { return hp <= 0; }