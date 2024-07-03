#include <SFML/Graphics.hpp>

#include "Window/Window.h"

int main() {
  Core::Window window(sf::Vector2u(1280, 720),
                      "Algorithm Visualizer - Aru Gyani");

  window.Run();

  return 0;
}