#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include <iostream>
#include "mnist/mnist_reader.hpp"
#include "mnist/mnist_reader_common.hpp"
#include "mnist/mnist_reader_less.hpp"
#include "mnist/mnist_utils.hpp"
#include "NN/perceptron.hpp"

int main()
{
  const unsigned int NUMBER_CASE_LENGTH = 28;
  const unsigned int RECTANGLE_SHAPE_MULTIPLICATOR = 16;

  auto dataset = mnist::read_dataset<std::vector, std::vector, uint8_t, uint8_t>();
  std::vector<std::vector<float>> trainingSet;
  for (int i = 0; i < dataset.training_images.size(); i++)
  {
    trainingSet.push_back({});
    for (int j = 0; j < dataset.training_images[i].size(); j++)
    {
      trainingSet[i].push_back(((float)dataset.training_images[i][j] / 255 * 0.99) + 0.01);
    }
  }
  std::vector<std::vector<float>> trainingLabels;
  for (int i = 0; i < dataset.training_labels.size(); i++)
  {
    trainingLabels.push_back({});
    for (int j = 0; j < 10; j++)
    {
      if (dataset.training_labels[i] == j)
      {
        trainingLabels[i].push_back(1);
      }
      else
      {
        trainingLabels[i].push_back(0);
      }
    }
  }
  Perceptron<float> perceptron(trainingSet, std::vector<unsigned int> {784, 40, 20, 10}, trainingLabels);
  perceptron.learn();
  int caseNumber;
  std::cout << "Input number of the case you want to test: ";
  std::cin >> caseNumber;
  sf::RenderWindow outputNumberWindow(sf::VideoMode(NUMBER_CASE_LENGTH * RECTANGLE_SHAPE_MULTIPLICATOR, NUMBER_CASE_LENGTH * RECTANGLE_SHAPE_MULTIPLICATOR), sf::String("NumberOutput"));
  for (int i = 0; i < outputNumberWindow.getSize().x / RECTANGLE_SHAPE_MULTIPLICATOR; i++)
  {
    for (int j = 0; j < outputNumberWindow.getSize().y / RECTANGLE_SHAPE_MULTIPLICATOR; j++)
    {
      sf::RectangleShape shape(sf::Vector2f(RECTANGLE_SHAPE_MULTIPLICATOR, RECTANGLE_SHAPE_MULTIPLICATOR));
      shape.move(i * shape.getSize().x, j * shape.getSize().y);
      shape.setFillColor(sf::Color(255, 255, 255, dataset.test_images[caseNumber][j * NUMBER_CASE_LENGTH + i]));
      outputNumberWindow.draw(shape);
    }
  }
  outputNumberWindow.display();


  std::cout << "Label of the case " << caseNumber << ": " << std::to_string(dataset.test_labels[caseNumber]) << '\n';
  std::vector<float> testCase = {};
  for (int i = 0; i < dataset.test_images[caseNumber].size(); i++)
  {
    testCase.push_back(((float)dataset.test_images[caseNumber][i] / 255 * 0.99) + 0.01);
  }
  perceptron.solve(testCase);

  while (outputNumberWindow.isOpen())
  {
    sf::Event e;
    if (outputNumberWindow.pollEvent(e))
    {
      switch (e.type)
      {
      case sf::Event::EventType::Closed:
        outputNumberWindow.close();
        break;
      }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
    {
      outputNumberWindow.close();
    }
  }
  return 0;
}