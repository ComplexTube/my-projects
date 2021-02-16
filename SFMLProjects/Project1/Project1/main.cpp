#include <SFML/Graphics.hpp>
#include <iostream>
#include "game-controller.hpp"

int main()
{
  try
  {
    sf::RenderWindow window(sf::VideoMode(800, 400), sf::String("Circle!"));
    GameController gameController(window);
    while (window.isOpen())
    {
      gameController.doEvents(&window);
      if (gameController.isCollides())
      {
        gameController.eatFood();
        gameController.changePlayerPref(0.2f, 0.01f);
        gameController.increaseScore();
      }
      gameController.movePlayer();
      gameController.increaseTimer();
      window.clear();
      gameController.displayGame(&window);
      window.display();
    }
    return 0;
  }
  catch (const std::exception& exception)
  {
    std::cerr << exception.what();
    return 1;
  }
  catch (...)
  {
    return 2;
  }
}