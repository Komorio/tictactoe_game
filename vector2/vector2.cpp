#include "vector2.hpp"
#include <cstdio>

Vector2 make_vector2(int x, int y) {
  Vector2 new_vector;

  new_vector.x = x;
  new_vector.y = y;

  return new_vector;
}

Vector2 clone_vector2(Vector2 *vector) {
  Vector2 new_vector;

  new_vector.x = vector->x;
  new_vector.y = vector->y;

  return new_vector;
}

void print_vector(Vector2 *vector) {
  printf("( %d, %d ) \n", vector->x, vector->y);
}
