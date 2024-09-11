#include "JohnConway.h"

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
  // todo: implement
  int row, column, currenNeighborCount;
  bool isWithinSpace;

  for (row = 0; row < world.SideSize(); row++) {
    for (column = 0; column < world.SideSize(); column++) {
      const Point2D newPoint = Point2D{row, column};
      isWithinSpace = world.Get(newPoint);
      currenNeighborCount = CountNeighbors(world, newPoint);

      if (isWithinSpace) {
        currenNeighborCount <= 3 ? world.SetNext(newPoint, true) : world.SetNext(newPoint, false);
      } else {
        if (currenNeighborCount == 3) {
          world.SetNext(newPoint, true);
        }
      }
    }
  }
}

int JohnConway::CountNeighbors(World& world, Point2D point) {
  // todo: implement
  int sumOfNeighbors = 0;
  int row, column;

  for (row = point.x - 1; row < point.x + 2; row++) {
    for (column = point.y - 1; column < point.y + 2; column++) {
      if (point.x != 1 || point.y != 1) {
        const Point2D newPoint = Point2D{row, column};
        sumOfNeighbors += (int) world.Get(newPoint);
      }
    }
  }
  return sumOfNeighbors;
}
