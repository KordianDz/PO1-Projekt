#include <cstdlib>
#include <ctime>
#include <numeric>
#include <map>
#include "raylib.h"
#include "gui/pause/pause.h"
#include "entity/player/player.hpp"
#include "entity/enemy/enemy.hpp"
#include "entity/bunker/bunker.hpp"
#include "utils/collision/collision.hpp"
#include "utils/spawner/spawner.hpp"

int main(void)
{
  // Inicjalizacja gry
  const int screenWidth = 800;
  const int screenHeight = 450;

  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(screenWidth, screenHeight, "Space Invaders");

  std::srand(static_cast<unsigned int>(std::time(nullptr)));

  SetTargetFPS(60);

  // Zmienne stanu gry
  bool gameOver = false;
  bool gameWon = false;
  int score = 0;

  Player player;
  Spawner spawner;
  std::vector<Enemy> enemies = spawner.SpawnWave(5, 11);
  CollisionManager collisionManager;

  // tworzenie bunkrow w ksztalcie
  std::vector<Bunker> bunkers;
  for (int b = 0; b < 4; b++)
  {
    float offsetX = 100.0f + b * 180.0f;
    float offsetY = screenHeight - 100.0f;
    for (int row = 0; row < 4; row++)
    {
      for (int col = 0; col < 6; col++)
      {
        // Wyciecie "łuku"
        if (row >= 2 && (col == 2 || col == 3)) continue;
        bunkers.emplace_back(Vector2{ offsetX + col * 10.0f, offsetY + row * 10.0f });
      }
    }
  }

  // Glowna petla gry
  while (!WindowShouldClose())
  {
    if (!PAUSE && !gameOver && !gameWon)
    {
      // Obsługa wejścia gracza
      if (IsKeyPressed(KEY_SPACE))
      {
        player.Shoot();
      }

      // Aktualizacja logiki gracza
      player.Update();

      // Aktualizacja wrogów
      Enemy::needsDropDown = false;
      for (auto& enemy : enemies)
      {
        enemy.Update();
      }

      // Obniżenie wrogów jeśli dotknęli krawędzi
      if (Enemy::needsDropDown)
      {
        Enemy::moveDirection *= -1;
        for (auto& enemy : enemies)
        {
          enemy.DropDown();
        }
      }

      // Aktualizacja bunkrów
      for (auto& bunker : bunkers)
      {
        bunker.Update();
      }

      // Sprawdzanie kolizji

      // Kolizje: pociski gracza -> wrogowie
      collisionManager.CheckCollisionsSingleShooter(player, enemies);

      // Kolizje: pociski gracza -> bunkry
      collisionManager.CheckCollisionsSingleShooter(player, bunkers);

      // Kolizje: pociski wrogów -> gracz
      collisionManager.CheckCollisions(enemies, player);

      // Kolizje: pociski wrogów -> bunkry
      collisionManager.CheckCollisions(enemies, bunkers);

      // Zliczanie punktów i usuwanie martwych bytów
      score += std::accumulate(
          enemies.begin(), enemies.end(), 0, [](int acc, const Enemy& e)
          { return acc + (e.IsDead() ? 100 + 25 * e.row : 0); });

      std::erase_if(enemies, [](const Enemy& e) { return e.IsDead(); });
      std::erase_if(bunkers, [](const Bunker& b) { return b.IsDead(); });

      // Mechanika pozwalająca na strzelanie tylko pierwszemu wrogowi z brzegu (w każdej kolumnie)
      std::map<int, Enemy*> bottomEnemies;
      for (auto& e : enemies)
      {
        e.canShoot = false;
        if (bottomEnemies.find(e.col) == bottomEnemies.end() || bottomEnemies[e.col]->row < e.row)
        {
          bottomEnemies[e.col] = &e;
        }
      }
      for (auto const& [col, e] : bottomEnemies)
      {
        e->canShoot = true;
      }

      // Sprawdzenie warunków zakończenia gry
      if (player.IsDead())
      {
        gameOver = true;
      }
      if (enemies.empty())
      {
        gameWon = true;
      }
    }

    // Obsługa restartu gry
    if ((gameOver || gameWon) && IsKeyPressed(KEY_R))
    {
      gameOver = false;
      gameWon = false;
      score = 0;
      player = Player();
      Enemy::moveDirection = 1;
      Enemy::needsDropDown = false;
      enemies = spawner.SpawnWave(5, 11);

      bunkers.clear();
      for (int b = 0; b < 4; b++)
      {
        float offsetX = 100.0f + b * 180.0f;
        float offsetY = screenHeight - 100.0f;
        for (int row = 0; row < 4; row++)
        {
          for (int col = 0; col < 6; col++)
          {
            if (row >= 2 && (col == 2 || col == 3)) continue;
            bunkers.emplace_back(Vector2{ offsetX + col * 10.0f, offsetY + row * 10.0f });
          }
        }
      }
    }

    // Rysowanie
    BeginDrawing();
    {
      ClearBackground(RAYWHITE);

      player.Draw();

      for (auto& enemy : enemies)
      {
        enemy.Draw();
      }

      for (auto& bunker : bunkers)
      {
        bunker.Draw();
      }

      // HUD
      DrawText(TextFormat("SCORE: %d", score), 10, 10, 20, DARKGRAY);
      DrawText(TextFormat("HP: %.0f", player.GetHP()), screenWidth - 100, 10, 20, DARKGRAY);

      // Ekran Game Over
      if (gameOver)
      {
        DrawText("GAME OVER", screenWidth / 2 - 120, screenHeight / 2 - 30, 40, RED);
        DrawText("Nacisnij R aby zagrac ponownie", screenWidth / 2 - 170, screenHeight / 2 + 20, 20, DARKGRAY);
      }

      // Ekran wygranej
      if (gameWon)
      {
        DrawText("YOU WIN!", screenWidth / 2 - 100, screenHeight / 2 - 30, 40, GREEN);
        DrawText("Nacisnij R aby zagrac ponownie", screenWidth / 2 - 170, screenHeight / 2 + 20, 20, DARKGRAY);
      }

      PauseMenu();
    }
    EndDrawing();
  }

  // Deinicjalizacja
  CloseWindow();
  return 0;
}