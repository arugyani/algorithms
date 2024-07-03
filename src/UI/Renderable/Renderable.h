#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <SFML/Graphics.hpp>

class Renderable : public sf::Drawable {
 public:
  virtual void Update(double deltaTime, const sf::Vector2i& mouse,
                      sf::RenderWindow& window) = 0;
};

#endif