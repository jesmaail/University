#pragma once
#include <vector>
#include <array>
#include "NeuralNetwork.h"

using namespace std;

struct transition{
	Images state;
	int action;
	int reward;
	Images nextState;
	bool terminal;
};

class ReplayMem{
private:
	const static int SIZE = 10000;
	const static int MINIBATCH_SIZE = 16;
	bool m_buffer = false;
	int m_bufferCount = 0;
	std::array<transition, SIZE> m_transitions;

public:
	ReplayMem();

	void AddTransition(Images s, int a, int r, Images n, bool t);

	vector<transition> GetMiniBatch();

	const int GetSize();
	const int GetMinibatchSize();
};