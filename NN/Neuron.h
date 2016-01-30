#pragma once
//#include "Connection.h"
#include <vector>

using std::vector;
using std::pair;

//class Connection;
class Neuron;
//typedef vector<Connection> ConnectionSet;
typedef vector<pair<double , double>> Connections;
typedef pair<double, double> Conn;
typedef vector<vector<double>> Filter;

class Neuron{
private:
	double m_bias;
	double m_value;
	Connections m_connections;

public:
	Neuron();
	Neuron(double bias);

	~Neuron(){};

	virtual double Activation();
	double CalculateValue();

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
	double m_bias;
	double m_value;
	Filter m_weights;
	Connections m_connections;

public:
	ConvNeuron();
	~ConvNeuron(){};

	void SetWeights(Filter w);
	Filter GetWeights();

	virtual double Activation();
};