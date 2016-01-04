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





//#### Convolutional Neuron ##############################

ConvNeuron:: ConvNeuron(){

}





//#### Connection ########################################

Connection:: Connection(Neuron *n, float weight)
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