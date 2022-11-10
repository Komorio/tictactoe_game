#ifndef OBJECT
#define OBJECT

#include "../vector2/vector2.hpp"

struct Object {
  Vector2 position;
  char character;
};

Object make_object(Vector2 position, char character);

#endif
