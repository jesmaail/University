#pragma once
#include "NeuralNetwork.h"

Neuron::Neuron(){
	SetValue(2);
	SetBias(0);
}

Neuron::Neuron(float bias)
	: m_bias(bias){
}




float Neuron::Activation(){
	//sigmoid functionr
	return 0; //ph
}

float Neuron::CalculateValue(){
	//foreach loop here with summation including bias and weights
	return 0; //ph
}




float Neuron::GetValue(){
	return m_value;
}

void Neuron::SetValue(float value){
	m_value = value;
}




float Neuron::GetBias(){
	return m_bias;
}

void Neuron::SetBias(float bias){
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




float ConvNeuron::GetBias(){
	return m_bias;
}

void ConvNeuron::SetBias(float b){
	m_bias = b;
}




float ConvNeuron::GetValue(){
	return m_value;
}

void ConvNeuron::SetValue(float v){
	m_value = v;
}




void ConvNeuron::SetWeights(vector<vector<float>> weights){
	m_weights = weights;
}

vector<vector<float>> ConvNeuron::GetWeights(){
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