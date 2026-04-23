#include "collision.hpp"

void CollisionManager::CheckProjectileEnemyCollisions(
    std::vector<Projectile>& projectiles, std::vector<Enemy>& enemies) {
  for (auto& enemy : enemies) {
    for (auto& projectile : projectiles) {
      if (!projectile.IsActive()) continue;

      bool rectCollision = CheckCollisionRecs(
          Rectangle{ projectile.GetPosition().x - projectile.GetRadius(),
                     projectile.GetPosition().y - projectile.GetRadius(),
                     projectile.GetRadius() * 2, projectile.GetRadius() * 2 },
          enemy.GetBounds());

      if (rectCollision) {
        enemy.TakeDamage();
        projectile.SetActive(false);
      }
    }
  }
}
