#include "player.hpp"

Player::Player(const sf::CircleShape& shapePlayer) :
  sf::CircleShape(shapePlayer),
  playerSpeed_(0.1f)
{
}

void Player::movePlayer(const float playerSpeed)
{
  sf::Keyboard::Key key = sf::Keyboard::Key::Unknown;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
  {
    key = sf::Keyboard::Key::Up;
  }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
  {
    key = sf::Keyboard::Key::Down;
  }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
  {
    key = sf::Keyboard::Key::Left;
  }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
  {
    key = sf::Keyboard::Key::Right;
  }
  switch (key)
  {
  case sf::Keyboard::Key::Up:
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
      this->move(-1 * std::cos(45 * 3.14 / 180) * playerSpeed, -1 * std::sin(45 * 3.14 / 180) * playerSpeed);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
      this->move(1 * std::cos(45 * 3.14 / 180) * playerSpeed, -1 * std::sin(45 * 3.14 / 180) * playerSpeed);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
      this->move(0, 0);
    }
    else
    {
      this->move(0, -playerSpeed);
    }
    break;
  case sf::Keyboard::Key::Down:
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
      this->move(-1 * std::cos(45 * 3.14 / 180) * playerSpeed, 1 * std::sin(45 * 3.14 / 180) * playerSpeed);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
      this->move(1 * std::cos(45 * 3.14 / 180) * playerSpeed, 1 * std::sin(45 * 3.14 / 180) * playerSpeed);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
      this->move(0, 0);
    }
    else
    {
      this->move(0, playerSpeed);
    }
    break;
  case sf::Keyboard::Key::Left:
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
      this->move(-1 * std::cos(45 * 3.14 / 180) * playerSpeed, -1 * std::sin(45 * 3.14 / 180) * playerSpeed);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
      this->move(-1 * std::cos(45 * 3.14 / 180) * playerSpeed, 1 * std::sin(45 * 3.14 / 180) * playerSpeed);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
      this->move(0, 0);
    }
    else
    {
      this->move(-playerSpeed, 0);
    }
    break;
  case sf::Keyboard::Key::Right:
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
      this->move(1 * std::cos(45 * 3.14 / 180) * playerSpeed, -1 * std::sin(45 * 3.14 / 180) * playerSpeed);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
      this->move(1 * std::cos(45 * 3.14 / 180) * playerSpeed, 1 * std::sin(45 * 3.14 / 180) * playerSpeed);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
      this->move(0, 0);
    }
    else
    {
      this->move(playerSpeed, 0);
    }
    break;
  default:
    break;
  }
}

float Player::getPlayerSpeed()
{
  return playerSpeed_;
}

void Player::setPlayerSpeed(const float speed)
{
  this->playerSpeed_ = speed;
}
