#include <raylib.h>
#include <stdbool.h>

bool IsPlrJumping()
{
  return IsKeyDown(KEY_SPACE) || IsMouseButtonDown(MOUSE_BUTTON_LEFT);
}

int main(int argc, const char **argv) {
  int screenWidth, screenHeight;

  screenWidth = 1600;
  screenHeight = 800;

  for (int i = 0; i < argc; i++) {
    if (i == 1)
      screenWidth = TextToInteger(argv[1]);
    if (i == 2)
      screenHeight = TextToInteger(argv[2]);
  }

  InitWindow(screenWidth, screenHeight, "Dinossauro");
  InitAudioDevice();

  int groundY = (screenHeight * 0.75) - 100;
  int dinoY = groundY;

  SetTargetFPS(30);
  int jumpDb = 0;


  bool gameOn = false;
  int frames = 0;

  double obsX = screenWidth;
  int obsY = groundY;

  int prevScore = 0;
  double obsVel = 10;
  
  // Music
  Music music = LoadMusicStream("./assets/music.mp3");
  
  Sound jumpSfx = LoadSound("./assets/jump.mp3");
  SetSoundVolume(jumpSfx, 1.2f);
  while (!WindowShouldClose()) {
    if (!gameOn && IsPlrJumping()) {gameOn = true; PlayMusicStream(music);};
    if (jumpDb == 0 && IsPlrJumping() && dinoY == groundY) {
      PlaySound(jumpSfx);
      jumpDb = 25;
      dinoY -= 500;
    }

    if (jumpDb > 0)
      jumpDb--;

    /*
     *
     *
     *   DRAWING BLOCK
     *
     */

    BeginDrawing();
    ClearBackground(LIGHTGRAY);

    if (gameOn) {
      DrawText(TextFormat("Score: %d | jumpDb: %d | Obstacle speed: %.2f | FPS: %d", frames,jumpDb, obsVel, GetFPS()), 0, 0, 30, BLACK);
      DrawRectangle(100, dinoY, 100, 100, DARKGREEN);
      DrawRectangle(0, screenHeight * 0.75, screenWidth, screenHeight / 4, BROWN);
     
      // Obstacle

      DrawRectangle(obsX, obsY, 100, 100, RED);
      obsX -=  obsVel;


      if (obsX < 0 - 100) obsX = screenWidth;
      if (100 + 100 > obsX && 100 < obsX + 100 
      &&  dinoY + 100 > obsY && dinoY < obsY + 100) {gameOn = false; prevScore = frames;frames = 0; StopMusicStream(music);};
 
      obsVel = 10 + (double) frames / 100;
    frames++;
    } else {
      if (prevScore == 0) DrawText("Press Space to begin", screenWidth / 2, screenHeight / 2, 50, BLACK);
      if (prevScore > 0) DrawText(TextFormat("!GAME OVER! Score: %d (Press Space to Begin)", prevScore), 0, screenHeight / 2, 40, BLACK);
    }
    EndDrawing();

    if (!(dinoY == groundY))
      dinoY += 20;
    if (dinoY > groundY)
      dinoY = groundY;
  }
  return 0;
}
