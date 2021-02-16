#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

class Player : public sf::CircleShape
{
public:
  Player(const sf::CircleShape&);
  void movePlayer(const float playerSpeed);
  float getPlayerSpeed();
  void setPlayerSpeed(const float speed);
private:
  float playerSpeed_;
};

#endif
