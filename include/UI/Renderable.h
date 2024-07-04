#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <SFML/Graphics.hpp>

namespace UI {

class Renderable : public sf::Drawable {
 public:
  virtual ~Renderable() = default;

  virtual void Update(double deltaTime, sf::RenderWindow& window) = 0;
};

}  // namespace UI

#endif