#pragma once
#include "NeuralNetwork.h"
#include <iostream>

typedef unsigned int uint;

using std::make_pair;

int main(){
	Image imagePH;
	vector<int> phRow;
	for (uint i = 0; i < 84; i++){
		for (uint j = 0; j < 84; j++){
			phRow.push_back(i*j);
		}
		imagePH.push_back(phRow);
		phRow.clear();
	}
	//std::cout << imagePH.size() << ", " <<imagePH[0].size()<< std::endl;
	
	int output1, output2, output3;
	FMS fs;
	NeuralNetwork nn;
	nn.populateInputLayer(imagePH);
	ConvNeuronSet ns = nn.GetInputLayer().GetNeurons();
	output1 = ns.size();
	output2 = ns[0].size();	
	std::cout << "Layer 1: " << output1 << ", " << output2 << std::endl;



	nn.populateSecondLayer();
	ns = nn.GetSecondLayer().GetFeatureMapAt(0);
	fs = nn.GetSecondLayer().GetFeatureMaps();
	output1 = fs.size();
	output2 = fs[0].size();
	output3 = fs[0][0].size();
	std::cout << "Layer 2: " << output1 << ", " << output2  << ", " << output3 << std::endl;


	nn.populateThirdLayer();
	ns = nn.GetThirdLayer().GetFeatureMapAt(0);
	fs = nn.GetThirdLayer().GetFeatureMaps();
	output1 = fs.size();
	output2 = fs[0].size();
	output3 = fs[0][0].size();
	std::cout << "Layer 3: " << output1 << ", " << output2 << ", " << output3 << std::endl;


	nn.populateFourthLayer();
	NeuronSet n = nn.GetFourthLayer().GetNeurons();
	output1 = n.size();
	std::cout << "Layer 4: " << output1 << std::endl;


	nn.SetActionSetSize(4);
	nn.populateOutputLayer();
	n = nn.GetOutputLayer().GetNeurons();	
	output1 = n.size();
	std::cout << "Layer 5: " << output1 << std::endl;

	
	//################################
	// Just to keep debug window open!
	int ph;
	std::cin >> ph;
	//################################

	return 0;
}

NeuralNetwork::NeuralNetwork(){
	//Image img;
	//Preprocessor pp(img);
	//populateInputLayer(pp.GetPPImg());
}



//Convolutional
void NeuralNetwork::populateInputLayer(Image img){
	ConvLayer layer;
	ConvRow neuronRow;
	ConvNeuronSet neurons;

	Filter filter;
	filter.push_back({ 1, 2, 3, 4, 5, 6 ,7 ,8 });
	filter.push_back({ 1, 2, 3, 4, 5, 6, 7, 8 });
	filter.push_back({ 1, 2, 3, 4, 5, 6, 7, 8 });
	filter.push_back({ 1, 2, 3, 4, 5, 6, 7, 8 });
	filter.push_back({ 1, 2, 3, 4, 5, 6, 7, 8 });
	filter.push_back({ 1, 2, 3, 4, 5, 6, 7, 8 });
	filter.push_back({ 1, 2, 3, 4, 5, 6, 7, 8 });
	filter.push_back({ 1, 2, 3, 4, 5, 6, 7, 8 });

	Filters fs;
	
	for (uint i = 0; i < 4; i++){ // <16  or 4 (feature map confusion)
		fs.push_back(filter);
	}
	layer.SetFilters(fs);
	layer.SetWeights(filter);
	layer.SetFilterNum(16);
	layer.SetFilterSize(8);
	layer.SetStride(4);
	layer.SetBias(0);

	int imgSize = 84;
	int iBound = img.size();
	int jBound = img[0].size();
	for (uint i = 0; i < iBound; i++){
		for (uint j = 0; j < jBound; j++){
			ConvNeuron n;
			n.SetValue(img[j][i]);
			neuronRow.push_back(n);
		}

		neurons.push_back(neuronRow);
		neuronRow.clear();
	}

	layer.SetNeurons(neurons);
	SetInputLayer(layer);
}

//Convolutional
void NeuralNetwork::populateSecondLayer(){
	ConvLayer layer;
	ConvLayer prevLayer = GetInputLayer();
	int stride = prevLayer.GetStride();

	ConvRow neuronRow;
	ConvNeuronSet neurons;

	Filter filter;
	filter.push_back({ 1, 2, 3, 4});
	filter.push_back({ 1, 2, 3, 4});
	filter.push_back({ 1, 2, 3, 4});
	filter.push_back({ 1, 2, 3, 4});

	Filters fs;

	for (int i = 0; i < 2; i++){// < 32  or 2 (feature map confusion)
		fs.push_back(filter);
	}
	layer.SetFilters(fs);

	layer.SetWeights(filter);
	layer.SetFilterNum(32);
	layer.SetFilterSize(4);
	layer.SetStride(2);
	layer.SetBias(0);

	ConvNeuronSet cns = prevLayer.GetNeurons();
	int imgSize = 84 - 4;

	for (Filter f : prevLayer.GetFilters()){
		for (uint y = 3; y < imgSize; y += stride){
			for (uint x = 3; x < imgSize; x += stride){
				ConvNeuron n;
				for (int j = y - 3; j <= y + 4; j++){
					for (int k = x - 3; k <= x + 4; k++){
						for (uint wy = 0; wy < 8; wy++){
							for (uint wx = 0; wx < 8; wx++){
								n.addConnection(make_pair(cns[j][k].GetValue(), f[wx][wy]));
							}
						}
					}
				}
				neuronRow.push_back(n);
			}
			neurons.push_back(neuronRow);
			neuronRow.clear();			
		}
		layer.addFeatureMap(neurons);
		neurons.clear();	
	}
	SetSecondLayer(layer);
}

//Convolutional
void NeuralNetwork::populateThirdLayer(){
	ConvLayer layer;
	ConvLayer prevLayer = GetSecondLayer();
	int stride = prevLayer.GetStride();

	ConvRow neuronRow;
	ConvNeuronSet neurons;

	layer.SetBias(0);
	int imgSize = 20-2;

	for (FeatureMap cns : prevLayer.GetFeatureMaps()){
		for (Filter f : prevLayer.GetFilters()){
			for (int y = 1; y < imgSize; y += stride){
				for (int x = 1; x < imgSize; x += stride){
					ConvNeuron n;

					for (int j = y - 1; j <= y + 2; j++){
						for (int k = x - 1; k <= x + 2; k++){

							for (int wy = 0; wy < 4; wy++){
								for (int wx = 0; wx < 4; wx++){
									n.addConnection(make_pair(cns[j][k].GetValue(), f[wx][wy]));
								}
							}

						}
					}
					neuronRow.push_back(n);
				}
				neurons.push_back(neuronRow);
				neuronRow.clear();
			}
			layer.addFeatureMap(neurons);
			neurons.clear();
		}
	}
	SetThirdLayer(layer);
}

//Fully Connected
void NeuralNetwork::populateFourthLayer(){
	FullConnLayer layer;
	ConvLayer prevLayer = GetThirdLayer();
	NeuronSet neurons;

	double weight = 1;
	for (uint i = 0; i < 256; i++){
		Neuron n;
		for (FeatureMap fm : prevLayer.GetFeatureMaps()){
			for (vector<ConvNeuron> row : fm){
				for (ConvNeuron conv : row){
					n.addConnection(make_pair(conv.GetValue(), weight));
				}
			}
		}
		neurons.push_back(n);		
	}
	layer.SetNeurons(neurons);
	SetFourthLayer(layer);
}

//Fully Connected
void NeuralNetwork::populateOutputLayer(){
	FullConnLayer layer;
	FullConnLayer prevLayer = GetFourthLayer();
	NeuronSet neurons;

	int s = GetActionSetSize();
	int t = prevLayer.GetNeurons().size();
	double weight = 1;
	NeuronSet ns = prevLayer.GetNeurons();

	for (int i = 0; i < s; i++){
		Neuron n;		
		for (int j = 0; j < t; j++){			
			//n.addConnection(make_pair(ns[j], weight));
			//n.AddToValue(ns[j].GetValue() * weight);
		}
		neurons.push_back(n);
	}
	layer.SetNeurons(neurons);
	SetOutputLayer(layer);
}




ConvLayer NeuralNetwork::GetInputLayer(){
	return m_inputLayer;
}

ConvLayer NeuralNetwork::GetSecondLayer(){
	return m_secondLayer;
}

ConvLayer NeuralNetwork::GetThirdLayer(){
	return m_thirdLayer;
}

FullConnLayer NeuralNetwork::GetFourthLayer(){
	return m_fourthLayer;
}

FullConnLayer NeuralNetwork::GetOutputLayer(){
	return m_outputLayer;
}




void NeuralNetwork::SetInputLayer(ConvLayer l){
	m_inputLayer = l;
}

void NeuralNetwork::SetSecondLayer(ConvLayer l){
	m_secondLayer = l;
}

void NeuralNetwork::SetThirdLayer(ConvLayer l){
	m_thirdLayer = l;
}

void NeuralNetwork::SetFourthLayer(FullConnLayer l){
	m_fourthLayer = l;
}

void NeuralNetwork::SetOutputLayer(FullConnLayer l){
	m_outputLayer = l;
}




vector<ConvLayer> NeuralNetwork::GetConvLayers(){
	return m_convLayers;
}

void NeuralNetwork::SetConvLayers(vector<ConvLayer> layers){
	m_convLayers = layers;
}




vector<FullConnLayer> NeuralNetwork::GetFullConnLayers(){
	return m_fcLayers;
}

void NeuralNetwork::SetFullConnLayers(vector<FullConnLayer> layers){
	m_fcLayers = layers;
}




int NeuralNetwork::GetActionSetSize(){
	return m_actionSetSize;
}

void NeuralNetwork::SetActionSetSize(int s){
	m_actionSetSize = s;
}