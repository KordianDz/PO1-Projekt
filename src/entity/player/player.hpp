#pragma once
#include <vector>
#include <algorithm>
#include <raylib.h>
#include <raymath.h>
#include "../projectile/projectile.hpp"
#include <entity/entity.hpp>

/**
 * @brief Klasa reprezentująca statek gracza.
 * 
 * Gracz posiada określoną ilość punktów życia (HP), może poruszać się 
 * na boki oraz wystrzeliwać własne pociski. Dziedziczy z klasy Entity.
 */
class Player : public Entity
{
 private:
  float hp = 3;                                ///< Punkty życia gracza.
  std::vector<Projectile> projectile_s = {};   ///< Kontener aktywnych pocisków wystrzelonych przez gracza.
  int projectileCountMax = 1;                  ///< Maksymalna liczba pocisków jednocześnie na ekranie.

  float margin = 24.0f;                        ///< Margines ruchu przy krawędziach ekranu.
  float radius = 12.0f;                        ///< Promień (rozmiar) gracza używany w obliczeniach kolizji.

 public:
  /**
   * @brief Konstruktor domyślny klasy Player.
   * Ustala pozycję początkową i parametry gracza.
   */
  Player();

  /**
   * @brief Destruktor klasy Player.
   */
  ~Player();

  /**
   * @brief Aktualizuje pozycję gracza oraz jego pocisków.
   */
  void Update() override;

  /**
   * @brief Rysuje statek gracza i jego pociski.
   */
  void Draw() override;

  /**
   * @brief Wykonuje strzał z lasera gracza (jeśli limit na ekranie pozwala).
   */
  void Shoot();

  /**
   * @brief Redukuje punkty życia gracza po trafieniu.
   */
  void TakeDamage();

  /**
   * @brief Sprawdza, czy gracz stracił wszystkie punkty życia.
   * @return true jeśli HP <= 0, false w przeciwnym wypadku.
   */
  bool IsDead() const;

  /**
   * @brief Zwraca aktualne punkty życia gracza (w celach UI).
   * @return Liczba punktów życia (HP).
   */
  float GetHP() const;

  /**
   * @brief Pobiera granice kolizji gracza jako prostokąt.
   * @return Prostokąt otaczający gracza.
   */
  Rectangle GetBounds() const;

  /**
   * @brief Dostęp do wektora pocisków gracza.
   * @return Referencja do wektora pocisków.
   */
  std::vector<Projectile>& GetProjectiles();

  /**
   * @brief Ręcznie usuwa pocisk z wektora (niezalecane, zamiast tego pocisk powinien zostać dezaktywowany).
   * @param index Indeks pocisku do usunięcia.
   */
  void RemoveProjectile(int index);
};