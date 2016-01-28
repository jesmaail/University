#pragma once
#include "NeuralNetwork.h"
#include <iostream>

int main(){
	vector<vector<int>> imagePH;
	vector<int> phRow;
	for (int i = 0; i < 84; i++){
		for (int j = 0; j < 84; j++){
			phRow.push_back(i*j);
		}
		imagePH.push_back(phRow);
		phRow.clear();
	}
	//std::cout << imagePH.size() << ", " <<imagePH[0].size()<< std::endl;
	
	NeuralNetwork nn;
	nn.populateInputLayer(imagePH);
	vector<vector<ConvNeuron>> ns = nn.GetInputLayer().GetNeurons();
	int output1 = ns.size();
	int output2 = ns[0].size();
	
	std::cout << "Layer 1: " << output1 << ", " << output2 << std::endl;


	nn.populateSecondLayer();
	ns = nn.GetSecondLayer().GetNeurons();
	output1 = ns.size();
	output2 = ns[0].size();

	std::cout << "Layer 2: " << output1 << ", " << output2 << std::endl;

	nn.populateThirdLayer();
	ns = nn.GetThirdLayer().GetNeurons();
	output1 = ns.size();
	output2 = ns[0].size();

	std::cout << "Layer 3: " << output1 << ", " << output2 << std::endl;


	
	nn.populateFourthLayer();
	vector<Neuron> n = nn.GetFourthLayer().GetNeurons();
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
	layer.SetStride(4);
	layer.SetBias(0);

	int imgSize = 84;
	int iBound = img.size();
	int jBound = img[0].size();
	for (int i = 0; i < iBound; i++){
		for (int j = 0; j < jBound; j++){
			ConvNeuron n;
			n.SetValue(img[j][i]);
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
	ConvLayer prevLayer = GetInputLayer();
	int stride = prevLayer.GetStride();

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
	layer.SetStride(2);
	layer.SetBias(0);

	vector<vector<ConvNeuron>> cns = prevLayer.GetNeurons();
	vector<vector<double>> ws = prevLayer.GetWeights();

	//need to fix loop here!
	int imgSize = 84 - 4;
	for (int y = 3; y <= imgSize; y += stride){
		for (int x = 3; x <= imgSize; x += stride){
			ConvNeuron n;

			//Add Connections to neuron
			//Loop through neurons 
			for (int i = y - 3; i <= y + 4; i++){
				for (int j = x - 3; j <= x + 4; j++){		

					//Loop through weights (is it too slow?)
					for (int wy = 0; wy < 8; wy++){
						/*n.addConnection(ConvConnection(cns[j][i], ws[0][wy]));
						n.addConnection(ConvConnection(cns[j][i], ws[1][wy]));
						n.addConnection(ConvConnection(cns[j][i], ws[2][wy]));
						n.addConnection(ConvConnection(cns[j][i], ws[3][wy]));
						n.addConnection(ConvConnection(cns[j][i], ws[4][wy]));
						n.addConnection(ConvConnection(cns[j][i], ws[5][wy]));
						n.addConnection(ConvConnection(cns[j][i], ws[6][wy]));
						n.addConnection(ConvConnection(cns[j][i], ws[7][wy]));*/
						for (int wx = 0; wx < 8; wx++){
							n.addConnection(ConvConnection(cns[j][i], ws[wx][wy]));
						}
					}
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
	ConvLayer prevLayer = GetSecondLayer();
	int stride = prevLayer.GetStride();

	vector<ConvNeuron> neuronRow;
	vector<vector<ConvNeuron>> neurons;

	layer.SetBias(0);

	vector<vector<ConvNeuron>> cns = prevLayer.GetNeurons();
	vector<vector<double>> ws = prevLayer.GetWeights();

	//needs new image size and for loop bounds for the smaller filter
	int imgSize = 20 - 2;
	for (int y = 1; y < imgSize; y += stride){
		for (int x = 1; x < imgSize; x += stride){
			ConvNeuron n;

			//Add Connections to neuron
			for (int i = y - 1; i <= y + 2; i++){
				for (int j = x - 1; j <= x + 2; j++){	

					//Loop through weights (is it too slow?)
					for (int wy = 0; wy < 4; wy++){						
						for (int wx = 0; wx < 4; wx++){
							n.addConnection(ConvConnection(cns[j][i], ws[wx][wy]));
						}
					}
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
	ConvLayer prevLayer = GetThirdLayer();
	vector<Neuron> neurons;

	double weight = 0;

	vector<vector<ConvNeuron>> cns = prevLayer.GetNeurons();
	
	for (int k = 0; k < 256; k++){
		Neuron n;
		for (int i = 0; i < 9; i++){
			for (int j = 0; j < 9; j++){
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