#pragma once
#include "Connection.h"
#include <vector>

using std::vector;

class Connection;

typedef vector<Connection> ConnectionSet;

class Neuron{
private:
	double m_bias;
	double m_value;
	ConnectionSet m_connections;

public:
	Neuron();
	Neuron(double bias);

	~Neuron(){};

	double Activation();
	double CalculateValue();

	double GetValue();
	void SetValue(double value);

	double GetBias();
	void SetBias(double bias);

	ConnectionSet GetConnections();
	void SetConnections(ConnectionSet c);

	void addConnection(Connection c);
};


typedef vector<vector<double>> Filter;

class ConvNeuron : public Neuron{
private:
	double m_bias;
	double m_value;
	Filter m_weights;
	ConnectionSet m_connections;

public:
	ConvNeuron();
	~ConvNeuron(){};

	double GetBias();
	void SetBias(double b);

	double GetValue();
	void SetValue(double v);

	void SetWeights(Filter w);
	Filter GetWeights();

	void SetConnections(ConnectionSet c);
	ConnectionSet GetConnections();

	void addConnection(Connection c);
	void addConnection(ConvConnection c);
};