#ifndef GAME
#define GAME

#include "../screen/screen.hpp"
#include "../vector2/vector2.hpp"

#define BOARD_WIDTH 3
#define BOARD_HEIGHT 3

enum GameTeam { OTeam, XTeam, None };
enum KEY_CODE {
  ENTER = 10,
  O = 79,
  X = 88,
  H = 104,
  J = 106,
  K = 107,
  L = 108,
  S = 115,
};

class Game {
private:
  Screen *screen;

  GameTeam game_turn;
  GameTeam winner_team;

  Object *checked;

  Vector2 game_board_position;
  Vector2 cursor_position;

  bool is_game_done;

  void make_game_board();
  void make_cursor();
  void make_manual();

  void move_cursor(Vector2 direction);
  void change_turn();

  void check_winner();

  void select();
  bool check_is_empty();

  void update_render();

public:
  Game(Screen *screen);

  void init();
  void update();

  ~Game();
};

#endif
