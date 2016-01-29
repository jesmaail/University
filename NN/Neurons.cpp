#pragma once
#include "NeuralNetwork.h"

Neuron::Neuron(){
	SetValue(2);
	SetBias(0);
}

Neuron::Neuron(double bias)
	: m_bias(bias){
}

double Neuron::Activation(){
	//sigmoid function
	return 0; //ph
}

double Neuron::CalculateValue(){
	//foreach loop here with summation including bias and weights
	return 0; //ph
}

double Neuron::GetValue(){
	return m_value;
}

void Neuron::SetValue(double value){
	m_value = value;
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

void Neuron::addConnection(pair<Neuron&, double> c){
	m_connections.push_back(c);
}




ConvNeuron:: ConvNeuron(){

}
/*
double ConvNeuron::GetBias(){
	return m_bias;
}

void ConvNeuron::SetBias(double b){
	m_bias = b;
}

double ConvNeuron::GetValue(){
	return m_value;
}

void ConvNeuron::SetValue(double v){
	m_value = v;
}
*/
void ConvNeuron::SetWeights(Filter w){
	m_weights = w;
}

Filter ConvNeuron::GetWeights(){
	return m_weights;
}
/*
void ConvNeuron::SetConnections(ConnectionSet c){
	m_connections = c;
}

ConnectionSet ConvNeuron::GetConnections(){
	return m_connections;
}

void ConvNeuron::addConnection(Connection c){
	m_connections.push_back(c);
}

void ConvNeuron::addConnection(ConvConnection c){
	m_connections.push_back(c);
}*/