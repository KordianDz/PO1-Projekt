#pragma once
#include <vector>
#include <raylib.h>
#include "entity/projectile/projectile.hpp"

// Zmienione
class CollisionManager
{
 public:
  // Wektor pociskow z wektorem celow
  template <typename TShooter, typename TTarget>
  void CheckCollisions(std::vector<TShooter>& shooters, std::vector<TTarget>& targets)
  {
    for (auto& shooter : shooters)
    {
      CheckCollisionsSingleShooter(shooter, targets);
    }
  }

  // Wektor pociskow z pojedynczym celem
  template <typename TShooter, typename TTarget>
  void CheckCollisions(std::vector<TShooter>& shooters, TTarget& target)
  {
    if (target.IsDead()) return;

    for (auto& shooter : shooters)
    {
      for (auto& projectile : shooter.GetProjectiles())
      {
        if (!projectile.IsActive()) continue;

        Rectangle projRect = {
          projectile.GetPosition().x - projectile.GetRadius(),
          projectile.GetPosition().y - projectile.GetRadius(),
          projectile.GetRadius() * 2, projectile.GetRadius() * 2
        };

        if (CheckCollisionRecs(projRect, target.GetBounds()))
        {
          target.TakeDamage();
          projectile.SetActive(false);
        }
      }
    }
  }

  // Pociski jednego strzelca z wektorem celow
  template <typename TShooter, typename TTarget>
  void CheckCollisionsSingleShooter(TShooter& shooter, std::vector<TTarget>& targets)
  {
    for (auto& projectile : shooter.GetProjectiles())
    {
      if (!projectile.IsActive()) continue;

      Rectangle projRect = {
        projectile.GetPosition().x - projectile.GetRadius(),
        projectile.GetPosition().y - projectile.GetRadius(),
        projectile.GetRadius() * 2, projectile.GetRadius() * 2
      };

      for (auto& target : targets)
      {
        if (target.IsDead()) continue;

        if (CheckCollisionRecs(projRect, target.GetBounds()))
        {
          target.TakeDamage();
          projectile.SetActive(false);
          break;  // Pocisk zniszczony, nie rani kolejnych celów
        }
      }
    }
  }
};