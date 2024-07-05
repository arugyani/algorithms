#include <Core/Canvas.h>
#include <Core/Grid.h>
#include <Core/Node.h>
#include <Core/Window.h>
#include <UI/Button.h>

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

int main() {
  Core::Window window(sf::Vector2u(1280, 720),
                      "Algorithm Visualizer - Aru Gyani");

  auto canvas = std::make_shared<Core::Canvas>(
      sf::Vector2f(500, 500), sf::Vector2f(1280 / 2 - 250, 720 / 2 - 250));

  auto grid = std::make_shared<Core::Grid>(sf::Vector2i(13, 13), 15.f, 20.f,
                                           canvas->GetSize());

  auto button = std::make_shared<UI::Button>(
      sf::Vector2f(100, 50), "Start Dijkstra's", window.GetWindow(),
      [grid]() { grid->InitializeAlgorithm(); });

  canvas->Add(grid);
  window.Add(canvas);
  window.Add(button);

  window.Run();

  return 0;
}