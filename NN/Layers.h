#pragma once
#include "Neuron.h"
#include <vector>

using std::vector;

class Layer{
private:
	float m_bias;
	vector<Neuron> m_neurons;

public:
	Layer();

	~Layer(){};


	float GetBias();
	void SetBias(float bias);

	vector<Neuron> GetNeurons();
	void AddNeuron(Neuron n);
	void AddNeuronVector(vector<Neuron> ns);
};




class ConvLayer : Layer{
private:
	float m_bias;

	int m_filterNum;
	int m_filterSize;
	int m_stride;
	vector<vector<float>> m_weights;

	vector<vector<ConvNeuron>> m_neurons;

public:
	ConvLayer();

	~ConvLayer(){};

	float GetBias();
	void SetBias(float bias);

	int GetFilterNum();
	void SetFilterNum(int num);

	int GetFilterSize();
	void SetFilterSize(int size);

	int GetStride();
	void SetStride(int stride);

	vector<vector<float>> GetWeights();
	void SetWeights(vector<vector<float>> w);

	vector<vector<ConvNeuron>> GetNeurons();
	void SetNeurons(vector<vector<ConvNeuron>> neurons);
};



class FullConnLayer : Layer{
private:
	float m_bias;
	vector<Neuron> m_neurons;

public:
	FullConnLayer();

	~FullConnLayer(){};

	vector<Neuron> GetNeurons();
	void SetNeurons(vector<Neuron> n);
};