#pragma once
#include "NeuralNetwork.h"
#include <minmax.h>

Neuron::Neuron(){
	SetValue(2);
	SetBias(0);
}

Neuron::Neuron(double bias)
	: m_bias(bias){
}

double Neuron::Activation(){
	return max(m_value, 0);
}

double Neuron::CalculateValue(){
	double newVal = 0;
	for (Conn c : m_connections){
		newVal += c.first * c.second;
	}
	newVal *= m_bias;
	m_connections.clear(); //maybe
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

double ConvNeuron::Activation(){
	//rectifier nonlinearity
	return max(m_value, 0); 
}