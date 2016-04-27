#pragma once
#include "network/NeuralNetwork.h"
#include "network/ReplayMem.h"
#include <ale_interface.hpp>
#include <vector>

class Agent{
private:
	const int REPLAY_MEM_SIZE = 10000;
	const double LEARNING_RATE = 0.99;
	const int EPOCH_COUNT = 5;
	ALEInterface m_ale;
	bool m_gameover;

	int m_numActions;
	ActionVect m_legalActs;
	int m_epsilon = 99;
	double discount = 0.99;
	Images m_current;
	Images m_next;
	int m_reward;
	int m_action;
	bool m_terminal = false;
	ReplayMem m_replay;

	weightStruct m_weights[2];


public:
	Agent(string game);

	void play();

	Images Preprocess(Images in);

	void PerformRandomAction();

	void UseNeuralNetwork(/*weights?*/);

	void Backprop(); //should this be here or in NN?

	weightStruct InitRandWeights();

	Images GetPlaceholderScreen();
	
	Image GetScreen();

	void Learning();
};