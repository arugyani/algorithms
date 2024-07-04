#include <Core/Canvas.h>

namespace Core {

Canvas::Canvas(sf::Vector2f size, sf::Vector2f position)
    : size(size), position(position), antialiasing(4) {
  settings.antialiasingLevel = antialiasing;

  renderTexture.create(size.x, size.y, settings);
  renderTexture.setSmooth(true);

  view.setSize(size.x, size.y);

  position = sf::Vector2f(size.x / 2, size.y / 2);
  view.setCenter(size.x / 2, size.y / 2);
}

void Canvas::Update(double deltaTime, sf::RenderWindow& window) {
  renderTexture.clear(sf::Color::White);

  sf::CircleShape shape(50);
  shape.setFillColor(sf::Color::Green);
  shape.setOrigin(sf::Vector2f(shape.getRadius(), shape.getRadius()));
  shape.setPosition(size.x / 2, size.y / 2);
  renderTexture.draw(shape);

  renderTexture.display();
}

void Canvas::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  sf::Sprite sprite(renderTexture.getTexture());
  sprite.setPosition(position);

  target.draw(sprite, states);
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