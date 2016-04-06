#pragma once
#include <iostream>
#include "NeuralNetwork.h"
#include "Agent.h"
#include "ReplayMem.h"
#include <stdlib.h>

const int FIRST_FILT_SIZE = 8;
const int FIRST_FILT_COUNT = 4;

const int SECOND_FILT_SIZE = 4;
const int SECOND_FILT_COUNT = 2;

const int FOURTH_LAYER_SIZE = 256;
const int OUTPUT_LAYER_SIZE = 4; //WILL BE ACTION SET SIZE

const int MINIBATCH_SIZE = 16;

int main(){
	Agent a;
	
	//################################
	// Just to keep debug window open!
	int ph;
	std::cin >> ph;
	//################################

	return 0;
}

Agent::Agent(){
	m_weights[0] = InitRandWeights();

	Image imagePH;		//Create placeholder images //TESTING PURPOSES ONLY
	vector<int> phRow;
	for (uint i = 0; i < 84; i++){
		for (uint j = 0; j < 84; j++){
			phRow.push_back(i + j);
		}
		imagePH.push_back(phRow);
		phRow.clear();
	}
	vector<Image> imgs;	
	for (uint i = 0; i < 4; i++){
		imgs.push_back(imagePH);
	}

	m_current = imgs;
	NeuralNetwork nn(imgs, m_weights[0]);
	//ALE ale;
	//get actionsetsize (minimal may be best)

}

void Agent::play(){
	ReplayMem rm;
	transition minibatch[MINIBATCH_SIZE];
	bool gameover; //temporary;

	for (uint ep = 0; ep < EPOCH_COUNT; ep++){
		//Set m_current  to a screenshot from game(preprocessed)
		while (!gameover){
			if (rand() % 100 + 1 <= m_epsilon){
				PerformRandomAction();
			}else{
				UseNeuralNetwork();
			}
			//m_reward = ale.act(m_action);
			rm.AddTransition(m_current, m_action, m_reward);
			//minibatch = rm.GetMiniBatch();

			//perform gradient descent
		}
	}
}

Images Agent::Preprocess(Images in){
	//perform preprocess (should just be downscaling and ROI)
	return in;
}

void Agent::PerformRandomAction(){
	m_action = rand() % m_numActions;
}

void Agent::UseNeuralNetwork(){
	//NeuralNetwork nn(m_current]);
	//m_action = nn.GetDecision; GetDecision method does not currently exist.
}

void Agent::Backprop(){//change to gradDescent?

}

weightStruct Agent::InitRandWeights(){
	weightStruct temp;
	Filter f;
	Filters fs;
	Weights ws;
	
	//Layer 1
	for (uint c = 0; c < FIRST_FILT_COUNT; c++){
		for (uint x = 0; x < FIRST_FILT_SIZE; x++){
			for (uint y = 0; y < FIRST_FILT_SIZE; y++){
				ws.push_back(rand() % 100 + 1);
			}
			f.push_back(ws);
			ws.clear();
		}
		fs.push_back(f);
		f.clear();
	}
	temp.weightLayer1 = fs;
	fs.clear();

	//Layer 2
	for (uint c = 0; c < SECOND_FILT_COUNT; c++){
		for (uint x = 0; x < SECOND_FILT_SIZE; x++){
			for (uint y = 0; y < SECOND_FILT_SIZE; y++){
				ws.push_back(rand() % 100 + 1);
			}
			f.push_back(ws);
			ws.clear();
		}
		fs.push_back(f);
		f.clear();
	}
	temp.weightLayer2 = fs;
	fs.clear();

	//Layer 3
	for (uint c = 0; c < FOURTH_LAYER_SIZE; c++){
		ws.push_back(rand() % 100 + 1);
	}
	temp.weightLayer3 = ws;
	ws.clear();

	//Layer 4
	for (uint c = 0; c < OUTPUT_LAYER_SIZE; c++){
		ws.push_back(rand() % 100 + 1);
	}
	temp.weightLayer4 = ws;
	ws.clear();

	return temp;
}



ReplayMem::ReplayMem(){

}

void ReplayMem::AddTransition(Images s, int a, int r){
	transition tran;
	tran.state = s;
	tran.action = a;
	tran.reward = r;
	int size = m_transitions.size();

	if (m_buffer){
		m_transitions[m_bufferCount];
		m_bufferCount++;
	}else if (size <= SIZE){	
		m_transitions[size] = tran;
	}else{
		m_buffer = true;
		m_bufferCount++;
	}
	
}

transition* ReplayMem::GetMiniBatch(){
	transition batch[MINIBATCH_SIZE];
	for (uint i = 0; i < MINIBATCH_SIZE; i++){
		int rand = 0; //should be random number
		batch[i] = m_transitions[0];
	}
	return batch;
}

const int ReplayMem::GetSize(){
	return SIZE;
}

const int ReplayMem::GetMinibatchSize(){
	return MINIBATCH_SIZE;
}