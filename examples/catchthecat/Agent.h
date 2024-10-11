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
    static int calculateHeuristic(const Point2D p, int sideOverHalf) {
      if (p.x - p.y > 0 && p.x + p.y > 0) { return sideOverHalf - p.x; }
      else if (p.x - p.y < 0 && p.x + p.y > 0) { return sideOverHalf - p.y; }
      else if (p.x - p.y < 0 && p.x + p.y < 0) { return p.x - sideOverHalf; }
      return p.y - sideOverHalf;
    }
  };

  virtual Point2D Move(World*) = 0;
  std::vector<Point2D> getVisitedNeighbors(World* w, const Point2D& p, std::unordered_set<Point2D> &frontierSet, std::unordered_map<Point2D, bool> &visited);
  std::vector<Point2D> generateAStarPath(World* w);
  std::vector<Point2D> generateBFSPath(World* w);
  bool isCheckPointFound(Point2D checkSpot, World* w, std::unordered_set<Point2D> &frontierSet, std::unordered_map<Point2D, bool> &visited);
};

#endif  // AGENT_H
