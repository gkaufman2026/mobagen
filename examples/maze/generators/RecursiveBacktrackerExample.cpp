#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>

bool RecursiveBacktrackerExample::Step(World* w) {
  // todo: implement this
  if (stack.empty && visited.empty()) {
    stack.push_back(randomStartPoint(w));
  }
  return false;
}

void RecursiveBacktrackerExample::Clear(World* world) {
  visited.clear();
  stack.clear();
  auto sideOver2 = world->GetSize() / 2;
  for (int i = -sideOver2; i <= sideOver2; i++) {
    for (int j = -sideOver2; j <= sideOver2; j++) {
      visited[i][j] = false;
    }
  }
}

Point2D RecursiveBacktrackerExample::randomStartPoint(World* world) {
  auto sideOver2 = world->GetSize() / 2;
  // todo: change this if you want
  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitables;

  if (p.x -1 >= -sideOver2 || p.y - 1 >= -sideOver2) {
    visitables.push_back(Point2D(p.x - 1, p.y));
  }

  if (p.x + 1 <= sideOver2 || p.y + 1 <= sideOver2) {
    visitables.push_back(Point2D(p.x, p.y + 1));
  }

  return visitables;
}
