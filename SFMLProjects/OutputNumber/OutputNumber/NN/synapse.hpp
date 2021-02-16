#ifndef SYNAPSE_HPP
#define SYNAPSE_HPP

#include "neuron.hpp"
#include <stdexcept>
#include <random>

class Synapse
{
public:
  Synapse(Neuron& prevNeuron, Neuron& nextNeuron, float weight);
  void updateDataNextNeuron();
  Neuron* getNextNeuron();
  float weight_;
  float gradient_;
  float prevDeltaWeight_;
  Neuron* prevNeuron_;
  Neuron* nextNeuron_;
};

Synapse::Synapse(Neuron& prevNeuron, Neuron& nextNeuron, float weight) :
  prevNeuron_(nullptr),
  nextNeuron_(nullptr),
  gradient_(0),
  prevDeltaWeight_(0),
  weight_(weight)
{
  if (!(&prevNeuron) || !(&nextNeuron))
  {
    throw std::invalid_argument("ERROR: One of neurons was invalide");
  }
  prevNeuron_ = &prevNeuron;
  nextNeuron_ = &nextNeuron;
}

void Synapse::updateDataNextNeuron()
{
  nextNeuron_->updateData(prevNeuron_->getData() * weight_);
}

Neuron* Synapse::getNextNeuron()
{
  return nextNeuron_;
}

#endif // !SYNAPSE_HPP
