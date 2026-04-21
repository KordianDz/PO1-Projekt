#include "projectile.hpp"

Projectile::Projectile(Vector2 position) { this->position = position; }

Projectile::~Projectile() {}

void Projectile::Draw() {
  position.y -= 1;

  if (IsOutOfBounds()) active = false;

  DrawCircleV(position, 6, MAROON);
}

bool Projectile::IsOutOfBounds() const {
  return position.y < 0.0f || position.y > GetScreenHeight() ||
         position.x < 0.0f || position.x > GetScreenWidth();
}

bool Projectile::IsActive() const { return active; }
