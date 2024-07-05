#include <Core/Grid.h>
#include <Core/Node.h>

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>

namespace Core {

Grid::Grid(sf::Vector2i size, float nodeSize, float padding,
           sf::Vector2f canvasSize)
    : size(size),
      nodeSize(nodeSize),
      padding(padding),
      stepInterval(0.007f),
      drawMode(true) {
  float totalGridWidth = size.x * nodeSize + (size.x - 1) * padding;
  float totalGridHeight = size.y * nodeSize + (size.y - 1) * padding;

  float startX = (canvasSize.x - totalGridWidth) / 2 - 7.5;
  float startY = (canvasSize.y - totalGridHeight) / 2 - 7.5;

  for (int i = 0; i < size.x; i++) {
    for (int j = 0; j < size.y; j++) {
      sf::Vector2f position(startX + i * (nodeSize + padding),
                            startY + j * (nodeSize + padding));

      int index = i * size.x + j;
      auto node = std::make_shared<Core::Node>(position, nodeSize, index);
      Add(node);
    }
  }

  algorithm = std::make_shared<Core::Algorithm>();
}

std::vector<std::shared_ptr<Core::Node>> Grid::GetTargets() { return targets; }

std::vector<std::shared_ptr<Core::Node>> Grid::GetNeighbors(
    const std::shared_ptr<Core::Node>& node) const {
  std::vector<std::shared_ptr<Core::Node>> neighbors;

  // Get the node index
  int index = node->GetIndex();

  // Calculate the node's x and y position in the 2D grid
  int x = index % size.x;
  int y = index / size.x;

  // Define relative positions of neighbors
  std::vector<sf::Vector2i> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

  for (const auto& dir : directions) {
    int nx = x + dir.x;
    int ny = y + dir.y;

    if (nx >= 0 && nx < size.x && ny >= 0 && ny < size.y) {
      int neighborIndex = ny * size.x + nx;
      neighbors.push_back(
          std::dynamic_pointer_cast<Core::Node>(targets[neighborIndex]));
    }
  }

  return neighbors;
}

void Grid::Reset() {
  algorithm = std::make_shared<Core::Algorithm>();
  start = nullptr;
  end = nullptr;
  drawMode = true;

  for (auto& node : targets) {
    node->Reset();
  }
}

void Grid::InitializeAlgorithm() {
  if (start && end) return;

  srand(time(0));

  if (!targets.empty()) {
    int startX, startY, endX, endY;
    do {
      startX = rand() % size.x;
      startY = rand() % size.y;
      endX = rand() % size.x;
      endY = rand() % size.y;
    } while (std::abs(startX - endX) + std::abs(startY - endY) <
             size.x / 2);  // Ensure they are relatively far

    int startIndex = startY * size.x + startX;
    int endIndex = endY * size.x + endX;

    start = targets[startIndex];
    start->SetStart(true);

    end = targets[endIndex];
    end->SetEnd(true);
  }
}

void Grid::Start() {
  if (!start || !end) return;
  algorithm->Start(start, end);
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

void Grid::SetDrawMode(bool drawMode) {
  this->drawMode = drawMode;
  for (const auto& t : targets) t->SetDrawMode(drawMode);
}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  for (const auto& t : targets) {
    target.draw(*t);
  }
}

void Grid::HandleClick(sf::RenderWindow& window, sf::Vector2i mouse) {
  for (const auto& t : targets) {
    t->HandleClick(window, mouse);
  }
}

}  // namespace Core