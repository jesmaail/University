#pragma once
#include "Connection.h"
#include <vector>

using std::vector;

class Connection;

class Neuron{
private:
	float m_bias;
	float m_value;
	vector<Connection> m_connections;

public:
	Neuron();
	Neuron(float bias);

	~Neuron(){};

	float Activation();
	float CalculateValue();

	float GetValue();
	void SetValue(float value);

	float GetBias();
	void SetBias(float bias);

	vector<Connection> GetConnections();
	void SetConnections(vector<Connection> conns);

	void addConnection(Connection c);
};




class ConvNeuron : Neuron{
private:
	float m_bias;
	float m_value;
	vector<vector<float>> m_weights;
	vector<Connection> m_connections;

public:
	ConvNeuron();
	~ConvNeuron(){};

	float GetBias();
	void SetBias(float b);

	float GetValue();
	void SetValue(float v);

	void SetWeights(vector<vector<float>> weights);
	vector<vector<float>> GetWeights();

	void SetConnections(vector<Connection> c);
	vector<Connection> GetConnections();

	void addConnection(Connection c);
};