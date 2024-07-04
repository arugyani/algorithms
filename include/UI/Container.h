#ifndef UI_CONTAINER_H
#define UI_CONTAINER_H

#include <UI/Renderable.h>

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

namespace UI {

class Container {
 protected:
  std::vector<std::shared_ptr<UI::Renderable>> targets;

 public:
  void Add(const std::shared_ptr<UI::Renderable>& target) {
    targets.push_back(target);
  }

  void UpdateTargets(float deltaTime, sf::RenderTarget& target) {
    for (auto& t : targets) {
      t->Update(deltaTime, target);
    }
  }

  void DrawTargets(sf::RenderTarget& target) {
    for (const auto& t : targets) {
      target.draw(*t);
    }
  }
};

}  // namespace UI

#endif