#pragma once
#include "NeuralNetwork.h"

Layer::Layer(){
}

double Layer::GetBias(){
	return m_bias;
}

void Layer::SetBias(double bias){
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




ConvLayer::ConvLayer(){
}




double ConvLayer::GetBias(){
	return m_bias;
}

void ConvLayer::SetBias(double bias){
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




vector<vector<double>> &ConvLayer::GetWeights(){
	return m_weights;
}

void ConvLayer::SetWeights(vector<vector<double>> w){
	m_weights = w;
}




vector<vector<ConvNeuron>> ConvLayer::GetNeurons(){
	return m_neurons;
}

void ConvLayer::SetNeurons(vector<vector<ConvNeuron>> neurons){
	m_neurons = neurons;
}




FullConnLayer::FullConnLayer(){
}

vector<Neuron> FullConnLayer::GetNeurons(){
	return m_neurons;
}

void FullConnLayer::SetNeurons(vector<Neuron> n){
	m_neurons = n;
}