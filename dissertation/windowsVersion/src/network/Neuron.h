#pragma once
//#include "Connection.h"
#include <vector>
#include <tuple>

using std::vector;
using std::pair;
using std::tuple;

class Neuron;

typedef tuple<int, int, int> ThrIndex;
//typedef pair<ThrIndex, ThrIndex> Conn;
//typedef pair<double, double> Conn;
typedef pair<double, ThrIndex> Conn;
typedef vector<Conn> Connections;

typedef vector<vector<double>> Filter;

class Layer;

class Neuron{
private:
	double m_bias;
	double m_value;
	Connections m_connections;

public:
	Neuron();

	~Neuron(){};

	//virtual double Activation();
	void Activation();
	double CalculateValue(Layer* prev);

	double GetValue();
	void SetValue(double v);

	double GetBias();
	void SetBias(double bias);

	Connections GetConnections();
	void SetConnections(Connections c);

	void addConnection(Conn c);
};

class ConvNeuron : public Neuron{
private:
	//double m_bias;
	double m_value;
	Filter m_weights;
	Connections m_connections;

public:
	ConvNeuron();
	~ConvNeuron(){};

	void SetWeights(Filter w);
	Filter GetWeights();

	//virtual double Activation();
	//void Activation();
};