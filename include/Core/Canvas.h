#ifndef CORE_CANVAS_H
#define CORE_CANVAS_H

#include <UI/Container.h>
#include <UI/Renderable.h>

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

namespace Core {

class Canvas : public UI::Renderable, public UI::Container {
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

  sf::Vector2f GetSize() { return size; }
  sf::View GetView() { return view; }

  virtual void Update(double deltaTime, sf::RenderTarget& target) override;
  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;
};

}  // namespace Core

#endif