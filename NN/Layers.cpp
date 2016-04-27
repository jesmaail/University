#pragma once
#include "NeuralNetwork.h"
#include <iostream>

typedef unsigned int uint;
using std::make_pair;
using std::make_tuple;

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

ConvLayer::ConvLayer(Images imgs, int filtSize, int filtNum, int stride){
	ConvRow neuronRow;
	ConvNeuronSet neurons;
	m_previous = 0;

	SetFilterSize(filtSize);
	SetFilterNum(filtNum);
	SetStride(stride);
	SetInputXY(84);
	SetInputZ(imgs.size());
	int iBound, jBound;

	for (Image img : imgs){
		iBound = img.size();
		jBound = img[0].size();
		for (uint i = 0; i < iBound; i++){
			for (uint j = 0; j < jBound; j++){
				ConvNeuron* n = new ConvNeuron;
				n->SetValue(img[j][i]);
				neuronRow.push_back(n);
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
	m_previous = &prevLayer;

	SetFilterSize(filterSize);
	SetFilterNum(filterNum);
	SetStride(stride);

	int fmPad = (prevLayer.GetFilterSize() / 2) - 1;
	int filtPad = (prevLayer.GetFilterSize() / 2) + 1;
	int imgBound = prevLayer.GetInputXY() - (prevLayer.GetFilterSize() / 2);
	int str = prevLayer.GetStride();

	ThrIndex nIndex, wIndex;

	for (FeatureMap fm : previous.GetFeatureMaps()){
		for (uint d = 0; d < previous.GetFilters().size(); d++){
			for (uint y = fmPad; y < imgBound; y += str){
				for (uint x = fmPad; x < imgBound; x += str){
					ConvNeuron* n = new ConvNeuron;
					for (int j = -fmPad; j < filtPad; j++){
						for (int k = -fmPad; k < filtPad; k++){
							wIndex = make_tuple(d, k + fmPad, j + fmPad);
							n->addConnection(make_pair(fm[x + k][y + j]->GetValue(), wIndex));
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

	/*for (uint c = 0; c < previous.GetFeatureMaps().size(); c++){
		for (uint d = 0; d < previous.GetFilters().size(); d++){
			for (uint y = fmPad; y < imgBound; y += str){
				for (uint x = fmPad; x < imgBound; x += str){
					ConvNeuron* n = new ConvNeuron;
					for (int j = -fmPad; j < filtPad; j++){
						for (int k = -fmPad; k < filtPad; k++){
							wIndex = make_tuple(d, k + fmPad, j + fmPad);
							n->addConnection(make_pair(prevNeuron, wIndex));
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
	}*/
	FMS fms = GetFeatureMaps();
	SetInputXY(fms[0][0].size());
	SetInputZ(fms.size());
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

int ConvLayer::GetInputXY(){
	return m_inputXY;
}

void ConvLayer::SetInputXY(int xy){
	m_inputXY = xy;
}

int ConvLayer::GetInputZ(){
	return m_inputZ;
}

void ConvLayer::SetInputZ(int z){
	m_inputZ = z;
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

void ConvLayer::activateNeurons(){
	for (FeatureMap fm : GetFeatureMaps()){
		for (ConvRow cr : fm){
			for (ConvNeuron* n : cr){
				n->SetValue(n->CalculateValue(m_previous));
				n->Activation();
			}
		}
	}
}


FullConnLayer::FullConnLayer(){
}

FullConnLayer::FullConnLayer(ConvLayer prev, int size){
	ThrIndex nIndex, wIndex;
	int cr;
	FeatureMap fm;
	m_previous = &prev;
	Neuron prevNeuron;
	for (uint i = 0; i < size; i++){
		Neuron* n = new Neuron;
		for (FeatureMap fm : prev.GetFeatureMaps()){
			for (vector<ConvNeuron*> row : fm){
				for (ConvNeuron* conv : row){
					wIndex = make_tuple(0, 0, i);
					n->addConnection(make_pair(conv->GetValue(), wIndex));
				}
			}
		}
		AddNeuron(n);
	}
	/*for (uint i = 0; i < size; i++){
		Neuron* n = new Neuron;
		for (uint c = 0; c < prev.GetFeatureMaps().size(); c++){
			fm = prev.GetFeatureMapAt(c);
			for (uint y = 0; y < fm.size(); y++){
				cr = fm[y].size();
				for (uint x = 0; x < cr; x++){				
					//nIndex = make_tuple(c, x, y);
					prevNeuron = *prev.GetFeatureMapAt(c)[x][y];
					wIndex = make_tuple(0, 0, i);
					n->addConnection(make_pair(prevNeuron, wIndex));
				}
			}
		}
		AddNeuron(n);
	}*/
}

FullConnLayer::FullConnLayer(FullConnLayer prev, int size){
	ThrIndex nIndex, wIndex;
	int s = size;
	int t = prev.GetNeurons().size();
	NeuronSet ns = prev.GetNeurons();
	m_previous = &prev;
	Neuron prevNeuron;

	for (int i = 0; i < s; i++){
		Neuron* n = new Neuron;
		for (int j = 0; j < t; j++){
			//nIndex = make_tuple(0, 0, j);
			prevNeuron = *ns[j];
			wIndex = make_tuple(0, 0, i);
			//n->addConnection(make_pair(prevNeuron, wIndex));
			n->addConnection(make_pair(ns[j]->GetValue(), wIndex));
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

void FullConnLayer::activateNeurons(){
	for (Neuron* n : GetNeurons()){
		n->SetValue(n->CalculateValue(m_previous));
		n->Activation();
	}
}