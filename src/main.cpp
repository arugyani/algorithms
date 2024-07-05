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

  auto canvas = std::make_shared<Core::Canvas>(sf::Vector2f(720, 720),
                                               sf::Vector2f(1280 - 720, 0));

  auto grid = std::make_shared<Core::Grid>(sf::Vector2i(27, 27), 10.f, 15.f,
                                           canvas->GetSize());

  auto init = std::make_shared<UI::Button>(
      sf::Vector2f(50, 50), "Dijkstra's", window.GetWindow(),
      [grid]() { grid->InitializeAlgorithm(); });

  auto reset = std::make_shared<UI::Button>(sf::Vector2f(50, 100), "Reset",
                                            window.GetWindow(),
                                            [grid]() { grid->Reset(); });

  auto start = std::make_shared<UI::Button>(sf::Vector2f(50, 150), "Start",
                                            window.GetWindow(),
                                            [grid]() { grid->Start(); });

  auto draw = std::make_shared<UI::Button>(
      sf::Vector2f(50, 200), "Draw", window.GetWindow(),
      [grid]() { grid->SetDrawMode(true); });

  auto erase = std::make_shared<UI::Button>(
      sf::Vector2f(170, 200), "Erase", window.GetWindow(),
      [grid]() { grid->SetDrawMode(false); });

  canvas->Add(grid);

  window.Add(canvas);
  window.Add(init);
  window.Add(reset);
  window.Add(start);
  window.Add(draw);
  window.Add(erase);

  window.Run();

  return 0;
}