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

  std::shared_ptr<Node> parent;

  int distance;
  int index;

  float size;
  float transitionTime;
  float elapsedTime;

  bool changeColor;
  bool visited;

  bool isObstacle;
  bool isStart;
  bool isEnd;

  void UpdateColor(double deltaTime);

 public:
  Node(sf::Vector2f position, float size, int index);

  sf::Vector2f GetPosition();
  sf::CircleShape GetShape();
  sf::Color GetColor();

  int GetDistance();
  int GetIndex();

  float GetSize();

  bool GetVisited();
  bool GetStart();
  bool GetEnd();
  bool GetObstacle();

  std::shared_ptr<Node> GetParent() const;

  void SetColor(sf::Color color);
  void SetPosition(sf::Vector2f position);
  void SetSize(float size);
  void SetDistance(int distance);
  void SetVisited(bool visited);
  void SetParent(const std::shared_ptr<Node>& parent);
  void SetStart(bool start);
  void SetEnd(bool end);
  void SetObstacle(bool obstacle);
  void Reset();

  void FadeTo(sf::Color color);

  virtual void Update(double deltaTime, sf::RenderTarget& target) override;

  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;
};

}  // namespace Core

#endif