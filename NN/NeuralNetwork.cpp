#pragma once
#include "NeuralNetwork.h"
#include <iostream>

typedef unsigned int uint;

using std::make_pair;

int main(){
	Image imagePH;		//Create placeholder images
	vector<int> phRow;
	for (uint i = 0; i < 84; i++){
		for (uint j = 0; j < 84; j++){
			phRow.push_back(i+j);
		}
		imagePH.push_back(phRow);
		phRow.clear();
	}
	vector<Image> imgs;
	for (uint i = 0; i < 4; i++){
		imgs.push_back(imagePH);
	}
	
	NeuralNetwork nn(imgs);
	
	//################################
	// Just to keep debug window open!
	int ph;
	std::cin >> ph;
	//################################

	return 0;
}

NeuralNetwork::NeuralNetwork(Images imgs){
	m_input = imgs;
	Filter filter;
	Filters fs;
	filter.push_back({ 1, 1, 1, 1, 1, 1, 1, 1 });
	filter.push_back({ 1, 2, 2, 2, 2, 2, 2, 1 });
	filter.push_back({ 1, 2, 2, 1, 2, 1, 2, 1 });
	filter.push_back({ 1, 2, 1, 3, 3, 2, 2, 1 });
	filter.push_back({ 1, 2, 2, 3, 3, 1, 2, 1 });
	filter.push_back({ 1, 2, 1, 2, 1, 2, 2, 1 });
	filter.push_back({ 1, 2, 2, 2, 2, 2, 2, 1 });
	filter.push_back({ 1, 1, 1, 1, 1, 1, 1, 1 });	
	for (uint i = 0; i < 4; i++){
		fs.push_back(filter);
	}
	m_inputLayer.SetFilters(fs);

	filter.clear();
	fs.clear();
	filter.push_back({ 1, 1, 1, 1 });
	filter.push_back({ 1, 2, 2, 1 });
	filter.push_back({ 1, 3, 3, 1 });
	filter.push_back({ 1, 2, 2, 1 });
	for (int i = 0; i < 2; i++){
		fs.push_back(filter);
	}
	m_secondLayer.SetFilters(fs);
	SetActionSetSize(4);
	std::cout << "Filters set" << std::endl;

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

	//int output4 = fs[0][0][0].GetConnections().size();
	//std::cout << "ConnCount: " << output4 << std::endl;
	//----

	for (FeatureMap fm : m_secondLayer.GetFeatureMaps()){
		for (ConvRow cr : fm){
			for (ConvNeuron* n : cr){
				n->SetValue(n->CalculateValue());
				n->Activation();
			}
		}
	}
	std::cout << "Neuron calcs done..." << std::endl;

	//Test for output
	/*for (FeatureMap cns : m_secondLayer.GetFeatureMaps()){
		for (ConvRow cr : cns){
			for (ConvNeuron* n : cr){
				std::cout << n->GetValue() << "!";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}*/


	populateThirdLayer();
	//Test
	ns = GetThirdLayer().GetFeatureMapAt(0);
	fs = GetThirdLayer().GetFeatureMaps();
	output1 = fs.size();
	output2 = fs[0].size();
	output3 = fs[0][0].size();
	std::cout << "Layer 3: " << output1 << ", " << output2 << ", " << output3 << std::endl;
	//output4 = fs[0][0][0].GetConnections().size();
	//std::cout << "ConnCount: " << output4 << std::endl;
	//----
	for (FeatureMap fm : m_thirdLayer.GetFeatureMaps()){
		for (ConvRow cr : fm){
			for (ConvNeuron* n : cr){
				n->SetValue(n->CalculateValue());
				n->Activation();
			}
		}
	}
	std::cout << "Neuron calcs done..." << std::endl;


	populateFourthLayer();
	//Test
	NeuronSet n = GetFourthLayer().GetNeurons();
	output1 = n.size();
	std::cout << "Layer 4: " << output1 << std::endl;
	//----
	for (Neuron* n : m_fourthLayer.GetNeurons()){
		n->SetValue(n->CalculateValue());
		n->Activation();
	}
	std::cout << "Neuron calcs done..." << std::endl;


	populateOutputLayer();
	//Test
	n = GetOutputLayer().GetNeurons();
	output1 = n.size();
	std::cout << "Layer 5: " << output1 << std::endl;
	//----
	for (Neuron* n : m_outputLayer.GetNeurons()){
		n->SetValue(n->CalculateValue());
		n->Activation();
	}
}



//Convolutional
void NeuralNetwork::populateInputLayer(){
	ConvRow neuronRow;
	ConvNeuronSet neurons;
	
	m_inputLayer.SetFilterSize(8);
	m_inputLayer.SetFilterNum(16);
	m_inputLayer.SetStride(4);
	m_inputLayer.SetBias(1);
	Images imgs = m_input;

	for (Image img : imgs){
		int imgSize = 84;
		int iBound = img.size();
		int jBound = img[0].size();
		for (uint i = 0; i < iBound; i++){
			for (uint j = 0; j < jBound; j++){
				ConvNeuron* n = new ConvNeuron;
				n->SetValue(img[j][i]);
				neuronRow.push_back(n);
			}

			neurons.push_back(neuronRow);
			neuronRow.clear();
		}
		m_inputLayer.addFeatureMap(neurons);
	}
}

//Convolutional
void NeuralNetwork::populateSecondLayer(){
	int stride = m_inputLayer.GetStride();

	ConvRow neuronRow;
	ConvNeuronSet neurons;

	m_secondLayer.SetFilterNum(32);
	m_secondLayer.SetFilterSize(4);
	m_secondLayer.SetStride(2);
	m_secondLayer.SetBias(1);

	ConvNeuronSet cns = m_inputLayer.GetNeurons();
	int imgSize = 84 - 4;
	for (FeatureMap cns : m_inputLayer.GetFeatureMaps()){
		for (Filter f : m_inputLayer.GetFilters()){
			for (uint y = 3; y < imgSize; y += stride){
				for (uint x = 3; x < imgSize; x += stride){
					ConvNeuron* n = new ConvNeuron;
					n->SetBias(m_secondLayer.GetBias());
					for (int j = -3; j < 5; j++){
						for (int k = -3; k < 5; k++){
							//std::cout << cns[x + k][y + j]->GetValue() << std::endl;							
							n->addConnection(make_pair(cns[x + k][y + j]->GetValue(), f[k + 3][j + 3]));
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
}

//Convolutional
void NeuralNetwork::populateThirdLayer(){
	int stride = m_secondLayer.GetStride();

	ConvRow neuronRow;
	ConvNeuronSet neurons;

	m_thirdLayer.SetBias(1);
	int imgSize = 20-2;

	for (FeatureMap cns : m_secondLayer.GetFeatureMaps()){
		for (Filter f : m_secondLayer.GetFilters()){
			for (int y = 1; y < imgSize; y += stride){
				for (int x = 1; x < imgSize; x += stride){
					ConvNeuron* n = new ConvNeuron;
					n->SetBias(m_thirdLayer.GetBias());
					for (int j = -1; j < 3; j++){
						for (int k = -1; k < 3; k++){
							//std::cout << cns[x + k][y + j]->GetValue() << std::endl;
							n->addConnection(make_pair(cns[x + k][y + j]->GetValue(), f[k + 1][j + 1]));
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
}

//Fully Connected
void NeuralNetwork::populateFourthLayer(){
	m_fourthLayer.SetBias(1);

	double weight = 1;
	for (uint i = 0; i < 256; i++){
		Neuron* n = new Neuron;
		n->SetBias(m_fourthLayer.GetBias());
		for (FeatureMap fm : m_thirdLayer.GetFeatureMaps()){
			for (vector<ConvNeuron*> row : fm){
				for (ConvNeuron* conv : row){
					n->addConnection(make_pair(conv->GetValue(), weight));
				}
			}
		}
		m_fourthLayer.AddNeuron(n);
	}
}

//Fully Connected
void NeuralNetwork::populateOutputLayer(){
	int s = GetActionSetSize();
	int t = m_fourthLayer.GetNeurons().size();
	double weight = 1;
	m_outputLayer.SetBias(1);
	NeuronSet ns = m_fourthLayer.GetNeurons();

	for (int i = 0; i < s; i++){
		Neuron* n = new Neuron;
		n->SetBias(m_outputLayer.GetBias());
		for (int j = 0; j < t; j++){			
			n->addConnection(make_pair(ns[j]->GetValue(), weight));
		}
		m_outputLayer.AddNeuron(n);
	}
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