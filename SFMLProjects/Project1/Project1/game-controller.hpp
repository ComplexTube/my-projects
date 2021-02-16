#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include <SFML/Graphics.hpp>
#include <random>
#include <cmath>
#include "player.hpp"

class GameController
{
public:
  GameController(const sf::Window& window);
  void doEvents(sf::RenderWindow* window);
  bool isCollides();
  void eatFood();
  void changePlayerPref(const float deltaRadius, const float deltaSpeed);
  void increaseScore();
  void increaseTimer();
  void movePlayer();
  void displayGame(sf::RenderWindow* window);

private:
  const sf::Window& window_;
  Player player_;
  sf::CircleShape food_;
  sf::Font font_;
  sf::Text scoreText_;
  sf::Text timerText_;
  sf::Clock timer_;
  size_t scoreCounter_;
};

#endif