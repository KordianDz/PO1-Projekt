#include <stddef.h>
#include "raylib.h"
#include "gui/pause/pause.h"
#include "entity/player/player.hpp"
#include "entity/enemy/enemy.hpp"
#include "utils/collision/collision.hpp"

int main(void) {
  // Initialization
  //---------------------------------------------------------
  const int screenWidth = 800;
  const int screenHeight = 450;

  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(screenWidth, screenHeight, "Arkanoid");

  int framesCounter = 0;

  SetTargetFPS(60);  // Set our game to run at 60 frames-per-second
  //----------------------------------------------------------

  Player player;
  std::vector<Enemy> enemies;
  enemies.emplace_back();
  CollisionManager collisionManager;

  // Main game loop
  while (!WindowShouldClose())  // Detect window close button or ESC key
  {
    framesCounter++;

    if (!PAUSE) {
      if (IsKeyPressed(KEY_SPACE)) {
        player.Shoot();
      }

      collisionManager.CheckProjectileEnemyCollisions(player.GetProjectiles(),
                                                      enemies);

      std::erase_if(enemies, [](const Enemy& e) { return e.IsDead(); });
    }

    BeginDrawing();
    {
      ClearBackground(RAYWHITE);

      player.Draw();

      for (auto& enemy : enemies) {
        enemy.Draw();
      }

      PauseMenu();

      DrawFPS(10, 10);
    }
    EndDrawing();
  }

  // De-Initialization
  //---------------------------------------------------------
  CloseWindow();  // Close window and OpenGL context
  //----------------------------------------------------------

  return 0;
}