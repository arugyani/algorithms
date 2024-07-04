#include <Core/Algorithm.h>

namespace Core {

Algorithm::Algorithm()
    : pq([](const std::shared_ptr<Core::Node>& a,
            const std::shared_ptr<Core::Node>& b) {
        return a->GetDistance() > b->GetDistance();
      }),
      running(false) {}

void Algorithm::Start(const std::shared_ptr<Core::Node>& startNode) {
  startNode->SetDistance(0);
  pq.push(startNode);
  running = true;
}

void Algorithm::Step(Core::Grid& grid) {
  if (pq.empty()) {
    running = false;
    return;
  }

  auto currentNode = pq.top();
  pq.pop();

  if (currentNode->GetVisited()) return;
  currentNode->SetVisited();

  // Iterate over all neighbors of currentNode
  for (auto& neighbor : grid.GetTargets()) {
    auto node = std::dynamic_pointer_cast<Core::Node>(neighbor);
    if (!node) continue;

    if (node == currentNode || node->GetVisited()) continue;

    // Calculate tentative distance (assuming grid neighbors)
    float distance =
        currentNode->GetDistance() + 1;  // Or use actual distance if different

    if (distance < node->GetDistance()) {
      node->SetDistance(distance);
      pq.push(node);
    }
  }
}

}  // namespace Core
