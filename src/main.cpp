#include <Core/Canvas.h>
#include <Core/Grid.h>
#include <Core/Node.h>
#include <Core/Window.h>
#include <UI/Button.h>

#include <SFML/Graphics.hpp>

int main() {
  Core::Window window(sf::Vector2u(1280, 720),
                      "Algorithm Visualizer - Aru Gyani");

  auto canvas = std::make_shared<Core::Canvas>(
      sf::Vector2f(500, 500), sf::Vector2f(1280 / 2 - 250, 720 / 2 - 250));

  auto grid = std::make_shared<Core::Grid>(sf::Vector2i(13, 13), 15.f, 20.f,
                                           canvas->GetSize());

  canvas->Add(grid);
  window.Add(canvas);

  grid->InitializeAlgorithm();

  window.Run();
}