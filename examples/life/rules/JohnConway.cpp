#include "JohnConway.h"

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
  // todo: implement

}

int JohnConway::CountNeighbors(World& world, Point2D point) {
  // todo: implement
  int sumOfNeighbors = 0;
  int row, column;

  for (row = point.x - 1; row < 1; row++) {
    for (column = point.y - 1; column < 1; column++) {
      if (point.x != 1 && point.y != 1) {
        const Point2D newPoint = point + Point2D{row, column};
        sumOfNeighbors += world.Get(newPoint);
      }
    }
  }
  return sumOfNeighbors;
}
