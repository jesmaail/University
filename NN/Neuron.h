#pragma once
#include "Connection.h"
#include <vector>

using std::vector;

class Connection;

class Neuron{
private:
	double m_bias;
	double m_value;
	vector<Connection> m_connections;

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

	vector<Connection> GetConnections();
	void SetConnections(vector<Connection> conns);

	void addConnection(Connection c);
};




class ConvNeuron : public Neuron{
private:
	double m_bias;
	double m_value;
	vector<vector<double>> m_weights;
	vector<Connection> m_connections;

public:
	ConvNeuron();
	~ConvNeuron(){};

	double GetBias();
	void SetBias(double b);

	double GetValue();
	void SetValue(double v);

	void SetWeights(vector<vector<double>> weights);
	vector<vector<double>> GetWeights();

	void SetConnections(vector<Connection> c);
	vector<Connection> GetConnections();

	void addConnection(Connection c);
	void addConnection(ConvConnection c);
};