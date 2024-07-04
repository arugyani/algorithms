#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "Core/Window.h"
#include "UI/Button.h"

void add(int* x, int value) {
  std::cout << *x << std::endl;
  *x += value;
  std::cout << &*x << std::endl;
}

int main() {
  Core::Window window(sf::Vector2u(1280, 720),
                      "Algorithm Visualizer - Aru Gyani");

  auto button = std::make_shared<UI::Button>(
      sf::Vector2f(100, 50), "Hello, world!",
      []() { std::cout << "Hello, world!" << std::endl; });

  window.Add(button);
  window.Run();
}