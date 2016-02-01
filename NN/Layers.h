#pragma once
#include "Neuron.h"
#include <vector>

using std::vector;

typedef vector<Neuron*> NeuronSet;
typedef vector<ConvNeuron*> ConvRow;
typedef vector<vector<ConvNeuron*>> ConvNeuronSet;
typedef vector<vector<ConvNeuron*>> FeatureMap;
typedef vector<FeatureMap> FMS;
typedef vector<Filter> Filters;

class Layer{
private:
	double m_bias;
	NeuronSet m_neurons;

public:
	Layer();

	~Layer(){};


	double GetBias();
	void SetBias(double bias);

	NeuronSet GetNeurons();
	void AddNeuron(Neuron n);
	void AddNeuronVector(NeuronSet ns);
};




class ConvLayer : public Layer{
private:
	double m_bias;

	int m_filterNum;
	int m_filterSize;
	int m_stride;
	Filter m_weights;
	Filters m_filters;
	ConvNeuronSet m_neurons;
	FMS m_featureMaps;

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

	Filter GetWeights();
	void SetWeights(Filter w);

	ConvNeuronSet GetNeurons();
	void SetNeurons(ConvNeuronSet neurons);

	Filters GetFilters();
	void SetFilters(Filters f);

	FMS GetFeatureMaps();
	FeatureMap GetFeatureMapAt(int i);
	void SetFeatureMaps(FMS f);
	void addFeatureMap(FeatureMap f);
};



class FullConnLayer : public Layer{
private:
	double m_bias;
	NeuronSet m_neurons;

public:
	FullConnLayer();

	~FullConnLayer(){};

	NeuronSet GetNeurons();
	void SetNeurons(NeuronSet n);
	void AddNeuron(Neuron* n);
};