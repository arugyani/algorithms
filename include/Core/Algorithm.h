#ifndef CORE_ALGORITHM_H
#define CORE_ALGORITHM_H

#include <Core/Grid.h>
#include <Core/Node.h>

#include <SFML/Graphics.hpp>
#include <memory>
#include <queue>

namespace Core {

class Grid;

class Algorithm {
 private:
  std::priority_queue<std::shared_ptr<Core::Node>,
                      std::vector<std::shared_ptr<Core::Node>>,
                      std::function<bool(const std::shared_ptr<Core::Node>&,
                                         const std::shared_ptr<Core::Node>&)>>
      pq;

  bool running;

 public:
  Algorithm();

  bool IsRunning() const { return running; }

  void Start(const std::shared_ptr<Node>& startNode);
  void Step(Grid& grid);
};

}  // namespace Core

#endif