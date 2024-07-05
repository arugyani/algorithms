#include <Core/Canvas.h>

#include <iostream>

namespace Core {

Canvas::Canvas(sf::Vector2f size, sf::Vector2f position)
    : size(size), position(position), antialiasing(4) {
  settings.antialiasingLevel = antialiasing;

  renderTexture.create(size.x, size.y, settings);
  renderTexture.setSmooth(true);

  view.setSize(size);
  view.setCenter(size.x / 2, size.y / 2);
}

void Canvas::Update(double deltaTime, sf::RenderTarget& target) {
  renderTexture.clear(sf::Color::White);

  UpdateTargets(deltaTime, renderTexture);
  DrawTargets(renderTexture);

  renderTexture.display();
}

void Canvas::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  sf::Sprite sprite(renderTexture.getTexture());
  sprite.setPosition(position);
  target.draw(sprite, states);
}

void Canvas::HandleClick(sf::RenderWindow& window, sf::Vector2i mouse) {
  sf::Vector2i localMouse =
      sf::Vector2i(mouse.x - position.x, mouse.y - position.y);

  for (const auto& t : targets) {
    t->HandleClick(window, localMouse);
  }
}

void Canvas::SetSize(sf::Vector2f size) {
  this->size = size;

  renderTexture.create(size.x, size.y, settings);
  renderTexture.setSmooth(true);

  view.setSize(size.x, size.y);

  SetView(0.f, 0.f);
}

void Canvas::SetView(float x, float y) {
  float centerX = x + (this->size.x / 2);
  float centerY = y + (this->size.y / 2);

  view.setCenter(centerX, centerY);
}

}  // namespace Core