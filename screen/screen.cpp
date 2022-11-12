#include "screen.hpp"

Screen::Screen() {
  this->screen_objects = new Object[HEIGHT * WIDTH];

  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      this->add_object(make_object(make_vector2(y, x), ' '));
    }
  }
}

void Screen::update() {}

void Screen::render() {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      printf("%c", this->screen_objects[y * HEIGHT + x].character);
    }

    printf("\n");
  }
}

void Screen::clear() { printf("\033[2J\033[1;1H"); }

void Screen::add_object(Object object) {
  Vector2 position = object.position;
  this->screen_objects[position.y * HEIGHT + position.x] = object;
}

void Screen::add_string(string str, Vector2 position) {
  for (int index = 0; index < str.length(); index++) {
    Object new_object;

    new_object.character = str[index];
    new_object.position = make_vector2(position.x + index, position.y);

    this->add_object(new_object);
  }
}

Screen::~Screen() { delete this->screen_objects; }
