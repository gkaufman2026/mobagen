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

  // bootstrap state
  auto catPos = w->getCat();
  frontier.push(catPos);
  frontierSet.insert(catPos);
  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we dont find a border, we have to return random points

  while (!frontier.empty()) {
    const Point2D current = frontier.front();
    frontier.pop();
    frontierSet.erase(current);

    int worldSize = w->getWorldSideSize() / 2;
    if (abs(current.x) == worldSize || abs(current.y) == worldSize) {
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
    // Ran into issues with previous while loop. Since this code is building the border for the cat, I went researching into alternatives with loops and found "custom" iterator for loops
    // https://stackoverflow.com/questions/8164567/how-to-make-my-custom-type-to-work-with-range-based-for-loops
    // Where it gave me an idea to condense the code within the for loop to check that the current != catPos and setting the current by the cameFrom array
    // And then just adding the current to the path vector
    for (Point2D currentHex = borderExit; currentHex != catPos; currentHex = cameFrom[currentHex]) {
      path.push_back(currentHex);
    }
  }
  return path;
}

// Not sure if this counts toward "extra", but created a bool function that returns if the point meets the conditions depending on the frontierSet, visited and world conditions
// Assumed something like this might be viable in varying maze algorithms and wanted to provide a way that would allow all algorithms to have a universal condition.
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
