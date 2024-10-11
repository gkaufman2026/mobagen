#include "Catcher.h"
#include "World.h"

Point2D Catcher::Move(World* world) {
  std::vector<Point2D> path;
  // Setting the vector based on the maze type
  if (world->getCurrentPath() == World::BFS) {
    path = generateBFSPath(world);
  } else if (world->getCurrentPath() == World::A_STAR) {
    path = generateAStarPath(world);
  }

  if (!path.empty()) { return path[0]; }
  return getVisitableNeighbors(world)[Random::Range(0, getVisitableNeighbors(world).size() - 1)];
}

// Similar to the code created within the Agent class, we are checking what neighboring spaces the cat and making sure that the catcher can find spots that the cat is near
std::vector<Point2D> Catcher::getVisitableNeighbors(World* w) {
  const Point2D catPos = w->getCat();
  int startPoint = catPos.x - static_cast<int>(catPos.y % 2 == 0), i;
  std::vector<Point2D> neighbors;

  // Checking above
  for (i = startPoint; i < startPoint + 2; i++) {
    const Point2D point = {i, catPos.y - 1};
    if (!w->getContent(point)) {
      neighbors.push_back(point);
    }
  }

  // Checking below
  for (i = startPoint; i < startPoint + 2; i++) {
    const Point2D point = {i, catPos.y + 1};
    if (!w->getContent(point)) {
      neighbors.push_back(point);
    }
  }

  // Checking sides
  startPoint = catPos.x - 1;
  for (i = startPoint; i < startPoint + 3; i++) {
    if (i != catPos.x) {
      const Point2D point = {i, catPos.y};
      if (!w->getContent(point)) {
        neighbors.push_back(point);
      }
    }
  }
  return neighbors;
}
