#include "Agent.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "World.h"
using namespace std;

std::vector<Point2D> Agent::generatePath(World* w) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  queue<Point2D> frontier;                   // to store next ones to visit
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results
  vector<Point2D> path, neighbors;

  // bootstrap state
  auto catPos = w->getCat();
  frontier.push(catPos);
  frontierSet.insert(catPos);
  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we dont find a border, we have to return random points

  while (!frontier.empty()) {
    Point2D current = frontier.front();
    frontierSet.erase(current);
    frontier.pop();
    visited[current] = true;
    neighbors = getVisitedNeighbors(w, current, frontierSet, visited);
    for (auto neighbor : neighbors) {
      cameFrom[neighbor] = current;
      frontierSet.insert(neighbor);
      frontier.push(neighbor);
    }
  }

  if (borderExit != Point2D::INFINITE) {
    Point2D current = borderExit;
    while (current != catPos) {
      current = cameFrom[current];
      path.push_back(current);
    }
  }

  return path;
}

bool Agent::isCheckPointFound(Point2D check, World* w, std::unordered_set<Point2D>& frontierSet, std::unordered_map<Point2D, bool>& visited) {
  return !visited.contains(check) && w->getCat() != check && !frontierSet.contains(check) && !w->getContent(check);
}

std::vector<Point2D> Agent::getVisitedNeighbors(World* w, const Point2D& p, unordered_set<Point2D>& frontierSet, unordered_map<Point2D, bool>& visited) {
  int startPoint = p.x - static_cast<int>(p.y % 2 == 0);
  std::vector<Point2D> neighbors;

  // Checking above
  for (int i = startPoint; i < startPoint + 2; i++) {
    const Point2D checkSpot = {i, p.y - 1};
    if (isCheckPointFound(checkSpot, w, frontierSet, visited)) {
      neighbors.push_back(checkSpot);
    }
  }

  // Checking below
  for (int i = startPoint; i < startPoint + 2; i++) {
    const Point2D checkSpot = {i, p.y + 1};
    if (isCheckPointFound(checkSpot, w, frontierSet, visited)) {
      neighbors.push_back(checkSpot);
    }
  }

  // Checking sides
  startPoint = p.x - 1;
  for (int i = startPoint; i < startPoint + 3; i++) {
    if (i != p.x) {
      const Point2D checkSpot = {i, p.y};
      if (isCheckPointFound(checkSpot, w, frontierSet, visited)) {
        neighbors.push_back(checkSpot);
      }
    }
  }

  return neighbors;
}
