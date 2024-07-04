#include <Core/Node.h>
#include <UI/Renderable.h>

#include <iostream>

namespace Core {

Node::Node(sf::Vector2f position, float size)
    : position(position),
      size(size),
      color(sf::Color::White),
      newColor(sf::Color::White),
      transitionTime(1.f),
      elapsedTime(0.0f),
      changeColor(false),
      distance(INFINITY),
      visited(false) {
  shape.setRadius(size);
  shape.setPosition(position);
  shape.setFillColor(color);
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
  FadeTo(sf::Color(224, 217, 67));
}

void Node::SetVisited() {
  visited = true;
  FadeTo(sf::Color(47, 194, 71));
}

sf::Vector2f Node::GetPosition() { return position; }

sf::CircleShape Node::GetShape() { return shape; }
sf::Color Node::GetColor() { return color; }
float Node::GetSize() { return size; }
float Node::GetDistance() { return distance; }
bool Node::GetVisited() { return visited; }

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

void Node::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(shape, states);
}

}  // namespace Core