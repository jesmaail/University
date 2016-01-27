#pragma once
#include "NeuralNetwork.h"

int main(){
	return 0;
}

NeuralNetwork::NeuralNetwork(){
	vector<vector<int>> img;
	Preprocessor pp(img);
	/*ConvLayer input = GetInputLayer();
	ConvLayer second = GetSecondLayer();
	ConvLayer third = GetThirdLayer();
	FullConnLayer fourth = GetFourthLayer();
	FullConnLayer output = GetOutputLayer();*/

	populateInputLayer(pp.GetPPImg());
}



//Convolutional
void NeuralNetwork::populateInputLayer(vector<vector<int>> img){
	ConvLayer layer;
	vector<ConvNeuron> neuronRow;
	vector<vector<ConvNeuron>> neurons;

	vector<vector<double>> filter;
	filter.push_back({ 1, 2, 3, 4, 5, 6 ,7 ,8 });
	filter.push_back({ 1, 2, 3, 4, 5, 6, 7, 8 });
	filter.push_back({ 1, 2, 3, 4, 5, 6, 7, 8 });
	filter.push_back({ 1, 2, 3, 4, 5, 6, 7, 8 });
	filter.push_back({ 1, 2, 3, 4, 5, 6, 7, 8 });
	filter.push_back({ 1, 2, 3, 4, 5, 6, 7, 8 });
	filter.push_back({ 1, 2, 3, 4, 5, 6, 7, 8 });
	filter.push_back({ 1, 2, 3, 4, 5, 6, 7, 8 });

	layer.SetWeights(filter);
	layer.SetFilterNum(16);
	layer.SetFilterSize(8);
	layer.SetBias(0);

	int imgSize = 84;
	for (int i = 0; i < imgSize; i++){
		for (int j=0; j<imgSize; j++){
			ConvNeuron n;
			n.SetValue(img[j][i]);
			//n.SetWeights(filter); //now done to layer
			neuronRow.push_back(n);
		}

		neurons.push_back(neuronRow);
		neuronRow.clear();
	}

	layer.SetNeurons(neurons);
	SetInputLayer(layer);
	//m_inputLayer.SetNeurons(neurons);
}

//Convolutional
void NeuralNetwork::populateSecondLayer(){
	ConvLayer layer;
	ConvLayer* prevLayer = &GetInputLayer();
	int stride = prevLayer->GetStride();

	vector<ConvNeuron> neuronRow;
	vector<vector<ConvNeuron>> neurons;

	vector<vector<double>> filter;
	filter.push_back({ 1, 2, 3, 4});
	filter.push_back({ 1, 2, 3, 4});
	filter.push_back({ 1, 2, 3, 4});
	filter.push_back({ 1, 2, 3, 4});

	layer.SetWeights(filter);
	layer.SetFilterNum(32);
	layer.SetFilterSize(4);
	layer.SetBias(0);

	int imgSize = 84 - 4;
	for (int y = 3; y < imgSize; y += stride){
		for (int x = 3; x < imgSize; x += stride){
			ConvNeuron n;

			//Add Connections to neuron
			for (int i = y - 1; i <= y + 2; i++){
				for (int j = x - 1; j <= x + 2; j++){
					vector<vector<ConvNeuron>> cns = prevLayer->GetNeurons();
					vector<vector<double>> ws = prevLayer->GetWeights();

					ConvNeuron cn = cns[i][j];
					double w = ws[i][j];

					ConvConnection conn(cn, w);
					n.addConnection(conn);
				}
			}
			neuronRow.push_back(n);
		}
		neurons.push_back(neuronRow);
		neuronRow.clear();
	}

	layer.SetNeurons(neurons);
	SetSecondLayer(layer);
	//m_secondLayer.SetNeurons(neurons);
}

//Convolutional
void NeuralNetwork::populateThirdLayer(){
	ConvLayer layer;
	ConvLayer* prevLayer = &GetSecondLayer();
	int stride = prevLayer->GetStride();

	vector<ConvNeuron> neuronRow;
	vector<vector<ConvNeuron>> neurons;

	layer.SetBias(0);

	//needs new image size and for loop bounds for the smaller filter
	int imgSize = 84 - 4;
	for (int y = 3; y < imgSize; y += stride){
		for (int x = 3; x < imgSize; x += stride){
			ConvNeuron n;

			//Add Connections to neuron
			for (int i = y - 1; i <= y + 2; i++){
				for (int j = x - 1; j <= x + 2; j++){
					vector<vector<ConvNeuron>> cns = prevLayer->GetNeurons();
					vector<vector<double>> ws = prevLayer->GetWeights();

					ConvNeuron cn = cns[i][j];
					double w = ws[i][j];

					ConvConnection conn(cn, w);
					n.addConnection(conn);
				}
			}
			neuronRow.push_back(n);
		}
		neurons.push_back(neuronRow);
		neuronRow.clear();
	}

	layer.SetNeurons(neurons);
	SetThirdLayer(layer);
}

//Fully Connected
void NeuralNetwork::populateFourthLayer(){
	FullConnLayer layer;
	ConvLayer *prevLayer = &GetThirdLayer();
	vector<Neuron> neurons;

	double weight = 0;
	
	for (int k = 0; k < 256; k++){
		Neuron n;
		for (int i = 0; i < 9; i++){
			for (int j = 0; j < 9; j++){
				vector<vector<ConvNeuron>> cns = prevLayer->GetNeurons();
				ConvNeuron cn = cns[i][j];

				ConvConnection conn(cn, weight);
				n.addConnection(conn);
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
	FullConnLayer *prevLayer = &GetFourthLayer();
	vector<Neuron> neurons;

	int s = GetActionSetSize();
	int t = prevLayer->GetNeurons().size();
	double weight = 0;

	for (int i = 0; i < s; i++){
		Neuron n;
		for (int j = 0; j < t; j++){
			vector<Neuron> ns = prevLayer->GetNeurons();
			Neuron n = ns[j];
			Connection conn(n, weight);
			n.addConnection(conn);
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