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
	int m_epsilon = 99;
	Images m_current;
	Images m_next;
	int m_reward;
	int m_action;
	bool m_terminal;
	ReplayMem m_replay;

	weightStruct m_weights[2];


public:
	Agent();

	void play();

	Images Preprocess(Images in);

	void PerformRandomAction();

	void UseNeuralNetwork(/*weights?*/);

	void Backprop(); //should this be here or in NN?

	weightStruct InitRandWeights();
};