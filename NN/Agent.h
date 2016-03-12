#pragma once
#include "NeuralNetwork.h"
#include "ReplayMem.h"
#include <vector>

class Agent{
private:
	const int REPLAY_MEM_SIZE = 10000;
	const double LEARNING_RATE = 0.99;
	const int EPOCH_COUNT = 5;
	const int MINIBATCH_SIZE = 16;
	//ALE ale;


public:

	void PerformRandomActions();

	void UseNeuralNetwork(/*weights?*/);

	void Backprop(); //should this be here or in NN?

};