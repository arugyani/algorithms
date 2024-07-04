#ifndef WINDOW_H
#define WINDOW_H

#include <UI/Renderable.h>

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

namespace Core {

class Window {
 private:
  sf::RenderWindow window;
  std::vector<std::shared_ptr<UI::Renderable>> targets;

  sf::Clock clock;
  constexpr static float dt =
      1.f / 60.0;  // time interval between current frame & previous frame
  float t;         // total running time of the application

  void HandleEvents();
  void UpdateLoop(float& currentTime);

  void Update(float deltaTime);
  void Draw();

 public:
  Window();
  explicit Window(const sf::Vector2u& size, const std::string& title);

  void Run();

  void Add(const std::shared_ptr<UI::Renderable>& target);
};

}  // namespace Core

#endif