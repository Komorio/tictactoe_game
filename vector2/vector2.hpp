#ifndef VECTOR2
#define VECTOR2

struct Vector2 {
  int x;
  int y;
};

struct Vector2 make_vector2(int x, int y);
struct Vector2 clone_vector2(Vector2 *vector);
void print_vector(Vector2 *vector);
#endif
