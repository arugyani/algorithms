#ifndef CORE_GRID_H
#define CORE_GRID_H

#include <Core/Algorithm.h>
#include <UI/Container.h>
#include <UI/Renderable.h>

#include <SFML/Graphics.hpp>
#include <memory>

namespace Core {

class Algorithm;

class Grid : public UI::Renderable, UI::Container<Core::Node> {
 private:
  sf::Vector2i size;
  sf::Clock clock;

  float nodeSize;
  float padding;
  float stepInterval;

  std::shared_ptr<Core::Algorithm> algorithm;

 public:
  Grid(sf::Vector2i size, float nodeSize, float padding,
       sf::Vector2f canvasSize);

  std::vector<std::shared_ptr<Core::Node>> GetTargets();
  std::vector<std::shared_ptr<Core::Node>> GetNeighbors(
      const std::shared_ptr<Core::Node>& node) const;

  void InitializeAlgorithm();
  void UpdateAlgorithm();
  void Reset();

  virtual void Update(double deltaTime, sf::RenderTarget& target) override;
  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;
};

}  // namespace Core

#endif