#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

namespace UI {

class Button : public sf::Drawable {
 private:
  sf::Vector2f position;
  sf::RectangleShape container;

  sf::Text text;
  sf::Font font;

  sf::Cursor cursor;
  bool cursorSet;

  sf::Color startContainerColor;
  sf::Color endContainerColor;
  sf::Color startTextColor;
  sf::Color endTextColor;

  float transitionTime;
  float elapsedTime;

  bool IsHovered(sf::Vector2i mouse);
  void OnClick();

  sf::Color lerpColor(const sf::Color& start, const sf::Color& end, double t);

 public:
  Button(sf::Vector2f position, std::string label);

  void Update(double deltaTime, sf::Vector2i mouse, sf::RenderWindow& window);
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  bool hovered;
};

}  // namespace UI

#endif