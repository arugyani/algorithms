#include "Window.h"

#include <iostream>
#include <string>

#include "../UI/Button/Button.h"

namespace Core {

Window::Window(sf::Vector2u size, std::string title)
    : window(sf::VideoMode(size.x, size.y), title) {
  for (int i = 0; i < 15; i++) {
    renderTargets.emplace_back(std::make_shared<UI::Button>(
        sf::Vector2f(100, 10 + (i * 40)), "Hello, world",
        [i]() { std::cout << "Button " << i << " clicked!" << std::endl; }));
  }
}

void Window::Run() {
  double t = 0.0;
  double dt = 1.f / 60.0;

  sf::Time timer = clock.restart();
  double currentTime = timer.asSeconds();

  while (window.isOpen()) {
    sf::Event event;

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }

    double newTime = clock.getElapsedTime().asSeconds();
    double frameTime = newTime - currentTime;
    currentTime = newTime;

    while (frameTime > 0.0) {
      float deltaTime = std::min(frameTime, dt);

      this->Update(deltaTime);

      frameTime -= deltaTime;
      t += deltaTime;
    }

    this->Draw();
  }
}

void Window::Update(double deltaTime) {
  sf::Vector2i mouse = sf::Mouse::getPosition(window);

  for (auto& target : renderTargets) {
    target->Update(deltaTime, mouse, window);
  }
}

void Window::Draw() {
  window.clear(sf::Color(20, 20, 31));

  for (const auto& target : renderTargets) {
    window.draw(*target);
  }

  window.display();
}

}  // namespace Core