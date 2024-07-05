#ifndef CORE_ALGORITHM_H
#define CORE_ALGORITHM_H

#include <Core/Grid.h>
#include <Core/Node.h>

#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>
#include <queue>
#include <vector>

namespace Core {

class Grid;

class Algorithm {
 private:
  std::priority_queue<std::shared_ptr<Core::Node>,
                      std::vector<std::shared_ptr<Core::Node>>,
                      std::function<bool(const std::shared_ptr<Core::Node>&,
                                         const std::shared_ptr<Core::Node>&)>>
      priorityQueue;

  bool isRunning;
  std::shared_ptr<Core::Node> endNode;

 public:
  Algorithm();

  bool IsRunning();

  void Start(const std::shared_ptr<Node>& startNode,
             const std::shared_ptr<Node>& endNode);
  void Step(Grid& grid);
  void TracePath(const std::shared_ptr<Node>& endNode);

  static bool ComparisonFunc(const std::shared_ptr<Node>& a,
                             const std::shared_ptr<Node>& b);
};

}  // namespace Core

#endif