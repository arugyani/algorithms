#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "Core/Canvas.h"
#include "Core/Window.h"

void add(int* x, int value) {
  std::cout << *x << std::endl;
  *x += value;
  std::cout << &*x << std::endl;
}

int main() {
  Core::Window window(sf::Vector2u(1280, 720),
                      "Algorithm Visualizer - Aru Gyani");

  auto canvas = std::make_shared<Core::Canvas>(
      sf::Vector2f(500, 500), sf::Vector2f(1280 / 2 - 250, 720 / 2 - 250));

  window.Add(canvas);
  window.Run();
}