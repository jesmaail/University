#include "NeuralNetwork.h"

//#### Neuron ###########################################
Neuron::Neuron(){
	SetValue(2);
	SetBias(0);
}

Neuron::Neuron(float bias)
	: m_bias(bias){
}




float Neuron::Activation(){
	//sigmoid function
}

float Neuron::CalculateValue(){
	//foreach loop here with summation including bias and weights
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




//#### Convolutional Neuron ##############################
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




//#### Connection ########################################
Connection::Connection(Neuron *n, float weight)
	: m_neuron(n), m_weight(weight){
}




Neuron Connection::GetNeuron(){
	return *m_neuron;
}

void Connection::SetNeuron(Neuron &n){
	*m_neuron = n;
}




float Connection::GetWeight(){
	return m_weight;
}

void Connection::SetWeight(float weight){
	m_weight = weight;
}