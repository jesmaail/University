#pragma once
#include "NeuralNetwork.h"
#include <algorithm>

Neuron::Neuron(){
	//SetValue(0);
	//SetBias(0);
}

void Neuron::Activation(){
	m_value = std::max(0.0, m_value);
}

double Neuron::CalculateValue(Layer* prev){
	ThrIndex weight;
	int nVal, wVal;
	double newVal = 0;

	for (Conn c : m_connections){
		weight = c.second;
		nVal = c.first;
		//wVal = prev->GetFilters
		//nVal = prev->GetFeatureMaps[std::get<0>(neuron)][std::get<1>(neuron)][std::get<2>(neuron)];
		//wVal = prev->
		//newVal += c.first * c.second;
	}
	newVal *= m_bias;
	//m_connections.clear(); //maybe
	return newVal; 
}

double Neuron::GetValue(){
	return m_value;
}

void Neuron::SetValue(double v){
	m_value = v;
}

double Neuron::GetBias(){
	return m_bias;
}

void Neuron::SetBias(double bias){
	m_bias = bias;
}

Connections Neuron::GetConnections(){
	return m_connections;
}

void Neuron::SetConnections(Connections c){
	m_connections = c;
}

void Neuron::addConnection(Conn c){
	m_connections.push_back(c);
}




ConvNeuron:: ConvNeuron(){

}

void ConvNeuron::SetWeights(Filter w){
	m_weights = w;
}

Filter ConvNeuron::GetWeights(){
	return m_weights;
}