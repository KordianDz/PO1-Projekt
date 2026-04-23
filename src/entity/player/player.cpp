#include "player.hpp"

Player::Player(/* args */) {}

Player::~Player() {}

void Player::Draw() {
  if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
    position.x -= speed;
  };
  if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
    position.x += speed;
  }

  position.x = Clamp(position.x, margin, GetScreenWidth() - margin);

  std::erase_if(projectile_s,
                [](const Projectile& p) { return !p.IsActive(); });

  for (auto& p : projectile_s) {
    p.Draw();
  }

  DrawCircleV(position, 12, MAROON);
}

void Player::Shoot() {
  if (projectile_s.size() < projectileCountMax) {
    projectile_s.emplace_back(Vector2(position));
  }
}

std::vector<Projectile>& Player::GetProjectiles() { return projectile_s; }

void Player::RemoveProjectile(int index) {
  if (index >= 0 && index < static_cast<int>(projectile_s.size())) {
    projectile_s.erase(projectile_s.begin() + index);
  }
}