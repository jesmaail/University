#pragma once
#include <vector>
#include "NeuralNetwork.h"

using namespace std;

struct transition{
	Images state;
	int action;
	int reward;
	Images nextState;
};

class ReplayMem{
private:
	vector<transition> m_transitions;

public:
	ReplayMem();

	void AddTransition(Images s, int a, int r, Images n);

	vector<transition> GetMiniBatch();
};