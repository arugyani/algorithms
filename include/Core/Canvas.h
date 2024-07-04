#ifndef CORE_CANVAS_H
#define CORE_CANVAS_H

#include <UI/Renderable.h>

#include <SFML/Graphics.hpp>

namespace Core {

class Canvas : public UI::Renderable {
 private:
  sf::Vector2f size;
  sf::Vector2f position;

  sf::RenderTexture renderTexture;
  sf::ContextSettings settings;
  sf::View view;

  int antialiasing;

 public:
  Canvas(sf::Vector2f size, sf::Vector2f position);

  void SetSize(sf::Vector2f size);
  void SetView(float x, float y);

  virtual void Update(double deltaTime, sf::RenderWindow& window) override;

  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;
};

}  // namespace Core

#endif