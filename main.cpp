#include "game/game.hpp"
#include "object/object.hpp"
#include "screen/screen.hpp"
#include "vector2/vector2.hpp"

int main() {
  Screen *screen = new Screen();
  screen->clear();

  Game *game = new Game(screen);

  while (true) {
    screen->render();
    screen->update();

    game->update();
  }

  delete screen;
  delete game;

  return 0;
}
