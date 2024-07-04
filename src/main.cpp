#include <Core/Canvas.h>
#include <Core/Node.h>
#include <Core/Window.h>
#include <UI/Button.h>

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <string>

void add(int* x, int value) {
  std::cout << *x << std::endl;
  *x += value;
  std::cout << &*x << std::endl;
}

void OnClick(std::shared_ptr<Core::Node> node) {
  sf::Color color = node->GetColor();

  if (color == sf::Color(230, 53, 44))
    node->FadeTo(sf::Color(230, 189, 44));
  else
    node->FadeTo(sf::Color(230, 53, 44));
}

int main() {
  Core::Window window(sf::Vector2u(1280, 720),
                      "Algorithm Visualizer - Aru Gyani");

  auto canvas = std::make_shared<Core::Canvas>(
      sf::Vector2f(500, 500), sf::Vector2f(1280 / 2 - 250, 720 / 2 - 250));

  float nodeSize = 15.f;
  float padding = 20.f;

  int gridWidth = 13;
  int gridHeight = 13;

  float totalGridWidth = gridWidth * nodeSize + (gridWidth - 1) * padding;
  float totalGridHeight = gridHeight * nodeSize + (gridHeight - 1) * padding;

  float startX = (canvas->GetSize().x - totalGridWidth) / 2 - padding / 2;
  float startY = (canvas->GetSize().y - totalGridHeight) / 2 - padding / 2;

  for (int i = 0; i < gridWidth; i++) {
    for (int j = 0; j < gridHeight; j++) {
      sf::Vector2f position(startX + i * (nodeSize + padding),
                            startY + j * (nodeSize + padding));

      auto node = std::make_shared<Core::Node>(position, nodeSize);
      canvas->Add(node);
    }
  }

  window.Add(canvas);

  window.Run();
}