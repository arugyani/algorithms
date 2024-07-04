#ifndef BUTTON_H
#define BUTTON_H

#include <UI/Renderable.h>

#include <SFML/Graphics.hpp>
#include <functional>
#include <string>

namespace UI {

class Button : public Renderable {
 private:
  sf::RectangleShape container;
  sf::Text label;

  sf::Font font;
  sf::Cursor cursor;

  sf::Color startContainerColor;
  sf::Color endContainerColor;
  sf::Color startTextColor;
  sf::Color endTextColor;

  sf::Vector2f position;
  sf::Vector2f padding;

  sf::FloatRect textBounds;

  std::function<void()> onClick;

  const float MAX_FONT_SIZE = 200.0f;
  const size_t MAX_TEXT_LENGTH = 75;

  float transitionTime;
  float elapsedTime;

  bool hovered;
  bool clicked;
  bool cursorSet;

  int fontSize;

  std::string text;

  bool IsHovered(sf::Vector2i mouse);
  void OnHover(double deltaTime, sf::RenderWindow& window);

  void Initialize(std::string label);
  void PositionShapes();
  void UpdateTextBounds();

  void LoadFont(std::string path);
  void LoadCursor();
  void OnClick();

 public:
  Button();
  Button(sf::Vector2f position, std::string string,
         std::function<void()> onClickCallback);

  void SetPadding(sf::Vector2f padding);
  void SetPosition(sf::Vector2f position);
  void SetFontSize(unsigned int fontSize);
  void SetText(std::string string);

  virtual void Update(double deltaTime, sf::RenderWindow& window) override;

  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;
};

}  // namespace UI

#endif