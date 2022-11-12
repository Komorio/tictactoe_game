#include "game.hpp"

Game::Game(Screen *screen) {
  this->screen = screen;

  this->game_turn = None;

  do {
    printf("Select First team (O/X): ");

    int key = getchar();

    if (key == O) {
      this->game_turn = OTeam;
    } else if (key == X) {
      this->game_turn = XTeam;
    }

    this->screen->clear();
  } while (this->game_turn == None);

  this->init();
}

void Game::init() {
  this->game_board_position = make_vector2(5, 3);
  this->cursor_position = this->game_board_position;

  this->checked = new Object[BOARD_HEIGHT * BOARD_WIDTH];

  for (int y = 0; y < BOARD_HEIGHT; y++) {
    for (int x = 0; x < BOARD_WIDTH; x++) {
      this->checked[y * BOARD_HEIGHT + x] =
          make_object(make_vector2(x, y), ' ');
    }
  }

  this->winner_team = None;

  this->make_manual();
  this->update_render();
}

void Game::make_manual() {
  this->screen->add_string("--- Map ---", make_vector2(15, 4));

  this->screen->add_string("C - Your cursor", make_vector2(15, 5));
  this->screen->add_string("E - Empty Cell", make_vector2(15, 6));

  this->screen->add_string("--- Control ---", make_vector2(15, 8));

  this->screen->add_string("h - Left", make_vector2(15, 9));
  this->screen->add_string("j - Down", make_vector2(15, 10));
  this->screen->add_string("k - Up", make_vector2(15, 11));
  this->screen->add_string("l - Right", make_vector2(15, 12));
  this->screen->add_string("s - Select", make_vector2(15, 13));
}

void Game::make_game_board() {
  for (int i = 0; i < BOARD_HEIGHT; i++) {
    for (int j = 0; j < BOARD_WIDTH; j++) {
      Object new_object;

      int x = this->game_board_position.x + j;
      int y = this->game_board_position.y + i;

      Vector2 object_position = make_vector2(x, y);
      Object checked = this->checked[i * BOARD_HEIGHT + j];

      if (checked.character == 'O') {
        new_object.character = 'O';
      } else if (checked.character == 'X') {
        new_object.character = 'X';
      } else {
        new_object.character = 'E';
      }

      new_object.position = object_position;

      this->screen->add_object(new_object);
    }
  }
}

void Game::make_cursor() {
  if (this->is_game_done) {
    return;
  }

  Object cursor;

  cursor.character = 'C';
  cursor.position = this->cursor_position;

  this->screen->add_object(cursor);
}

void Game::update() {
  this->check_winner();
  this->update_render();

  int key = getchar();

  if (this->is_game_done) {
    this->screen->clear();
    return;
  }

  switch (key) {
  default:
  case ENTER:
    this->screen->clear();
    return;
  case H:
    this->move_cursor(make_vector2(-1, 0));
    break;
  case J:
    this->move_cursor(make_vector2(0, 1));
    break;
  case K:
    this->move_cursor(make_vector2(0, -1));
    break;
  case L:
    this->move_cursor(make_vector2(1, 0));
    break;
  case S:
    this->select();
    break;
  }
}

void Game::move_cursor(Vector2 direction) {
  int x = this->cursor_position.x + direction.x;
  int y = this->cursor_position.y + direction.y;

  int maxX = this->game_board_position.x + BOARD_WIDTH;
  if (x < this->game_board_position.x || x >= maxX) {
    return;
  }

  int maxY = this->game_board_position.y + BOARD_HEIGHT;
  if (y < this->game_board_position.y || y >= maxY) {
    return;
  }

  Vector2 position = make_vector2(x, y);
  this->cursor_position = position;
}

void Game::change_turn() {
  this->game_turn = this->game_turn == OTeam ? XTeam : OTeam;
}

void Game::check_winner() {
  int win_case[8][3] = {
      // Horizontal
      {0, 1, 2},
      {3, 4, 5},
      {6, 7, 8},

      // Vertical
      {0, 3, 6},
      {1, 4, 7},
      {2, 5, 8},

      // Diagonal
      {0, 4, 8},
      {2, 4, 6},
  };

  for (int i = 0; i < 8; i++) {
    char prev_char = this->checked[win_case[i][0]].character;
    if (prev_char == ' ') {
      continue;
    }

    int count = 0;

    for (int j = 1; j < 3; j++) {
      char current_char = this->checked[win_case[i][j]].character;

      if (prev_char == current_char) {
        count++;
      } else {
        break;
      }
    }

    if (count == 2) {
      if (prev_char == 'O') {
        this->winner_team = OTeam;
      } else if (prev_char == 'X') {
        this->winner_team = XTeam;
      }

      this->is_game_done = true;
      return;
    }
  }

  int count = 0;
  int size = BOARD_HEIGHT * BOARD_WIDTH;

  for (int index = 0; index < size; index++) {
    if (this->checked[index].character != ' ') {
      count++;
    }
  }

  bool is_draw = count == size;

  if (is_draw) {
    this->is_game_done = true;
  }
}

void Game::select() {
  if (this->check_is_empty() == false) {
    return;
  }

  int x = this->cursor_position.x - this->game_board_position.x;
  int y = this->cursor_position.y - this->game_board_position.y;

  if (this->game_turn == OTeam) {
    this->checked[y * BOARD_HEIGHT + x].character = 'O';
  } else if (this->game_turn == XTeam) {
    this->checked[y * BOARD_HEIGHT + x].character = 'X';
  }

  this->change_turn();
}

bool Game::check_is_empty() {
  int x = this->cursor_position.x - this->game_board_position.x;
  int y = this->cursor_position.y - this->game_board_position.y;

  return this->checked[y * BOARD_HEIGHT + x].character == ' ';
}

void Game::update_render() {
  this->make_game_board();
  this->make_cursor();

  this->screen->add_string("--- State ---", make_vector2(15, 0));

  if (this->winner_team == None) {
    this->screen->add_string("WINNER : \0", make_vector2(15, 1));
  } else if (this->winner_team == OTeam) {
    this->screen->add_string("WINNER : O", make_vector2(15, 1));
  } else if (this->winner_team == XTeam) {
    this->screen->add_string("WINNER : X", make_vector2(15, 1));
  }

  if (this->game_turn == OTeam) {
    this->screen->add_string("Turn : O", make_vector2(15, 2));
  } else if (this->game_turn == XTeam) {
    this->screen->add_string("Turn : X", make_vector2(15, 2));
  }
}

Game::~Game() { delete this->checked; }
