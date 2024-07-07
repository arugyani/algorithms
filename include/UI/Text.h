#ifndef UI_TEXT_H
#define UI_TEXT_H

#include <UI/Renderable.h>

#include <SFML/Graphics.hpp>
#include <string>

namespace UI {

class Text : public Renderable {
 private:
  sf::Font font;
  sf::Color color;
  sf::Text label;
  sf::Vector2f position;

  std::string text;

  int fontSize;

 public:
  Text(std::string text, sf::Vector2f position, int fontSize);

  sf::Text& GetLabel() { return label; }

  virtual void Update(double deltaTime, sf::RenderTarget& target) override {}

  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;

  virtual void HandleClick(sf::RenderWindow& window,
                           sf::Vector2i mouse) override {}
};

}  // namespace UI

#endif