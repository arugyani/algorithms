#include <Core/Node.h>
#include <UI/Renderable.h>

#include <iostream>

namespace Core {

Node::Node(sf::Vector2f position, float size, int index)
    : position(position),
      size(size),
      index(index),
      color(sf::Color::White),
      newColor(sf::Color::White),
      transitionTime(1.f),
      elapsedTime(0.0f),
      changeColor(false),
      distance(INT_MAX),
      visited(false),
      isObstacle(false),
      isStart(false),
      isEnd(false),
      parent(nullptr) {
  shape.setRadius(size);
  shape.setPosition(position);
  shape.setFillColor(color);
  shape.setOutlineColor(sf::Color::Black);
  shape.setOutlineThickness(1);
}

void Node::SetColor(sf::Color color) {
  this->color = color;
  shape.setFillColor(color);
}

void Node::SetPosition(sf::Vector2f position) {
  this->position = position;
  shape.setPosition(position);
}

void Node::SetSize(float size) {
  this->size = size;
  shape.setRadius(size);
}

void Node::SetDistance(int distance) {
  this->distance = distance;

  if (!isStart && !isEnd && !isObstacle) {
    FadeTo(sf::Color(250, 201, 55, 125));
  }
}

void Node::SetVisited(bool visited) {
  this->visited = visited;

  if (!isStart && !isEnd && !isObstacle) {
    FadeTo(sf::Color(62, 155, 237));
  }
}

void Node::SetStart(bool isStart) {
  this->isStart = isStart;
  FadeTo(sf::Color(62, 237, 88));
}

void Node::SetEnd(bool isEnd) {
  this->isEnd = isEnd;
  FadeTo(sf::Color(237, 85, 62));
}

void Node::SetObstacle(bool isObstacle) {
  this->isObstacle = isObstacle;
  FadeTo(sf::Color(31, 32, 33));
}

void Node::SetParent(const std::shared_ptr<Node>& parent) {
  this->parent = parent;
}

sf::Vector2f Node::GetPosition() { return position; }
sf::CircleShape Node::GetShape() { return shape; }
sf::Color Node::GetColor() { return color; }

std::shared_ptr<Node> Node::GetParent() const { return parent; }

int Node::GetDistance() { return distance; }
int Node::GetIndex() { return index; }

float Node::GetSize() { return size; }

bool Node::GetVisited() { return visited; }
bool Node::GetStart() { return isStart; }
bool Node::GetEnd() { return isEnd; }
bool Node::GetObstacle() { return isObstacle; }

void Node::FadeTo(sf::Color color) {
  newColor = color;
  changeColor = true;
}

void Node::Update(double deltaTime, sf::RenderTarget& target) {
  UpdateColor(deltaTime);
}

void Node::UpdateColor(double deltaTime) {
  if (changeColor) {
    if (elapsedTime < transitionTime) {
      elapsedTime += deltaTime;

      double t = elapsedTime / transitionTime;

      sf::Color interpolatedColor =
          UI::Renderable::LerpColor(color, newColor, t);

      shape.setFillColor(interpolatedColor);

      if (elapsedTime > transitionTime) {
        elapsedTime = transitionTime;
      }
    } else {
      SetColor(newColor);
      changeColor = false;
      elapsedTime = 0.f;
    }
  }
}

void Node::Reset() {
  distance = INT_MAX;
  visited = false;
  isStart = false;
  isEnd = false;
  isObstacle = false;
  parent = nullptr;
  shape.setFillColor(sf::Color::White);
}

void Node::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(shape, states);
}

}  // namespace Core