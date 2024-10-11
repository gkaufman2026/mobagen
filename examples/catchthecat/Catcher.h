#ifndef CATCHER_H
#define CATCHER_H

#include "Agent.h"

class Catcher : public Agent {
public:
  explicit Catcher() : Agent(){};
  Point2D Move(World*) override;
  std::vector<Point2D> getVisitableNeighbors(World* w);
};

#endif  // CATCHER_H
