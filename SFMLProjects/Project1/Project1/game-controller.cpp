#include "game-controller.hpp"

GameController::GameController(const sf::Window& window) :
  window_(window),
  player_(Player(sf::CircleShape(30.f))),
  food_(sf::CircleShape(10.f)),
  font_(),
  scoreText_(),
  timerText_(),
  timer_(sf::Clock()),
  scoreCounter_(0)
{
  player_.setFillColor(sf::Color::Green);
  player_.setPosition(window.getSize().x / 2, window.getSize().y / 2);
  food_.setFillColor(sf::Color::Red);
  food_.setPosition(rand() % (int)(window.getSize().x - food_.getRadius() * 2), rand() % (int)(window.getSize().y - food_.getRadius() * 2));
  font_.loadFromFile("fonts/NotoSansTCRegular.otf");
  scoreText_.setString(sf::String("Score: 0"));
  scoreText_.setFont(font_);
  timerText_.setString(sf::String("Timer: 0"));
  timerText_.setFont(font_);
  timerText_.setPosition(0, scoreText_.getCharacterSize());
}

void GameController::doEvents(sf::RenderWindow* window)
{
  sf::Event e;
  while (window->pollEvent(e))
  {
    switch (e.type)
    {
    case sf::Event::Closed:
      window->close();
    }
  }
}

bool GameController::isCollides()
{
  if (sqrt(pow(((player_.getPosition().x + player_.getRadius()) - (food_.getPosition().x + food_.getRadius())), 2) +
    pow(((player_.getPosition().y + player_.getRadius()) - (food_.getPosition().y + food_.getRadius())), 2))
    <= player_.getRadius() + food_.getRadius())
  {
    return true;
  }
  else
  {
    return false;
  }
}

void GameController::eatFood()
{
  food_.setPosition(rand() % (int)(window_.getSize().x - food_.getRadius() * 2), rand() % (int)(window_.getSize().y - food_.getRadius() * 2));
}

void GameController::changePlayerPref(const float deltaRadius, const float deltaSpeed)
{
  player_.setRadius(player_.getRadius() - 0.2);
  player_.setPlayerSpeed(player_.getPlayerSpeed() + 0.001f);
}

void GameController::increaseScore()
{
  scoreText_.setString(sf::String("Score: " + std::to_string(++scoreCounter_)));
}

void GameController::increaseTimer()
{
  timerText_.setString(sf::String("Time: " + std::to_string((int)timer_.getElapsedTime().asSeconds())));
}

void GameController::movePlayer()
{
  player_.movePlayer(player_.getPlayerSpeed());
}

void GameController::displayGame(sf::RenderWindow* window)
{
  window->draw(player_);
  window->draw(food_);
  window->draw(scoreText_);
  window->draw(timerText_);
}
