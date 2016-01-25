#include "NeuralNetwork.h"

int main(){
	return 0;
}

NeuralNetwork::NeuralNetwork(){
	vector<vector<int>> img;
	Preprocessor pp(img);

	populateInputLayer(pp.GetPPImg());
}

void NeuralNetwork::populateInputLayer(vector<vector<int>> img){
	vector<Neuron> neuronRow;
	vector<vector<Neuron>> neurons;

	int imgSize = 84;
	for (int i = 0; i < imgSize; i++){
		for (int j=0; j<imgSize; j++){
			Neuron n;
			n.SetValue(img[j][i]);
			neuronRow.push_back(n);
		}

		neurons.push_back(neuronRow);
		neuronRow.clear();
	}

	m_inputLayer.SetNeurons(neurons);
}

void NeuralNetwork::populateSecondLayer(){
	vector<ConvNeuron> neuronRow;
	vector<vector<ConvNeuron>> neurons;

	int imgSize = 20;
	for (int i = 0; i < imgSize; i++){
		for (int j = 0; j < imgSize; j++){
			ConvNeuron n;
		}
	}
}

void NeuralNetwork::populateThirdLayer(){

}

void NeuralNetwork::populateFourthLayer(){

}

void NeuralNetwork::populateOutputLayer(){

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