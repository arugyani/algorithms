#ifndef UI_RENDERABLE_H
#define UI_RENDERABLE_H

#include <SFML/Graphics.hpp>

namespace UI {

class Renderable : public sf::Drawable {
 public:
  virtual ~Renderable() = default;

  virtual void Update(double deltaTime, sf::RenderTarget& target) = 0;
  virtual void HandleClick(sf::RenderWindow& window, sf::Vector2i mouse) = 0;

 protected:
  sf::Color LerpColor(const sf::Color& start, const sf::Color& end, double t) {
    return sf::Color(static_cast<sf::Uint8>(start.r + t * (end.r - start.r)),
                     static_cast<sf::Uint8>(start.g + t * (end.g - start.g)),
                     static_cast<sf::Uint8>(start.b + t * (end.b - start.b)),
                     static_cast<sf::Uint8>(start.a + t * (end.a - start.a)));
  }
};

}  // namespace UI

#endif