#include "Cat.h"
#include "World.h"

Point2D Cat::Move(World* world) {
  std::vector<Point2D> path;
  // Setting the vector based on the maze type
  if (world->getCurrentPath() == World::BFS) {
    path = generateBFSPath(world);
  } else if (world->getCurrentPath() == World::A_STAR) {
    path = generateAStarPath(world);
  }

  if (!path.empty()) {
    return path.back();
  }

  // Updated random system for cat's movement, Tristan gave me jumping off point in class.
  int rand = Random::Range(0, 5);
  Point2D pos = world->getCat();
  std::vector<Point2D> directions = {World::NE(pos), World::NW(pos), World::E(pos), World::W(pos), World::SE(pos), World::SW(pos)};

  if (world->getContent(directions[rand])) {
    for (int i = (rand + 1) % directions.size(); i != rand; i = (i + 1) % directions.size()) {
      if (!world->getContent(directions[i])) {
        return directions[i];
      }
    }
    return Point2D::INFINITE;
  }
  return directions[rand];
}
