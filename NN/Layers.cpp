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

NeuronSet Layer::GetNeurons(){
	return m_neurons;
}

void Layer::AddNeuron(Neuron n){

}

void Layer::AddNeuronVector(NeuronSet ns){
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




Filter ConvLayer::GetWeights(){
	return m_weights;
}

void ConvLayer::SetWeights(Filter w){
	m_weights = w;
}




ConvNeuronSet ConvLayer::GetNeurons(){
	return m_neurons;
}

void ConvLayer::SetNeurons(ConvNeuronSet neurons){
	m_neurons = neurons;
}



Filters ConvLayer::GetFilters(){
	return m_filters;
}

void ConvLayer::SetFilters(Filters f){
	m_filters = f;
}

FMS ConvLayer::GetFeatureMaps(){
	return m_featureMaps;
}

FeatureMap ConvLayer::GetFeatureMapAt(int i){
	return m_featureMaps[i];
}

void ConvLayer::SetFeatureMaps(FMS f){
	m_featureMaps = f;
}

void ConvLayer::addFeatureMap(FeatureMap f){
	m_featureMaps.push_back(f);
}



FullConnLayer::FullConnLayer(){
}

NeuronSet FullConnLayer::GetNeurons(){
	return m_neurons;
}

void FullConnLayer::SetNeurons(NeuronSet n){
	m_neurons = n;
}

void FullConnLayer::AddNeuron(Neuron* n){
	m_neurons.push_back(n);
}

vector<double> FullConnLayer::GetWeights(){
	return m_weights;
}

void FullConnLayer::SetWeights(vector<double> w){
	m_weights = w;
}

void FullConnLayer::AddWeight(double d){
	m_weights.push_back(d);
}

double FullConnLayer::GetWeightAt(int i){
	return m_weights[i];
}