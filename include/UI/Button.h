#ifndef BUTTON_H
#define BUTTON_H

#include <UI/Renderable.h>

#include <SFML/Graphics.hpp>
#include <functional>
#include <string>

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
  void OnHovered(double deltaTime, const sf::Vector2i& mouse,
                 sf::RenderWindow& window);

  sf::Color LerpColor(const sf::Color& start, const sf::Color& end, double t);

 public:
  /**
   * \brief Button constructor
   * \param position Position relative to screen
   * \param label Text displayed inside button
   */
  Button(sf::Vector2f position, std::string label,
         std::function<void()> onClickCallback);

  virtual void Update(double deltaTime, sf::RenderWindow& window) override;
  void Update(double deltaTime, const sf::Vector2i& mouse,
              sf::RenderWindow& window);

  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;

  void OnClick();

  bool hovered;
};

}  // namespace UI

#endif