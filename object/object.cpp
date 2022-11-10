#include "object.hpp"

Object make_object(Vector2 position, char character) {
  Object object;

  object.position = position;
  object.character = character;

  return object;
}
