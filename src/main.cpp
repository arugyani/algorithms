#include <Core/Canvas.h>
#include <Core/Grid.h>
#include <Core/Node.h>
#include <Core/Window.h>
#include <UI/Button.h>
#include <UI/Text.h>

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
  grid->InitializeAlgorithm();
  canvas->Add(grid);

  //   auto start = std::make_shared<UI::Button>(sf::Vector2f(20, 20), "Start",
  //                                             window.GetWindow(),
  //                                             [grid]() { grid->Start(); });

  //   auto reset = std::make_shared<UI::Button>(sf::Vector2f(130, 20), "Reset",
  //                                             window.GetWindow(),
  //                                             [grid]() { grid->Reset(); });

  //   auto clear = std::make_shared<UI::Button>(sf::Vector2f(240, 20), "Clear",
  //                                             window.GetWindow(),
  //                                             [grid]() { grid->Clear(); });

  auto algorithm =
      std::make_shared<UI::Text>("Select algorithm", sf::Vector2f(20, 20), 16);
  algorithm->GetLabel().setStyle(sf::Text::Underlined);

  auto dijkstra = std::make_shared<UI::Button>(
      sf::Vector2f(20, 50), "Dijkstra's", window.GetWindow(), []() {});

  auto controls = std::make_shared<UI::Text>("Select action",
                                             sf::Vector2f(20, 720 / 2), 16);
  controls->GetLabel().setStyle(sf::Text::Underlined);

  auto start = std::make_shared<UI::Button>(sf::Vector2f(20, 390), "Start",
                                            window.GetWindow(),
                                            [grid]() { grid->Start(); });

  auto reset = std::make_shared<UI::Button>(sf::Vector2f(130, 390), "Reset",
                                            window.GetWindow(),
                                            [grid]() { grid->Reset(); });

  auto clear = std::make_shared<UI::Button>(sf::Vector2f(240, 390), "Clear",
                                            window.GetWindow(),
                                            [grid]() { grid->Clear(); });

  auto draw = std::make_shared<UI::Button>(
      sf::Vector2f(20, 440), "Draw", window.GetWindow(),
      [grid]() { grid->SetDrawMode(true); });

  auto erase = std::make_shared<UI::Button>(
      sf::Vector2f(130, 440), "Erase", window.GetWindow(),
      [grid]() { grid->SetDrawMode(false); });

  window.Add(canvas);

  window.Add(algorithm);
  window.Add(dijkstra);

  window.Add(controls);
  window.Add(start);
  window.Add(reset);
  window.Add(clear);
  window.Add(draw);
  window.Add(erase);

  window.Run();

  return 0;
}