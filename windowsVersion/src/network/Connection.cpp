#pragma once
#include "NeuralNetwork.h"


Connection::Connection(Neuron n, double weight)
: m_neuron(&n), m_weight(weight){
}




Neuron* Connection::GetNeuron(){
	return m_neuron;
}

void Connection::SetNeuron(Neuron* n){
	m_neuron = n;
}




double Connection::GetWeight(){
	return m_weight;
}

void Connection::SetWeight(double weight){
	m_weight = weight;
}




ConvConnection::ConvConnection(ConvNeuron n, double w){
	m_neuron = &n;
	m_weight = w;
}

ConvNeuron* ConvConnection::GetNeuron(){
	return m_neuron;
}