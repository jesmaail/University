#pragma once
#include "Neuron.h"

class Neuron;

class Connection{
private:
	Neuron *m_neuron;
	float m_weight;

public:
	Connection(Neuron &n, float weight);

	~Connection(){};


	Neuron* GetNeuron();
	void SetNeuron(Neuron* n);

	float GetWeight();
	void SetWeight(float weight);
};