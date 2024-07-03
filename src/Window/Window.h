#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>

#include "../UI/Button.h"

namespace Core {

/**
 * \brief Handles all Window events, I/O, rendering, and windows.
 */
class Window {
 private:
  sf::RenderWindow window;
  sf::Clock clock;

  UI::Button button;

 public:
  Window(sf::Vector2u size, std::string title);

  /**
   * \brief Update function for all window data (should be called before draw)
   * \param deltaTime elapsed time for standardizing updates & frame rates
   * across machines
   */
  void Update(double deltaTime);

  /** \brief Draw function for all window renderables */
  void Draw();

  /** \brief Starts application loop. */
  void Run();
};

}  // namespace Core

#endif