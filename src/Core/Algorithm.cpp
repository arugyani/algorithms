#include <Core/Algorithm.h>

#include <iostream>

namespace Core {

Algorithm::Algorithm()
    : isRunning(false), priorityQueue(Algorithm::ComparisonFunc) {}

bool Algorithm::ComparisonFunc(const std::shared_ptr<Node>& a,
                               const std::shared_ptr<Node>& b) {
  return a->GetDistance() > b->GetDistance();
}

bool Algorithm::IsRunning() { return isRunning; }

void Algorithm::Start(const std::shared_ptr<Node>& startNode,
                      const std::shared_ptr<Node>& endNode) {
  startNode->SetDistance(0);
  this->endNode = endNode;

  priorityQueue.push(startNode);
  isRunning = true;
}

void Algorithm::Step(Grid& grid) {
  if (priorityQueue.empty()) {
    isRunning = false;
    return;
  }

  auto currentNode = priorityQueue.top();
  priorityQueue.pop();

  if (currentNode->GetVisited()) return;
  currentNode->SetVisited(true);

  if (currentNode == endNode) {
    isRunning = false;
    TracePath(currentNode);
    return;
  }

  auto neighbors = grid.GetNeighbors(currentNode);
  for (auto& neighbor : neighbors) {
    if (neighbor->GetVisited() || neighbor->GetObstacle()) continue;

    float distance = currentNode->GetDistance() + 1;

    if (distance < neighbor->GetDistance()) {
      neighbor->SetDistance(distance);
      neighbor->SetParent(currentNode);
      priorityQueue.push(neighbor);
    }
  }
}

void Algorithm::TracePath(const std::shared_ptr<Node>& endNode) {
  auto currentNode = endNode;
  while (currentNode != nullptr) {
    if (!currentNode->GetStart() && !currentNode->GetEnd())
      currentNode->FadeTo(sf::Color(129, 244, 129));
    currentNode = currentNode->GetParent();
  }
}

}  // namespace Core
