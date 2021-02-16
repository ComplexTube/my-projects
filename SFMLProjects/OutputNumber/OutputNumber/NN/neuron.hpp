#ifndef NEURON_HPP
#define NEURON_HPP

#include <math.h>
#include <stdexcept>

struct Neuron
{
  enum class NeuronType
  {
    INPUT = 0,
    HIDDEN = 1,
    OUTPUT = 2
  };
  Neuron(const float inputData, NeuronType neuronType = NeuronType::INPUT);
  void updateData(const float data);
  float getData() const;
  float normalizeData();
  NeuronType neuronType_;
  float inputData_;
  float bufferData_;
  float outputData_;
  float delta_;
};

Neuron::Neuron(const float inputData, NeuronType neuronType) :
  neuronType_(neuronType),
  inputData_(0),
  bufferData_(0),
  outputData_(0),
  delta_(0)
{
  if ((inputData < 0 || inputData > 1) && (neuronType_ == NeuronType::INPUT))
  {
    throw std::invalid_argument("Invalid input data of input neuron");
  }
  inputData_ = inputData;
  outputData_ = inputData_;
}

void Neuron::updateData(const float data)
{
  bufferData_ += data;
  inputData_ = bufferData_;
}

float Neuron::getData() const
{
  return outputData_;
}

float Neuron::normalizeData()
{
  outputData_ = (1 / (1 + exp(-bufferData_)));
  bufferData_ = 0;
  return outputData_;
}

#endif // !NEURON_HPP
