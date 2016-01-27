#pragma once
#include "Neuron.h"

class Neuron;

class Connection{
private:
	Neuron *m_neuron;
	double m_weight;

public:
	Connection(Neuron &n, double weight);

	~Connection(){};


	Neuron* GetNeuron();
	void SetNeuron(Neuron* n);

	double GetWeight();
	void SetWeight(double weight);
};