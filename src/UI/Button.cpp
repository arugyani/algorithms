#include "UI/Button.h"

#include <functional>
#include <iostream>
#include <string>

namespace UI {

Button::Button()
    : position(sf::Vector2f(0, 0)),
      onClick([]() { std::cout << "onClick not defined!"; }),
      text("") {
  Initialize("");
}

Button::Button(sf::Vector2f position, std::string text,
               std::function<void()> onClick)
    : position(position), text(text), onClick(onClick) {
  Initialize(text);
}

void Button::LoadFont(std::string path) {
  if (!font.loadFromFile(path)) {
    throw std::runtime_error("Could not load \"" + path + "\" font!");
  }
}

void Button::LoadCursor() {
  if (!cursor.loadFromSystem(sf::Cursor::Hand)) {
    throw std::runtime_error("Could not load hand cursor!");
  }
}

void Button::Initialize(std::string text) {
  LoadFont("assets/arial.ttf");
  LoadCursor();

  transitionTime = 0.1f;
  elapsedTime = 0.0f;
  hovered = false;
  cursorSet = false;
  clicked = false;
  fontSize = 15;
  padding = sf::Vector2f(24.f, 24.f);

  startContainerColor = sf::Color(255, 255, 255);
  endContainerColor = sf::Color(31, 32, 33);
  startTextColor = sf::Color(31, 32, 33);
  endTextColor = sf::Color(255, 255, 255);

  label.setFont(font);
  label.setString(text);
  label.setCharacterSize(fontSize);
  label.setFillColor(startTextColor);
  container.setFillColor(startContainerColor);

  UpdateTextBounds();
}

void Button::Update(double deltaTime, sf::RenderWindow& window) {
  OnHover(deltaTime, window);
  OnClick();
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(container, states);
  target.draw(label, states);
}

bool Button::IsHovered(sf::Vector2i mouse) {
  if (mouse.x < position.x || mouse.x > position.x + container.getSize().x)
    return false;
  else if (mouse.y < position.y || mouse.y > position.y + container.getSize().y)
    return false;

  return true;
}

void Button::OnHover(double deltaTime, sf::RenderWindow& window) {
  sf::Vector2i mouse = sf::Mouse::getPosition(window);

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
    window.setMouseCursor(sf::Cursor());
    cursorSet = false;

    if (elapsedTime > 0) {
      elapsedTime -= deltaTime;
      if (elapsedTime < 0) {
        elapsedTime = 0;
      }
    }
  }

  double t = elapsedTime / transitionTime;

  sf::Color currentContainerColor =
      Renderable::LerpColor(startContainerColor, endContainerColor, t);
  sf::Color currentTextColor =
      Renderable::LerpColor(startTextColor, endTextColor, t);

  // Apply interpolated colors
  container.setFillColor(currentContainerColor);
  label.setFillColor(currentTextColor);
}

void Button::OnClick() {
  bool isMousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
  if (hovered && isMousePressed && !clicked) {
    if (onClick) {
      onClick();
    } else {
      std::cerr << "No callback function provided!" << std::endl;
    }
  }
  clicked = isMousePressed;
}

void Button::PositionShapes() {
  float containerWidth = std::max(100.f, textBounds.width + padding.x);
  float containerHeight = textBounds.height + padding.y;

  label.setOrigin(sf::Vector2f(textBounds.left + textBounds.width / 2.f,
                               textBounds.top + textBounds.height / 2.f));
  label.setPosition(sf::Vector2f(position.x + containerWidth / 2.f,
                                 position.y + containerHeight / 2.f));

  container.setSize(sf::Vector2f(containerWidth, containerHeight));
  container.setPosition(position);
}

void Button::SetPadding(sf::Vector2f padding) {
  this->padding = padding;
  PositionShapes();
}

void Button::SetPosition(sf::Vector2f position) {
  this->position = position;

  PositionShapes();
}

void Button::SetFontSize(unsigned int fontSize) {
  if (fontSize < MAX_FONT_SIZE) {  // capped font size
    this->fontSize = fontSize;

    label.setCharacterSize(fontSize);

    UpdateTextBounds();
  }
}

void Button::SetText(std::string text) {
  if (text.size() < MAX_TEXT_LENGTH) {  // capped text length
    this->text = text;
    label.setString(text);

    UpdateTextBounds();
  }
}

void Button::UpdateTextBounds() {
  textBounds = label.getLocalBounds();
  PositionShapes();
}

}  // namespace UI