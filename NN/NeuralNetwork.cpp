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
	vector<Image> imgs;
	for (uint i = 0; i < 4; i++){
		imgs.push_back(imagePH);
	}
	
	int output1, output2, output3;
	FMS fs;
	NeuralNetwork nn(imgs);
	/*ConvNeuronSet ns;
	nn.populateInputLayer();
	ns = nn.GetInputLayer().GetFeatureMapAt(0);
	fs = nn.GetInputLayer().GetFeatureMaps();
	output1 = fs.size();
	output2 = fs[0].size();
	output3 = fs[0][0].size();
	std::cout << "Layer 1: " << output1 << ", " << output2 << ", " << output3 << std::endl;
	/*
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
	*/
	
	//################################
	// Just to keep debug window open!
	int ph;
	std::cin >> ph;
	//################################

	return 0;
}

NeuralNetwork::NeuralNetwork(Images imgs){
	m_input = imgs;
	//Set Layer filters 
	Filter filter;
	Filters fs;
	filter.push_back({ 1, 2, 3, 4, 5, 6, 7, 8 });
	filter.push_back({ 1, 2, 3, 4, 5, 6, 7, 8 });
	filter.push_back({ 1, 2, 3, 4, 5, 6, 7, 8 });
	filter.push_back({ 1, 2, 3, 4, 5, 6, 7, 8 });
	filter.push_back({ 1, 2, 3, 4, 5, 6, 7, 8 });
	filter.push_back({ 1, 2, 3, 4, 5, 6, 7, 8 });
	filter.push_back({ 1, 2, 3, 4, 5, 6, 7, 8 });
	filter.push_back({ 1, 2, 3, 4, 5, 6, 7, 8 });	
	for (uint i = 0; i < 4; i++){
		fs.push_back(filter);
	}
	m_inputLayer.SetFilters(fs);

	filter.clear();
	fs.clear();
	filter.push_back({ 1, 2, 3, 4 });
	filter.push_back({ 1, 2, 3, 4 });
	filter.push_back({ 1, 2, 3, 4 });
	filter.push_back({ 1, 2, 3, 4 });
	for (int i = 0; i < 2; i++){
		fs.push_back(filter);
	}
	m_secondLayer.SetFilters(fs);
	SetActionSetSize(4);

	//Call Forward Prop
	ForwardProp();

	//Call backward Prop
}

void::NeuralNetwork::ForwardProp(){
	int output1, output2, output3;
	FMS fs;
	ConvNeuronSet ns;


	populateInputLayer();
	//Test
	ns = GetInputLayer().GetFeatureMapAt(0);
	fs = GetInputLayer().GetFeatureMaps();
	output1 = fs.size();
	output2 = fs[0].size();
	output3 = fs[0][0].size();
	std::cout << "Layer 1: " << output1 << ", " << output2 << ", " << output3 << std::endl;
	//----

	populateSecondLayer();
	//Test
	ns = GetSecondLayer().GetFeatureMapAt(0);
	fs = GetSecondLayer().GetFeatureMaps();
	output1 = fs.size();
	output2 = fs[0].size();
	output3 = fs[0][0].size();
	std::cout << "Layer 2: " << output1 << ", " << output2 << ", " << output3 << std::endl;
	//----
	for (ConvRow cr : m_secondLayer.GetNeurons()){
		for (ConvNeuron n : cr){
			n.SetValue(n.CalculateValue());
			n.SetValue(n.Activation());
		}
	}
	std::cout << "Neuron calcs done..." << std::endl;


	populateThirdLayer();
	//Test
	ns = GetThirdLayer().GetFeatureMapAt(0);
	fs = GetThirdLayer().GetFeatureMaps();
	output1 = fs.size();
	output2 = fs[0].size();
	output3 = fs[0][0].size();
	std::cout << "Layer 3: " << output1 << ", " << output2 << ", " << output3 << std::endl;
	//----
	for (ConvRow cr : m_thirdLayer.GetNeurons()){
		for (ConvNeuron n : cr){
			n.SetValue(n.CalculateValue());
			n.SetValue(n.Activation());
		}
	}
	std::cout << "Neuron calcs done..." << std::endl;


	populateFourthLayer();
	//Test
	NeuronSet n = GetFourthLayer().GetNeurons();
	output1 = n.size();
	std::cout << "Layer 4: " << output1 << std::endl;
	//----
	for (Neuron n : m_fourthLayer.GetNeurons()){
		n.SetValue(n.CalculateValue());
		n.SetValue(n.Activation());
	}
	std::cout << "Neuron calcs done..." << std::endl;


	populateOutputLayer();
	//Test
	n = GetOutputLayer().GetNeurons();
	output1 = n.size();
	std::cout << "Layer 5: " << output1 << std::endl;
	//----
	for (Neuron n : m_outputLayer.GetNeurons()){
		n.SetValue(n.CalculateValue());
		n.SetValue(n.Activation());
		std::cout << n.GetValue() << std::endl;
	}
}



//Convolutional
void NeuralNetwork::populateInputLayer(){
	//ConvLayer layer;
	ConvRow neuronRow;
	ConvNeuronSet neurons;

	
	//m_inputLayer.SetWeights(filter);
	m_inputLayer.SetFilterSize(8);
	m_inputLayer.SetFilterNum(16);
	m_inputLayer.SetStride(4);
	m_inputLayer.SetBias(1);

	/*
	layer.SetFilters(fs);
	layer.SetWeights(filter);
	layer.SetFilterNum(16);
	layer.SetFilterSize(8);
	layer.SetStride(4);
	layer.SetBias(0);
	*/
	Images imgs = m_input;

	for (Image img : imgs){
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
		m_inputLayer.addFeatureMap(neurons);
		//layer.addFeatureMap(neurons);
	}
	//SetInputLayer(layer);
}

//Convolutional
void NeuralNetwork::populateSecondLayer(){
	//ConvLayer layer;
	//ConvLayer prevLayer = GetInputLayer();
	//int stride = prevLayer.GetStride();
	int stride = m_inputLayer.GetStride();

	ConvRow neuronRow;
	ConvNeuronSet neurons;

	
	//m_secondLayer.SetWeights(filter);
	m_secondLayer.SetFilterNum(32);
	m_secondLayer.SetFilterSize(4);
	m_secondLayer.SetStride(2);
	m_secondLayer.SetBias(1);
	
	/*layer.SetFilters(fs);
	layer.SetWeights(filter);
	layer.SetFilterNum(32);
	layer.SetFilterSize(4);
	layer.SetStride(2);
	layer.SetBias(0);*/

	ConvNeuronSet cns = m_inputLayer.GetNeurons();
	int imgSize = 84 - 4;
	for (FeatureMap cns : m_inputLayer.GetFeatureMaps()){
		for (Filter f : m_inputLayer.GetFilters()){
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
			m_secondLayer.addFeatureMap(neurons);
			neurons.clear();
		}
	}
	//SetSecondLayer(layer);
}

//Convolutional
void NeuralNetwork::populateThirdLayer(){
	//ConvLayer layer;
	//ConvLayer prevLayer = GetSecondLayer();
	int stride = m_secondLayer.GetStride();

	ConvRow neuronRow;
	ConvNeuronSet neurons;

	m_thirdLayer.SetBias(1);
	int imgSize = 20-2;

	for (FeatureMap cns : m_secondLayer.GetFeatureMaps()){
		for (Filter f : m_secondLayer.GetFilters()){
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
			m_thirdLayer.addFeatureMap(neurons);
			neurons.clear();
		}
	}
	//SetThirdLayer(layer);
}

//Fully Connected
void NeuralNetwork::populateFourthLayer(){
	//FullConnLayer layer;
	//ConvLayer prevLayer = GetThirdLayer();
	//NeuronSet neurons;
	m_fourthLayer.SetBias(1);

	double weight = 1;
	for (uint i = 0; i < 256; i++){
		//std::cout << i << std::endl;
		Neuron n;
		for (FeatureMap fm : m_thirdLayer.GetFeatureMaps()){
			for (vector<ConvNeuron> row : fm){
				for (ConvNeuron conv : row){
					n.addConnection(make_pair(conv.GetValue(), weight));
				}
			}
		}
		//neurons.push_back(n);	
		m_fourthLayer.AddNeuron(n);
	}
	//m_fourthLayer.SetNeurons(neurons);
	//SetFourthLayer(layer);
}

//Fully Connected
void NeuralNetwork::populateOutputLayer(){
	int s = GetActionSetSize();
	int t = m_fourthLayer.GetNeurons().size();
	double weight = 1;
	m_outputLayer.SetBias(1);
	NeuronSet ns = m_fourthLayer.GetNeurons();

	for (int i = 0; i < s; i++){
		Neuron n;		
		for (int j = 0; j < t; j++){			
			n.addConnection(make_pair(ns[j].GetValue(), weight));
			//n.AddToValue(ns[j].GetValue() * weight);
		}
		//neurons.push_back(n);
		m_outputLayer.AddNeuron(n);
	}
	//m_outputLayer.SetNeurons(neurons);
	//SetOutputLayer(layer);
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

Images NeuralNetwork::GetInput(){
	return m_input;
}

void NeuralNetwork::SetInput(Images i){
	m_input = i;
}

int NeuralNetwork::GetActionSetSize(){
	return m_actionSetSize;
}

void NeuralNetwork::SetActionSetSize(int s){
	m_actionSetSize = s;
}