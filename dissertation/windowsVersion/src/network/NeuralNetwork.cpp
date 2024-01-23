#pragma once
#include "NeuralNetwork.h"
#include <iostream>
#include <math.h>

using std::make_pair;
const int FIRST_FILT_SIZE = 8;
const int FIRST_FILT_COUNT = 4;
const int FIRST_FILT_STRIDE = 4;

const int SECOND_FILT_SIZE = 4;
const int SECOND_FILT_COUNT = 2;
const int SECOND_FILT_STRIDE = 2;

const int FOURTH_LAYER_SIZE = 256;

NeuralNetwork::NeuralNetwork(Images imgs, weightStruct weights, int actionSize){
	SetActionSetSize(actionSize);
	m_input = imgs;

	m_weights = weights;

	ForwardProp();
	//BackProp();
}

void::NeuralNetwork::ForwardProp(){

	SetInputLayer(ConvLayer(m_input, FIRST_FILT_SIZE, FIRST_FILT_COUNT, FIRST_FILT_STRIDE));
	m_inputLayer.SetFilters(m_weights.wl1);
	//testConvLayer(m_inputLayer, 1); //Test


	SetSecondLayer(ConvLayer(m_inputLayer, SECOND_FILT_SIZE, SECOND_FILT_COUNT, SECOND_FILT_STRIDE));
	m_secondLayer.SetFilters(m_weights.wl2);
	//testConvLayer(m_secondLayer, 2); //Test
	m_secondLayer.ActivateNeurons();

	SetThirdLayer(ConvLayer(m_secondLayer, 0, 0, 0));
	//testConvLayer(m_thirdLayer, 3); //Test
	m_thirdLayer.ActivateNeurons();

	SetFourthLayer(FullConnLayer(m_thirdLayer, FOURTH_LAYER_SIZE));
	m_fourthLayer.SetWeights(m_weights.wl3);
	//testFCLayer(m_fourthLayer, 4); // Test
	m_fourthLayer.ActivateNeurons();

	SetOutputLayer(FullConnLayer(m_fourthLayer, GetActionSetSize()));
	m_outputLayer.SetWeights(m_weights.wl4);
	//testFCLayer(m_outputLayer, 5); // Test
	m_outputLayer.ActivateNeurons();
}

void NeuralNetwork::BackProp(int cost){
	//Want to feed in the target value to this function, when called from the agent.
	//Calculate the loss function

}


void NeuralNetwork::testConvLayer(ConvLayer l, int n){
	int num = n;
	int output1, output2, output3;
	FMS fs;
	ConvNeuronSet ns;

	fs = l.GetFeatureMaps();
	output1 = fs.size();
	output2 = fs[0].size();
	output3 = fs[0][0].size();
	std::cout << "Layer "<<n << ": " << output1 << ", " << output2 << ", " << output3 << std::endl;
}

void NeuralNetwork::testFCLayer(FullConnLayer l, int n){
	int num = n;
	int output1;
	NeuronSet ns = l.GetNeurons();
	output1 = ns.size();
	std::cout << "Layer " << n << ": " << output1 << std::endl;
}

ConvLayer NeuralNetwork::GetInputLayer(){
	return m_inputLayer;
}

ConvLayer NeuralNetwork::GetSecondLayer(){
	return m_secondLayer;
}

ConvLayer NeuralNetwork::GetThirdLayer(){
	return m_thirdLayer;
}

FullConnLayer NeuralNetwork::GetFourthLayer(){
	return m_fourthLayer;
}

FullConnLayer NeuralNetwork::GetOutputLayer(){
	return m_outputLayer;
}

void NeuralNetwork::SetInputLayer(ConvLayer l){
	m_inputLayer = l;
}

void NeuralNetwork::SetSecondLayer(ConvLayer l){
	m_secondLayer = l;
}

void NeuralNetwork::SetThirdLayer(ConvLayer l){
	m_thirdLayer = l;
}

void NeuralNetwork::SetFourthLayer(FullConnLayer l){
	m_fourthLayer = l;
}

void NeuralNetwork::SetOutputLayer(FullConnLayer l){
	m_outputLayer = l;
}

Images NeuralNetwork::GetInput(){
	return m_input;
}

void NeuralNetwork::SetInput(Images i){
	m_input = i;
}

int NeuralNetwork::GetActionSetSize(){
	return m_actionSetSize;
}

void NeuralNetwork::SetActionSetSize(int s){
	m_actionSetSize = s;
}

int NeuralNetwork::GetDecision(){
	int count = 0;
	double max = -9999;
	int maxNum = 0;
	for (Neuron* n : m_outputLayer.GetNeurons()){
		if (n->GetValue() > max){
			max = n->GetValue();
			maxNum = count;
		}
		count++;
	}

	return maxNum;
}