#ifndef CORE_NODE_H
#define CORE_NODE_H

#include <UI/Renderable.h>

#include <SFML/Graphics.hpp>

namespace Core {

class Node : public UI::Renderable {
 private:
  sf::Vector2f position;
  sf::CircleShape shape;

  sf::Color color;
  sf::Color newColor;

  float size;
  float transitionTime;
  float elapsedTime;
  float distance;

  bool changeColor;
  bool visited;

  void UpdateColor(double deltaTime);

 public:
  Node(sf::Vector2f position, float size);

  sf::Vector2f GetPosition();
  sf::CircleShape GetShape();
  sf::Color GetColor();

  float GetSize();
  float GetDistance();

  bool GetVisited();

  void SetColor(sf::Color color);
  void SetPosition(sf::Vector2f position);
  void SetSize(float size);
  void SetDistance(int distance);
  void SetVisited();

  void FadeTo(sf::Color color);

  virtual void Update(double deltaTime, sf::RenderTarget& target) override;

  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;
};

}  // namespace Core

#endif