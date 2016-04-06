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
const int OUTPUT_LAYER_SIZE = 4; //WILL BE ACTION SET SIZE

int main(){
	Image imagePH;		//Create placeholder images //TESTING PURPOSES ONLY
	vector<int> phRow;
	for (uint i = 0; i < 84; i++){
		for (uint j = 0; j < 84; j++){
			phRow.push_back(i+j);
		}
		imagePH.push_back(phRow);
		phRow.clear();
	}
	vector<Image> imgs;
	for (uint i = 0; i < 4; i++){
		imgs.push_back(imagePH);
	}
	
	NeuralNetwork nn(imgs);
	
	//################################
	// Just to keep debug window open!
	int ph;
	std::cin >> ph;
	//################################

	return 0;
}

//Should pass in a struct of weights!!!!!!!!!
NeuralNetwork::NeuralNetwork(Images imgs){
	SetActionSetSize(OUTPUT_LAYER_SIZE); //change to ALE command get action size
	m_input = imgs;
	// Filter creation here should be done outside the network and passed in.
	Filter filter;
	Filters fs;
	filter.push_back({ 1, 1, 1, 1, 1, 1, 1, 1 });
	filter.push_back({ 1, 2, 2, 2, 2, 2, 2, 1 });
	filter.push_back({ 1, 2, 2, 1, 2, 1, 2, 1 });
	filter.push_back({ 1, 2, 1, 3, 3, 2, 2, 1 });
	filter.push_back({ 1, 2, 2, 3, 3, 1, 2, 1 });
	filter.push_back({ 1, 2, 1, 2, 1, 2, 2, 1 });
	filter.push_back({ 1, 2, 2, 2, 2, 2, 2, 1 });
	filter.push_back({ 1, 1, 1, 1, 1, 1, 1, 1 });	
	for (uint i = 0; i < FIRST_FILT_COUNT; i++){
		fs.push_back(filter);
	}
	m_firstWeights = fs;

	filter.clear();
	fs.clear();
	filter.push_back({ 1, 1, 1, 1 });
	filter.push_back({ 1, 2, 2, 1 });
	filter.push_back({ 1, 3, 3, 1 });
	filter.push_back({ 1, 2, 2, 1 });
	for (int i = 0; i < SECOND_FILT_COUNT; i++){
		fs.push_back(filter);
	}
	m_secondWeights = fs;
	Weights w;

	for (uint i = 0; i < FOURTH_LAYER_SIZE; i++){
		w.push_back(i);
	}
	m_thirdWeights = w;
	
	w.clear();
	for (uint i = 0; i < GetActionSetSize(); i++){
		w.push_back(i);
	}
	m_fourthWeights = w;

	std::cout << "Filters set" << std::endl;

	ForwardProp();

	//BackProp();
}

void::NeuralNetwork::ForwardProp(){

	SetInputLayer(ConvLayer(m_input, FIRST_FILT_SIZE, FIRST_FILT_COUNT, FIRST_FILT_STRIDE));
	m_inputLayer.SetFilters(m_firstWeights);
	testConvLayer(m_inputLayer, 1); //Test

	SetSecondLayer(ConvLayer(m_inputLayer, SECOND_FILT_SIZE, SECOND_FILT_COUNT, SECOND_FILT_STRIDE));
	m_secondLayer.SetFilters(m_secondWeights);
	testConvLayer(m_secondLayer, 2); //Test
	m_secondLayer.activateNeurons();

	SetThirdLayer(ConvLayer(m_secondLayer, 0, 0, 0));
	testConvLayer(m_thirdLayer, 3); //Test
	m_thirdLayer.activateNeurons();

	SetFourthLayer(FullConnLayer(m_thirdLayer, FOURTH_LAYER_SIZE));
	m_fourthLayer.SetWeights(m_thirdWeights);
	testFCLayer(m_fourthLayer, 4); // Test
	m_fourthLayer.activateNeurons();

	SetOutputLayer(FullConnLayer(m_fourthLayer, GetActionSetSize()));
	m_outputLayer.SetWeights(m_fourthWeights);
	testFCLayer(m_outputLayer, 5); // Test
	m_outputLayer.activateNeurons();
}

void NeuralNetwork::BackProp(){
	NeuronSet out = m_outputLayer.GetNeurons();
	NeuronSet fourth = m_fourthLayer.GetNeurons();
	Connections cs;
	double dedw; //derivate of weight wrt. error
	double y; //yield
	double x; //neuron value;
	double delta; //change for weight
	double w; //weight to change
	double t = 5; //target value, from Q table?????
	double eps = 0.00025; //learning rate
	double mu = 0.01;	//smoothing value
	double ms = 0; //mean square

	for (Neuron *on : out){
		cs = on->GetConnections();
		for (Conn c : cs){
			//ThrIndex index = c.first;
			//Neuron *n = fourth[index];
			//w = m_fourthLayer.GetWeightAt[c.second];
			y = on->GetValue();
			//x = n->GetValue();
			dedw = (t - y) * y*(1 - y) * x;
			ms = 0.9 * ms + 0.1* pow(dedw, 2); 
			delta = (eps * dedw) / sqrt(ms) + mu;
			w += delta;
		}
	}

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