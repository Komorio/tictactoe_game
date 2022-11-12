#ifndef SCREEN
#define SCREEN

#define WIDTH 30
#define HEIGHT 30

#include "../object/object.hpp"

#include <cstdio>
#include <iostream>

using std::string;

class Screen {
private:
  Object *screen_objects;

public:
  Screen();

  void update();
  void render();
  void clear();

  void add_object(Object object);
  void add_string(string str, Vector2 position);

  ~Screen();
};

#endif
