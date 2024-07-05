#include "Core/Window.h"

#include <iostream>

#include "UI/Button.h"
#include "UI/Renderable.h"

namespace Core {

Window::Window(const sf::Vector2u& size, const std::string& title)
    : window(sf::VideoMode(size.x, size.y), title), t(0.0f) {}

void Window::Run() {
  float t = 0.0;
  float currentTime = clock.getElapsedTime().asSeconds();

  while (window.isOpen()) {
    HandleEvents();
    UpdateLoop(currentTime);
    Draw();
  }
}

void Window::Update(float deltaTime) { UpdateTargets(deltaTime, window); }

void Window::Draw() {
  window.clear(sf::Color(20, 20, 31));

  DrawTargets(window);

  window.display();
}

void Window::HandleEvents() {
  sf::Event event;

  while (window.pollEvent(event)) {
    switch (event.type) {
      case sf::Event::Closed:
        window.close();
      default:
        break;
    }
  }
}

void Window::UpdateLoop(float& currentTime) {
  float newTime = clock.getElapsedTime().asSeconds();
  float frameTime = newTime - currentTime;
  currentTime = newTime;

  while (frameTime > 0.0) {
    float deltaTime = std::min(frameTime, dt);

    Update(deltaTime);

    frameTime -= deltaTime;
    t += deltaTime;
  }
}

}  // namespace Core