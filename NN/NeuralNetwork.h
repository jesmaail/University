#pragma once
#include "Preprocessor.h"
#include "Layers.h"
#include "Neuron.h"
#include "Connection.h"
#include <vector>

using std::vector;

class NeuralNetwork{
private:
	vector<ConvLayer> m_convLayers;
	vector<FullConnLayer> m_fcLayers;
	ConvLayer m_inputLayer;		//Need getters/setters
	ConvLayer m_secondLayer;
	ConvLayer m_thirdLayer;
	FullConnLayer m_fourthLayer;
	FullConnLayer m_outputLayer;
	int m_actionSetSize;

public:
	NeuralNetwork();

	~NeuralNetwork(){};

	void populateInputLayer(vector<vector<int>> img);
	void populateSecondLayer();
	void populateThirdLayer();
	void populateFourthLayer();
	void populateOutputLayer();

	ConvLayer GetInputLayer();
	ConvLayer GetSecondLayer();
	ConvLayer GetThirdLayer();
	FullConnLayer GetFourthLayer();
	FullConnLayer GetOutputLayer();

	void SetInputLayer(ConvLayer l);
	void SetSecondLayer(ConvLayer l);
	void SetThirdLayer(ConvLayer l);
	void SetFourthLayer(FullConnLayer l);
	void SetOutputLayer(FullConnLayer l);

	vector<ConvLayer> GetConvLayers();
	void SetConvLayers(vector<ConvLayer> layers);

	vector<FullConnLayer> GetFullConnLayers();
	void SetFullConnLayers(vector<FullConnLayer> layers);

	int GetActionSetSize();
	void SetActionSetSize(int s);
};


//This is where the Neural Network will be run from, containing the Network, ALE and Q-Table
class Main{
private:
	//ALE m_ale;
	NeuralNetwork m_nn;

public:


};