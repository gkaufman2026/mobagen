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
  struct ASNode {
    ASNode(Point2D startingPoint) : point(startingPoint){};
    ASNode() = default;
    Point2D point;
    int heuristic, weight;
    bool operator < (const ASNode &rhs) const { return weight + heuristic > rhs.weight + rhs.heuristic; }
  };

  virtual Point2D Move(World*) = 0;
  std::vector<Point2D> getVisitedNeighbors(World* w, const Point2D& p, std::unordered_set<Point2D> &frontierSet, std::unordered_map<Point2D, bool> &visited);
  std::vector<Point2D> generateAStarPath(World* w);
  std::vector<Point2D> generateBFSPath(World* w);
  bool isCheckPointFound(Point2D checkSpot, World* w, std::unordered_set<Point2D> &frontierSet, std::unordered_map<Point2D, bool> &visited);
  Point2D probableExit(const Point2D &p, int sideSize);
};

#endif  // AGENT_H
