#pragma once
#include "Preprocessor.h"
#include "Neuron.h"
#include "Layers.h"
#include "Connection.h"
#include <vector>

using std::vector;

typedef vector<Image> Images;
typedef unsigned int uint;

struct weightStruct{
	Filters weightLayer1;
	Filters weightLayer2;
	Weights weightLayer3;
	Weights weightLayer4;
};

class NeuralNetwork{
private:
	Images m_input;	//getter/setter
	int m_actionSetSize;
	ConvLayer m_inputLayer;
	ConvLayer m_secondLayer;
	ConvLayer m_thirdLayer;
	FullConnLayer m_fourthLayer;
	FullConnLayer m_outputLayer;

	Filters m_firstWeights;
	Filters m_secondWeights;
	Weights m_thirdWeights;
	Weights m_fourthWeights;

public:
	NeuralNetwork(Images imgs, weightStruct weights, int actionSize);

	~NeuralNetwork(){};

	void testConvLayer(ConvLayer l, int n);
	void testFCLayer(FullConnLayer l, int n);

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

	Images GetInput();
	void SetInput(Images i);

	int GetActionSetSize();
	void SetActionSetSize(int s);

	void ForwardProp();
	void BackProp(int target);

	int getDecision();
};


//This is where the Neural Network will be run from, containing the Network, ALE and Q-Table
class Main{
private:
	//ALE m_ale;
	NeuralNetwork m_nn;

public:


};