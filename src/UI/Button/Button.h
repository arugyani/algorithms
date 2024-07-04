#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <string>

#include "../Renderable/Renderable.h"

namespace UI {

class Button : public Renderable {
 private:
  sf::Vector2f position;
  sf::RectangleShape container;

  sf::Text text;
  sf::Font font;

  sf::Cursor cursor;
  bool cursorSet;

  bool clicked;
  std::function<void()> callback;

  sf::Color startContainerColor;
  sf::Color endContainerColor;
  sf::Color startTextColor;
  sf::Color endTextColor;

  float transitionTime;
  float elapsedTime;

  bool IsHovered(sf::Vector2i mouse);

  sf::Color lerpColor(const sf::Color& start, const sf::Color& end, double t);

 public:
  /**
   * \brief Button constructor
   * \param position Position relative to screen
   * \param label Text displayed inside button
   */
  Button(sf::Vector2f position, std::string label,
         std::function<void()> onClickCallback);

  void Update(double deltaTime, const sf::Vector2i& mouse,
              sf::RenderWindow& window) override;
  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;

  void OnClick();

  bool hovered;
};

}  // namespace UI

#endif