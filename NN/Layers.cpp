#pragma once
#include "NeuralNetwork.h"

typedef unsigned int uint;
using std::make_pair;

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

ConvLayer::ConvLayer(int inpXY, int inpZ, int filtSize, int filtNum, int stride){
	ConvRow neuronRow;
	ConvNeuronSet neurons;

	SetFilterSize(filtSize);
	SetFilterNum(filtNum);
	SetStride(stride);
	SetInputXY(inpXY);
	SetInputZ(inpZ);

	for (uint z = 0; z < inpZ; z++){
		for (uint y = 0; y < inpXY; y++){
			for (uint x = 0; x < inpXY; x++){
				neuronRow.push_back(new ConvNeuron);
			}
			neurons.push_back(neuronRow);
			neuronRow.clear();
		}
		addFeatureMap(neurons);
		neurons.clear();
	}
}

ConvLayer::ConvLayer(ConvLayer prevLayer, int filterSize, int filterNum, int stride){
	ConvLayer previous = prevLayer;
	ConvRow neuronRow;
	ConvNeuronSet neurons;
	FMS prevFMS = previous.GetFeatureMaps();

	SetFilterSize(filterSize);
	SetFilterNum(filterNum);
	SetStride(stride);
	SetInputXY(prevFMS[0][0].size());
	SetInputZ(prevFMS.size());

	int fmPad = (prevLayer.GetFilterSize / 2) - 1;		//make these layer variables??
	int filtPad = (prevLayer.GetFilterSize / 2) + 1;
	int imgBound = prevLayer.GetInputXY - (prevLayer.GetFilterSize / 2);

	for (FeatureMap fm : previous.GetFeatureMaps()){
		for (Filter f : previous.GetFilters()){
			for (uint y = fmPad; y < imgBound; y += stride){
				for (uint x = fmPad; x < imgBound; x += stride){
					ConvNeuron* n = new ConvNeuron;
					for (int j = -fmPad; j < filtPad; j++){
						for (int k = -fmPad; k < filtPad; k++){
							n->addConnection(make_pair(fm[x + k][y + j]->GetValue(), f[k + 3][j + 3]));
						}
					}
					neuronRow.push_back(n);
				}
				neurons.push_back(neuronRow);
				neuronRow.clear();
			}
			addFeatureMap(neurons);
			neurons.clear();
		}
	}
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

FullConnLayer::FullConnLayer(ConvLayer prev, int size){

	for (uint i = 0; i < 256; i++){
		Neuron* n = new Neuron;
		for (FeatureMap fm : prev.GetFeatureMaps()){
			for (vector<ConvNeuron*> row : fm){
				for (ConvNeuron* conv : row){
					n->addConnection(make_pair(conv->GetValue(), GetWeightAt(i)));
				}
			}
		}
		AddNeuron(n);
	}
}

FullConnLayer::FullConnLayer(FullConnLayer prev, int size){
	int s = size;
	int t = prev.GetNeurons().size();
	NeuronSet ns = prev.GetNeurons();

	for (int i = 0; i < s; i++){
		Neuron* n = new Neuron;
		for (int j = 0; j < t; j++){
			n->addConnection(make_pair(ns[j]->GetValue(), GetWeightAt(i)));
		}
		AddNeuron(n);
	}
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