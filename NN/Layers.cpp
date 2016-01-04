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

void Layer::AddNeuron(Neuron *n){

}

void Layer::AddNeuronVector(vector<Neuron> ns){
	m_neurons = ns;
}




//#### Convolutional Layer ###############################

ConvLayer::ConvLayer(){
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



//#### Fully Connected Layer #############################
FullConnLayer::FullConnLayer(){
}