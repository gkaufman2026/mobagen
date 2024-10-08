#ifndef AGENT_H
#define AGENT_H
#include "math/Point2D.h"
#include <unordered_set>
#include <unordered_map>
#include <vector>

class World;

class Agent {
public:
  explicit Agent() = default;

  virtual Point2D Move(World*) = 0;
  std::vector<Point2D> getVisitedNeighbors(World* w, const Point2D& p, std::unordered_set<Point2D> &frontierSet, std::unordered_map<Point2D, bool> &visited);
  std::vector<Point2D> generatePath(World* w);
  bool isCheckPointFound(Point2D checkSpot, World* w, std::unordered_set<Point2D> &frontierSet, std::unordered_map<Point2D, bool> &visited);
};

#endif  // AGENT_H
