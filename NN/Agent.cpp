#pragma once
#include "NeuralNetwork.h"
#include "Agent.h"
#include "ReplayMem.h"
#include <stdlib.h>

int main(){
	

	return 0;
}

Agent::Agent(){
	//ALE ale;
	//get actionsetsize (minimal may be best)

}

void Agent::play(){
	ReplayMem rm;
	transition minibatch[rm.GetMinibatchSize];
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
			minibatch = rm.GetMiniBatch();

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
	NeuralNetwork nn(m_current);
	//m_action = nn.GetDecision; GetDecision method does not currently exist.
}

void Agent::Backprop(){//change to gradDescent?

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
	transition *batch = new transition[MINIBATCH_SIZE];
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