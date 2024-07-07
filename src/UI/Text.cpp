#include <UI/Text.h>

#include <SFML/Graphics.hpp>
#include <string>

namespace UI {

Text::Text(std::string text, sf::Vector2f position, int fontSize)
    : text(text), fontSize(fontSize), color(sf::Color(31, 32, 33)) {
  if (!font.loadFromFile("assets/arial.ttf")) {
    throw std::runtime_error("Couldn't load text font!");
  }

  label.setString(text);
  label.setFont(font);
  label.setPosition(position);
  label.setCharacterSize(fontSize);
  label.setFillColor(color);
}

void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(label, states);
}

}  // namespace UI