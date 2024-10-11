#include "Agent.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "World.h"
using namespace std;

std::vector<Point2D> Agent::generateBFSPath(World* w) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  queue<Point2D> frontier;                   // to store next ones to visit
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results

  // bootstrap state
  auto catPos = w->getCat();
  frontier.push(catPos);
  frontierSet.insert(catPos);
  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we dont find a border, we have to return random points

  while (!frontier.empty()) {
    const Point2D current = frontier.front();
    frontier.pop();
    frontierSet.erase(current);

    const int worldSize = w->getWorldSideSize() / 2;
    if (current == worldSize) {
      borderExit = current;
      break;
    }

    visited[current] = true;
    const vector<Point2D> neighbors = getVisitedNeighbors(w, current, frontierSet, visited);
    if (!neighbors.empty()) {
      for (const auto& neighbor : neighbors) {
        cameFrom[neighbor] = current;
        frontier.push(neighbor);
        frontierSet.insert(neighbor);
      }
    }
  }

  vector<Point2D> path;
  if (borderExit != Point2D::INFINITE) {
    for (Point2D currentHex = borderExit; currentHex != catPos; currentHex = cameFrom[currentHex]) {
      path.push_back(currentHex);
    }
  }
  return path;
}

std::vector<Point2D> Agent::generateAStarPath(World* w) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  priority_queue<ASNode> frontier;           // to store next ones to visit
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element don't exist [] will give you wrong results

  // bootstrap state
  auto startPos = ASNode(w->getCat());

  frontier.push(startPos);
  frontierSet.insert(startPos.point);
  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we don't find a border, we have to return random points

  while (!frontier.empty()) {
    const ASNode current = frontier.top();
    frontier.pop();
    frontierSet.erase(current.point);

    const int worldSize = w->getWorldSideSize() / 2;
    // Created operator overload for == inside Point2D to clean up clutter and to make it clear that the point is
    // being compared to another Point2D (worldSize) rather than calculating each axis' absolute value individually
    if (current.point == worldSize) {
      borderExit = current.point;
      break;
    }

    visited[current.point] = true;
    const vector<Point2D> neighbors = getVisitedNeighbors(w, current.point, frontierSet, visited);
    if (!neighbors.empty()) {
      for (const auto& neighbor : neighbors) {
        cameFrom[neighbor] = current.point;

        auto newNeighbor = ASNode(neighbor);
        newNeighbor.heuristic = ASNode::calculateHeuristic(startPos.point, worldSize); // done in class
        newNeighbor.weight = current.weight + 1;

        frontier.push(newNeighbor);
        frontierSet.insert(neighbor);
      }
    }
  }

  vector<Point2D> path;
  if (borderExit != Point2D::INFINITE) {
    // Ran into issues with the recommended while loop, so I converted system to be a for loop, where it parses through each of
    // the borderExits and checks that it isn't the cat's starting position and adds the currentHexagon to the vector
    for (Point2D currentHex = borderExit; currentHex != startPos.point; currentHex = cameFrom[currentHex]) {
      path.push_back(currentHex);
    }
  }
  return path;
}

// Not sure if this counts toward "extra", but created a boolean function that returns if the point meets the conditions
// depending on the frontierSet, visited and world conditions Assumed something like this might be viable
// in varying maze algorithms and wanted to provide a way that would allow all algorithms to have a universal condition.
bool Agent::isCheckPointFound(Point2D point, World* w, std::unordered_set<Point2D>& frontierSet, std::unordered_map<Point2D, bool>& visited) {
  return !visited.contains(point) && w->getCat() != point && !frontierSet.contains(point) && !w->getContent(point);
}

std::vector<Point2D> Agent::getVisitedNeighbors(World* w, const Point2D& p, unordered_set<Point2D>& frontierSet, unordered_map<Point2D, bool>& visited) {
  int startPoint = p.x - static_cast<int>(p.y % 2 == 0), i;
  vector<Point2D> neighbors;

  // Checking above
  for (i = startPoint; i < startPoint + 2; i++) {
    const Point2D point = {i, p.y - 1};
    if (isCheckPointFound(point, w, frontierSet, visited)) {
      neighbors.push_back(point);
    }
  }

  // Checking below
  for (i = startPoint; i < startPoint + 2; i++) {
    const Point2D point = {i, p.y + 1};
    if (isCheckPointFound(point, w, frontierSet, visited)) {
      neighbors.push_back(point);
    }
  }

  // Checking sides
  startPoint = p.x - 1;
  for (i = startPoint; i < startPoint + 3; i++) { // increased radius
    if (i != p.x) {
      const Point2D point = {i, p.y};
      if (isCheckPointFound(point, w, frontierSet, visited)) {
        neighbors.push_back(point);
      }
    }
  }
  return neighbors;
}
