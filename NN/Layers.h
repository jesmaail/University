#pragma once
#include "Neuron.h"
#include <vector>

using std::vector;

class Layer{
private:
	double m_bias;
	vector<Neuron> m_neurons;

public:
	Layer();

	~Layer(){};


	double GetBias();
	void SetBias(double bias);

	vector<Neuron> GetNeurons();
	void AddNeuron(Neuron n);
	void AddNeuronVector(vector<Neuron> ns);
};




class ConvLayer : public Layer{
private:
	double m_bias;

	int m_filterNum;
	int m_filterSize;
	int m_stride;
	vector<vector<double>> m_weights;

	vector<vector<ConvNeuron>> m_neurons;

public:
	ConvLayer();

	~ConvLayer(){};

	double GetBias();
	void SetBias(double bias);

	int GetFilterNum();
	void SetFilterNum(int num);

	int GetFilterSize();
	void SetFilterSize(int size);

	int GetStride();
	void SetStride(int stride);

	vector<vector<double>> &GetWeights();
	void SetWeights(vector<vector<double>> w);

	vector<vector<ConvNeuron>> GetNeurons();
	void SetNeurons(vector<vector<ConvNeuron>> neurons);
};



class FullConnLayer : public Layer{
private:
	double m_bias;
	vector<Neuron> m_neurons;

public:
	FullConnLayer();

	~FullConnLayer(){};

	vector<Neuron> GetNeurons();
	void SetNeurons(vector<Neuron> n);
};