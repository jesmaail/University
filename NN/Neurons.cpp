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
	//sigmoid functionr
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




vector<Connection> Neuron::GetConnections(){
	return m_connections;
}

void Neuron::SetConnections(vector<Connection> conns){
	m_connections = conns;
}

void Neuron::addConnection(Connection c){
	m_connections.push_back(c);
}




ConvNeuron:: ConvNeuron(){

}




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




void ConvNeuron::SetWeights(vector<vector<double>> weights){
	m_weights = weights;
}

vector<vector<double>> ConvNeuron::GetWeights(){
	return m_weights;
}




void ConvNeuron::SetConnections(vector<Connection> c){
	m_connections = c;
}

vector<Connection> ConvNeuron::GetConnections(){
	return m_connections;
}

void ConvNeuron::addConnection(Connection c){
	m_connections.push_back(c);
}

void ConvNeuron::addConnection(ConvConnection c){
	m_connections.push_back(c);
}