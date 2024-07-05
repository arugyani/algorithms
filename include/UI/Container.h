#ifndef UI_CONTAINER_H
#define UI_CONTAINER_H

#include <Core/Node.h>
#include <UI/Renderable.h>

#include <SFML/Graphics.hpp>
#include <memory>
#include <type_traits>
#include <vector>

namespace UI {

template <typename T>
using IsRenderable = std::enable_if_t<std::is_base_of_v<UI::Renderable, T>>;

template <typename T, typename = IsRenderable<T>>
class Container {
 protected:
  std::vector<std::shared_ptr<T>> targets;

 public:
  std::vector<std::shared_ptr<T>> GetTargets();

  void Add(const std::shared_ptr<T>& target) { targets.push_back(target); }

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