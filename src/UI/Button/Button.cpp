#include "Button.h"

#include <functional>
#include <iostream>

namespace UI {

Button::Button(sf::Vector2f position, std::string label,
               std::function<void()> onClickCallback)
    : transitionTime(0.1f),
      elapsedTime(0.0f),
      hovered(false),
      cursorSet(false),
      clicked(false),
      callback(onClickCallback) {
  this->position = position;

  if (!font.loadFromFile("assets/arial.ttf")) {
    std::cerr << "Could not load \"" << "assets/arial.ttf" << "\" font!"
              << std::endl;
    exit(1);
  }

  if (!cursor.loadFromSystem(sf::Cursor::Hand)) {
    std::cerr << "Could not load hand cursor!" << std::endl;
    exit(1);
  }

  startContainerColor = sf::Color(255, 255, 255);
  endContainerColor = sf::Color(31, 32, 33);
  startTextColor = sf::Color(31, 32, 33);
  endTextColor = sf::Color(255, 255, 255);

  text.setFont(font);
  text.setString(label);
  text.setCharacterSize(15);
  text.setFillColor(startTextColor);

  sf::FloatRect textBounds = text.getLocalBounds();

  float xPadding = 24.f, yPadding = 24.f;
  float containerWidth = std::max(100.f, textBounds.width + xPadding);
  float containerHeight = textBounds.height + yPadding;

  container.setSize(sf::Vector2f(containerWidth, containerHeight));
  container.setFillColor(startContainerColor);

  text.setOrigin(sf::Vector2f(textBounds.left + textBounds.width / 2.f,
                              textBounds.top + textBounds.height / 2.f));
  text.setPosition(sf::Vector2f(position.x + containerWidth / 2.f,
                                position.y + containerHeight / 2.f));

  container.setPosition(sf::Vector2f(position.x, position.y));
}

void Button::Update(double deltaTime, const sf::Vector2i& mouse,
                    sf::RenderWindow& window) {
  hovered = IsHovered(mouse);

  if (hovered) {
    if (!cursorSet) {
      window.setMouseCursor(cursor);
      cursorSet = true;
    }

    if (elapsedTime < transitionTime) {
      elapsedTime += deltaTime;
      if (elapsedTime > transitionTime) {
        elapsedTime = transitionTime;
      }
    }
  } else {
    if (cursorSet) {
      window.setMouseCursor(sf::Cursor());
      cursorSet = false;
    }

    if (elapsedTime > 0) {
      elapsedTime -= deltaTime;
      if (elapsedTime < 0) {
        elapsedTime = 0;
      }
    }
  }

  double t = elapsedTime / transitionTime;

  sf::Color currentContainerColor =
      lerpColor(startContainerColor, endContainerColor, t);
  sf::Color currentTextColor = lerpColor(startTextColor, endTextColor, t);

  // Apply interpolated colors
  container.setFillColor(currentContainerColor);
  text.setFillColor(currentTextColor);

  // Detect click event
  bool isMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
  if (hovered && isMousePressed && !clicked) {
    OnClick();
  }
  clicked = isMousePressed;
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(container, states);
  target.draw(text, states);
}

bool Button::IsHovered(sf::Vector2i mouse) {
  if (mouse.x < position.x || mouse.x > position.x + container.getSize().x)
    return false;
  else if (mouse.y < position.y || mouse.y > position.y + container.getSize().y)
    return false;

  return true;
}

void Button::OnClick() {
  if (callback) {
    callback();
  } else {
    std::cerr << "No callback function provided!" << std::endl;
  }
}

sf::Color Button::lerpColor(const sf::Color& start, const sf::Color& end,
                            double t) {
  return sf::Color(static_cast<sf::Uint8>(start.r + t * (end.r - start.r)),
                   static_cast<sf::Uint8>(start.g + t * (end.g - start.g)),
                   static_cast<sf::Uint8>(start.b + t * (end.b - start.b)),
                   static_cast<sf::Uint8>(start.a + t * (end.a - start.a)));
}

}  // namespace UI