/*#pragma once
#include "Neuron.h"

class Neuron;

class ConvNeuron;

class Connection{
private:
	Neuron *m_neuron;
	double m_weight;

public:
	Connection(){};
	Connection(Neuron n, double weight);

	~Connection(){};


	Neuron* GetNeuron();
	void SetNeuron(Neuron* n);

	double GetWeight();
	void SetWeight(double weight);
};

class ConvConnection : public Connection{
private:
	ConvNeuron *m_neuron;
	double m_weight;

public:
	ConvConnection(){};
	ConvConnection(ConvNeuron n, double w);

	~ConvConnection(){};

	ConvNeuron* GetNeuron();
	void SetNeuron(ConvNeuron* n);
};*/