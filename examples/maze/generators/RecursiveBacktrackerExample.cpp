#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>

bool RecursiveBacktrackerExample::Step(World* w) {
  // todo: implement this
  auto sideOver2 = w->GetSize() / 2;
  if (stack.empty() && !visited[-sideOver2][-sideOver2]) {
    stack.emplace_back(-sideOver2, -sideOver2);
    w->SetNodeColor({-sideOver2, -sideOver2}, Color::Green);
    return true;
  }
  if (!stack.empty()) {
    Point2D p = stack.back();
    std::vector<Point2D> neighbors = getVisitables(w, p);
    if (neighbors.size() > 0) {
      w->SetNodeColor(p, Color::Green);
      Point2D nextPoint = neighbors[getVisitableIndex() % neighbors.size()];
      std::cout << "Setting node to color" << '\n';
      stack.push_back(nextPoint);
    } else {
      Point2D nextPoint = stack.back();
      w->SetNodeColor(nextPoint, Color::Green);
      stack.pop_back();
    }
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

  // Left
  if (p.x + 1 <= sideOver2) {
    visitables.push_back(Point2D(p.x + 1, p.y));
  }

  // Right
  if (p.x - 1 >= -sideOver2) {
    visitables.push_back(Point2D(p.x - 1, p.y));
  }

  // Up
  if (p.y + 1 <= sideOver2) {
    visitables.push_back(Point2D(p.x, p.y + 1));
  }

  // Down
  if (p.x - 1 >= -sideOver2 || p.y - 1 >= -sideOver2) {
    visitables.push_back(Point2D(p.x, p.y - 1));
  }

  return visitables;
}
int RecursiveBacktrackerExample::getVisitableIndex() {
  int const sequence[] = {72, 99, 56, 34, 43, 62, 31, 4, 70, 22, 6, 65, 96, 71, 29, 9, 98, 41, 90, 7, 30, 3, 97, 49, 63, 88, 47, 82, 91, 54, 74, 2, 86, 14, 58, 35, 89, 11, 10, 60, 28, 21, 52, 50, 55, 69, 76, 94, 23, 66, 15, 57, 44, 18, 67, 5, 24, 33, 77, 53, 51, 59, 20, 42, 80, 61, 1, 0, 38, 64, 45, 92, 46, 79, 93, 95, 37, 40, 83, 13, 12, 78, 75, 73, 84, 81, 8, 32, 27, 19, 87, 85, 16, 25, 17, 68, 26, 39, 48, 36};
  int index = 0;
  return sequence[index++] % std::size(sequence);
}
