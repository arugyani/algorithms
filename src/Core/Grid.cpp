#include <Core/Grid.h>
#include <Core/Node.h>

#include <memory>

namespace Core {

Grid::Grid(sf::Vector2i size, float nodeSize, float padding,
           sf::Vector2f canvasSize)
    : size(size), nodeSize(nodeSize), padding(padding), stepInterval(0.1f) {
  float totalGridWidth = size.x * nodeSize + (size.x - 1) * padding;
  float totalGridHeight = size.y * nodeSize + (size.y - 1) * padding;

  float startX = (canvasSize.x - totalGridWidth) / 2 - 7.5;
  float startY = (canvasSize.y - totalGridHeight) / 2 - 7.5;

  for (int i = 0; i < size.x; i++) {
    for (int j = 0; j < size.y; j++) {
      sf::Vector2f position(startX + i * (nodeSize + padding),
                            startY + j * (nodeSize + padding));

      auto node = std::make_shared<Core::Node>(position, nodeSize);
      Add(node);
    }
  }

  algorithm = std::make_shared<Core::Algorithm>();
}

std::vector<std::shared_ptr<UI::Renderable>> Grid::GetTargets() {
  return targets;
}

void Grid::InitializeAlgorithm() {
  if (!targets.empty()) {
    auto node = std::dynamic_pointer_cast<Core::Node>(targets[20]);
    if (!node) throw std::runtime_error("Grid targets must be nodes!");

    algorithm->Start(node);
  }
}

void Grid::UpdateAlgorithm() {
  if (algorithm && algorithm->IsRunning()) {
    if (clock.getElapsedTime().asSeconds() >= stepInterval) {
      algorithm->Step(*this);
      clock.restart();
    }
  }
}

void Grid::Update(double deltaTime, sf::RenderTarget& target) {
  UpdateTargets(deltaTime, target);
  UpdateAlgorithm();
}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  for (const auto& t : targets) {
    target.draw(*t);
  }
}

}  // namespace Core