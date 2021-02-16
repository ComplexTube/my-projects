#ifndef PERCEPTRON_HPP
#define PERCEPTRON_HPP

#include <vector>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <random>
#include <cmath>
#include "synapse.hpp"

template <typename T>
class Perceptron
{
public:
  Perceptron(const std::vector<std::vector<T>>& trainingCase,
    const std::vector<unsigned int>& countOfEachLayerNeurons,
    const std::vector<std::vector<T>>& idealOutputValues);
  void setInputNeuronsData(const std::vector<T>& trainingCase);
  void backPropogation(const std::vector<T>& idealOutputValue);
  void passForward();
  void learn(const unsigned int epoch = 1);
  void solve(const std::vector<T>& userCase);
  std::vector<std::vector<T>> trainingCase_;
  std::vector<std::vector<Neuron>> neurons_;
  std::vector<Synapse> synapses_;
  std::vector<std::vector<T>> idealOutputValues_;
  float error_;
  const float epsilon_ = 0.7; //По факту скорость обучения
  const float alfa_ = 0; //Ну, нужна, чтобы избежать локльный минимум, но... Тут не нужна по моему)
};

template<typename T>
inline Perceptron<T>::Perceptron(const std::vector<std::vector<T>>& trainingCase, 
  const std::vector<unsigned int>& countOfEachLayerNeurons, 
  const std::vector<std::vector<T>>& idealOutputValues) :
  trainingCase_(trainingCase),
  neurons_(),
  synapses_(),
  idealOutputValues_(idealOutputValues),
  error_(0)
{
  const unsigned int countOfInputNeurons = countOfEachLayerNeurons[0];
  std::for_each(trainingCase.begin(), trainingCase.end(), [countOfInputNeurons](const std::vector<T>& testCase) //Проверка на правильность входных значений
    {
      if (testCase.size() > countOfInputNeurons)
      {
        throw std::invalid_argument("ERROR!");
      }
    });
  const unsigned int countOfOutputNeurons = countOfEachLayerNeurons[countOfEachLayerNeurons.size() - 1];
  std::for_each(idealOutputValues.begin(), idealOutputValues.end(), [countOfOutputNeurons](const std::vector<T>& idealValue) //Проверка на правильность выходных значений
    {
      if (idealValue.size() > countOfOutputNeurons)
      {
        throw std::invalid_argument("ERROR!");
      }
    });
  for (unsigned int i = 0; i < countOfEachLayerNeurons.size(); i++)
  {
    neurons_.push_back({});
  }
  for (unsigned int i = 0; i < countOfInputNeurons; i++) //Создание входных нейронов
  {
    Neuron neuron(0, Neuron::NeuronType::INPUT);
    neurons_[0].push_back(neuron);
  }
  for (unsigned int i = 1; i < countOfEachLayerNeurons.size() - 1; i++)
  {
    for (unsigned int j = 0; j < countOfEachLayerNeurons[i]; j++)
    {
      Neuron neuron(0, Neuron::NeuronType::HIDDEN);
      neurons_[i].push_back(neuron);
    }
  }
  for (unsigned int i = 0; i < countOfOutputNeurons; i++) //Создание выходных нейронов
  {
    Neuron neuron(0, Neuron::NeuronType::OUTPUT);
    neurons_[countOfEachLayerNeurons.size() - 1].push_back(neuron);
  }
  for (unsigned int i = 0; i < countOfEachLayerNeurons.size() - 1; i++)
  {
    for (unsigned int j = 0; j < countOfEachLayerNeurons[i]; j++)
    {
      for (unsigned int k = 0; k < countOfEachLayerNeurons[i + 1]; k++)
      {
        Synapse synapse(neurons_[i][j], neurons_[i + 1][k], (float)rand() / RAND_MAX - 0.5);
        synapses_.push_back(synapse);
      }
    }
  }
}

template<typename T>
inline void Perceptron<T>::setInputNeuronsData(const std::vector<T>& trainingCase)
{
  for (unsigned int i = 0; i < trainingCase.size(); i++)
  {
    neurons_[0][i].inputData_ = trainingCase[i];
    neurons_[0][i].outputData_ = neurons_[0][i].inputData_;
  }
}

template<typename T>
inline void Perceptron<T>::backPropogation(const std::vector<T>& idealOutputValue)
{
  for (int i = 0; i < neurons_[neurons_.size() - 1].size(); i++)
  {
    neurons_[neurons_.size() - 1][i].delta_ = (idealOutputValue[i] - neurons_[neurons_.size() - 1][i].getData())
      * (1 - neurons_[neurons_.size() - 1][i].getData())
      * neurons_[neurons_.size() - 1][i].getData();
  }
  std::reverse(synapses_.begin(), synapses_.end()); //Переворачивю вектор синапсов
  const float epsilon = epsilon_;
  const float alfa = alfa_;
  std::for_each(synapses_.begin(), synapses_.end(), [](Synapse& synapse) {synapse.prevNeuron_->delta_ = 0; });
  std::for_each(synapses_.begin(), synapses_.end(), [](Synapse& synapse)
    {
      if (synapse.prevNeuron_->neuronType_ == Neuron::NeuronType::HIDDEN)
      {
        synapse.prevNeuron_->delta_ += (1 - synapse.prevNeuron_->getData()) * synapse.prevNeuron_->getData() *
          (synapse.weight_ * synapse.nextNeuron_->delta_); //Обновляю дельту на скрытых нейронах
      }
    });
  std::for_each(synapses_.begin(), synapses_.end(), [epsilon, alfa](Synapse& synapse) //Обновляю веса синапсов
    {
      synapse.gradient_ = synapse.prevNeuron_->getData() * synapse.nextNeuron_->delta_; //Обновляю градиент синапса
      synapse.weight_ = synapse.weight_ + (epsilon * synapse.gradient_ + alfa * synapse.prevDeltaWeight_); //обновляю вес синапса
      synapse.prevDeltaWeight_ = epsilon * synapse.gradient_ + alfa * synapse.prevDeltaWeight_; //Записываю предыдущую дельту веса
    });
  std::reverse(synapses_.begin(), synapses_.end()); //Возвращаю векторы в прежнюю последовательность
  int i = 0;
  float error = 0;
  std::for_each(neurons_[neurons_.size() - 1].begin(), neurons_[neurons_.size() - 1].end(), [idealOutputValue, &i, &error](const Neuron& neuron) //считаю ошибку
    {
      error += (idealOutputValue[i] - neuron.getData()) * (idealOutputValue[i] - neuron.getData());
      i++;
    });
  error_ += error;
}

template<typename T>
inline void Perceptron<T>::passForward()
{
  unsigned int counterSynapses = 0;
  unsigned int counterSynapsesBetweenLayers = 0;
  for (int i = 0; i < neurons_.size() - 1; i++)
  {
    while (counterSynapsesBetweenLayers < (neurons_[i].size() * neurons_[i + 1].size()))
    {
      synapses_[counterSynapses].updateDataNextNeuron();
      counterSynapses++;
      counterSynapsesBetweenLayers++;
    }
    counterSynapsesBetweenLayers = 0;
    std::for_each(neurons_[i + 1].begin(), neurons_[i + 1].end(), [](Neuron& neuron) {neuron.normalizeData(); });
  }
}

template<typename T>
inline void Perceptron<T>::learn(const unsigned int epoch)
{
  for (int i = 0; i < epoch; i++) //Итерация эпохи
  {
    error_ = 0;
    for (int j = 0; j < trainingCase_.size(); j++) // Итерация тренировочных кейсов, в данном случае их 4, ну понятно, да
    {
      setInputNeuronsData(trainingCase_[j]);
      passForward();
      backPropogation(idealOutputValues_[j]);
    }
  }
}

template<typename T>
inline void Perceptron<T>::solve(const std::vector<T>& userCase)
{
  if (userCase.size() != neurons_[0].size())
  {
    throw std::invalid_argument("ERROR: User is dumb!");
  }
  for (int i = 0; i < userCase.size(); i++)
  {
    neurons_[0][i].inputData_ = userCase[i];
    neurons_[0][i].outputData_ = neurons_[0][i].inputData_;
  }
  passForward();
  std::for_each(neurons_[neurons_.size() - 1].begin(), neurons_[neurons_.size() - 1].end(), [](Neuron& neuron) 
    {
      neuron.outputData_ = std::round(neuron.outputData_); 
      std::cout << neuron.getData() << '\n';
    });
}


#endif