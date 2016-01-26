#include "NeuralNetwork.h"

//#### Layer #############################################

Layer::Layer(){
}

float Layer::GetBias(){
	return m_bias;
}

void Layer::SetBias(float bias){
	m_bias = bias;
}

vector<Neuron> Layer::GetNeurons(){
	return m_neurons;
}

void Layer::AddNeuron(Neuron n){

}

void Layer::AddNeuronVector(vector<Neuron> ns){
	m_neurons = ns;
}




//#### Convolutional Layer ###############################

ConvLayer::ConvLayer(){
}




float ConvLayer::GetBias(){
	return m_bias;
}

void ConvLayer::SetBias(float bias){
	m_bias = bias;
}




int ConvLayer::GetFilterNum(){
	return m_filterNum;
}

void ConvLayer::SetFilterNum(int num){
	m_filterNum = num;
}




int ConvLayer::GetFilterSize(){
	return m_filterSize;
}

void ConvLayer::SetFilterSize(int size){
	m_filterSize = size;
}




int ConvLayer::GetStride(){
	return m_stride;
}

void ConvLayer::SetStride(int stride){
	m_stride = stride; 
}




vector<vector<float>> ConvLayer::GetWeights(){
	return m_weights;
}

void ConvLayer::SetWeights(vector<vector<float>> w){
	m_weights = w;
}




vector<vector<ConvNeuron>> ConvLayer::GetNeurons(){
	return m_neurons;
}

void ConvLayer::SetNeurons(vector<vector<ConvNeuron>> neurons){
	m_neurons = neurons;
}



//#### Fully Connected Layer #############################

FullConnLayer::FullConnLayer(){
}

vector<Neuron> FullConnLayer::GetNeurons(){
	return m_neurons;
}

void FullConnLayer::SetNeurons(vector<Neuron> n){
	m_neurons = n;
}