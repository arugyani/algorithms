#ifndef CORE_WINDOW_H
#define CORE_WINDOW_H

#include <UI/Container.h>
#include <UI/Renderable.h>

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

namespace Core {

class Window : public UI::Container<UI::Renderable> {
 private:
  sf::RenderWindow window;

  sf::Clock clock;
  constexpr static float dt =
      1.f / 60.0;  // time interval between current frame & previous frame
  float t;         // total running time of the application

  void HandleEvents();
  void HandleClicks();
  void UpdateLoop(float& currentTime);

  void Update(float deltaTime);
  void Draw();

 public:
  Window();
  explicit Window(const sf::Vector2u& size, const std::string& title);

  void Run();
  sf::RenderWindow& GetWindow() { return window; }
};

}  // namespace Core

#endif