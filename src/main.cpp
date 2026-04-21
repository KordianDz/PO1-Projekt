#include <stddef.h>
#include "raylib.h"
#include "gui/pause/pause.h"
#include "entity/player/player.hpp"
#include "entity/enemy/enemy.hpp"

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
  Enemy enemy;

  // Main game loop
  while (!WindowShouldClose())  // Detect window close button or ESC key
  {
    framesCounter++;

    if (!PAUSE) {
    }

    BeginDrawing();
    {
      ClearBackground(RAYWHITE);

      player.Draw();
      enemy.Draw();

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