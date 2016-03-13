#pragma once
#include "NeuralNetwork.h"
#include "ReplayMem.h"
#include <vector>

class Agent{
private:
	const int REPLAY_MEM_SIZE = 10000;
	const double LEARNING_RATE = 0.99;
	const int EPOCH_COUNT = 5;
	//ALE ale;

	int m_numActions;
	int m_epsilon;
	Images m_current;
	int m_reward;
	int m_action;


public:
	Agent();

	void play();

	Images Preprocess(Images in);

	void PerformRandomAction();

	void UseNeuralNetwork(/*weights?*/);

	void Backprop(); //should this be here or in NN?

};