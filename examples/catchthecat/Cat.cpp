#include "Cat.h"
#include "World.h"

Point2D Cat::Move(World* world) {
  std::vector<Point2D> path;
  if (world->getCurrentPath() == 0) {
    path = generateBFSPath(world);
  } else if (world->getCurrentPath() == 1){
    path = generateAStarPath(world);
  }

  if (!path.empty()) {
    return path[path.size() - 1];
  }

  auto rand = Random::Range(0, 5);
  auto pos = world->getCat();
  switch (rand) {
    case 0:
      return World::NE(pos);
    case 1:
      return World::NW(pos);
    case 2:
      return World::E(pos);
    case 3:
      return World::W(pos);
    case 4:
      return World::SW(pos);
    case 5:
      return World::SE(pos);
    default:
      throw "random out of range";
  }
}
