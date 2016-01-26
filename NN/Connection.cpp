#pragma once
#include "NeuralNetwork.h"


Connection::Connection(Neuron &n, float weight)
: m_neuron(&n), m_weight(weight){
}




Neuron* Connection::GetNeuron(){
	return m_neuron;
}

void Connection::SetNeuron(Neuron* n){
	m_neuron = n;
}




float Connection::GetWeight(){
	return m_weight;
}

void Connection::SetWeight(float weight){
	m_weight = weight;
}