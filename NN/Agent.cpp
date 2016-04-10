#pragma once
#include <iostream>
#include "NeuralNetwork.h"
#include "Agent.h"
#include "ReplayMem.h"
#include <stdlib.h>
#include <ale_interface.hpp>
#ifdef __USE_SDL
	#include <SDL.h>
#endif

const int EPISODE_COUNT;

const int FIRST_FILT_SIZE = 8;
const int FIRST_FILT_COUNT = 4;
const int SECOND_FILT_SIZE = 4;
const int SECOND_FILT_COUNT = 2;
const int FOURTH_LAYER_SIZE = 256;
const int OUTPUT_LAYER_SIZE = 4; //WILL BE ACTION SET SIZE

const int MINIBATCH_SIZE = 16;

const int IMAGE_COUNT = 2;
const int INPUT_IMAGE_X = 120;
const int INPUT_IMAGE_Y = 180;
const int DESIRED_IMAGE_XY = 84;
const int Y_BOUND_TOP = 32;
const int Y_BOUND_BOT = 18;


const int grayscaleValue[256] = 
{0, 0, 63, 63, 106, 106, 143, 143, 174, 174, 200, 200, 219, 219, 234, 234, 62, 62, 94, 94, 124, 124, 151, 151, 174, 174, 197, 197, 221, 221,
 240, 240, 51, 51, 76, 76, 99, 99, 126, 126, 144, 144, 163, 163, 182, 182, 201, 201, 44, 44, 69, 69, 96, 96, 119, 119, 141, 141, 160, 160,
 177, 177, 197, 197, 28, 28, 57, 57, 83, 83, 109, 109, 130, 130, 153, 153, 175, 175, 193, 193, 31, 31, 60, 60, 85, 85, 109, 109, 132, 132,
 151, 151, 172, 172, 190, 190, 23, 23, 53, 53, 79, 79, 104, 104, 127, 127, 147, 147, 169, 169, 187, 187, 13, 13, 43, 43, 70, 70, 97, 97,
 120, 120, 143, 143, 166, 166, 185, 185, 9, 9, 38, 38, 69, 69, 95, 95, 118, 118, 141, 141, 164, 164, 183, 183, 25, 25, 55, 55, 82, 82,
 109, 109, 132, 132, 153, 153, 175, 175, 195, 195, 37, 37, 67, 67, 95, 95, 123, 123, 146, 146, 169, 169, 192, 192, 212, 212, 46, 46,
 76, 76, 107, 107, 136, 136, 160, 160, 187, 187, 207, 207, 229, 229, 43, 43, 74, 74, 106, 106, 137, 137, 161, 161, 187, 187, 209, 209,
 231, 231, 44, 44, 77, 77, 108, 108, 136, 136, 163, 163, 186, 186, 211, 211, 234, 234, 43, 43, 73, 73, 104, 104, 132, 132, 159, 159,
 183, 183, 203, 203, 226, 226, 42, 42, 73, 73, 104, 104, 132, 132, 156, 156, 179, 179, 202, 202, 222, 222};


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
	/*m_weights[0] = InitRandWeights();

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
	NeuralNetwork nn(imgs, m_weights[0]);*/


	ALEInterface ale;

	#ifdef __USE_SDL	//Simple Direct Media Layer, for observing game as it is played
		ale.setBool("display_screen", false);
		ale.setBool("sound", false);
	#endif

	ale.loadRom("../breakout.bin");
	ActionVect legalActions = ale.getLegalActionSet();
	int actionSize = legalActions.size();

	for(uint ep = 0; ep < EPISODE_COUNT; ep++){
		play();
	}
}

void Agent::play(){
	//ReplayMem rm;
	vector<transition> minibatch;
	//bool gameover; //temporary, replace with ale.gameover()
	bool gameover = ale.game_over();
	float reward;
	ALEScreen screen;

	for (uint ep = 0; ep < EPOCH_COUNT; ep++){
		//Set m_current  to a screenshot from game(preprocessed)
		while (!gameover){
			if (rand() % 100 + 1 <= m_epsilon){
				PerformRandomAction();
			}else{
				
				NeuralNetwork nn(m_current, m_weights[0]);
				m_action = nn.getDecision();
			}
			m_reward = ale.act(legalActions[m_action]);
			m_replay.AddTransition(m_current, m_action, m_reward);
			minibatch = m_replay.GetMiniBatch();

			//perform gradient descent (try with stochastic GD of 1)
		}
	}
}

Images Agent::Preprocess(Images in){
	//perform preprocess (should just be downscaling and ROI)
	//!!!!NEEDS ROI ADDED!!!!
	int newX, newY;
	int xRatio = (int)(INPUT_IMAGE_X << 16 / DESIRED_IMAGE_XY) + 1;
	int yRatio = (int)(INPUT_IMAGE_Y << 16 / DESIRED_IMAGE_XY) + 1;
	Image newImg;
	Images out;

	for (Image img : in){
		for (int y = 0; y < DESIRED_IMAGE_XY; y++){
			for (int x = 0; x < DESIRED_IMAGE_XY; x++){
				newY = ((y*yRatio) >> 16);
				newX = ((x*xRatio) >> 16);
				newImg[x][y] = img[newX][newY];
			}
		}
		out.push_back(newImg);
		newImg.clear();
	}
	return out;
}

void Agent::PerformRandomAction(){
	m_action = rand() % m_numActions;
}

void Agent::UseNeuralNetwork(){
	ALEScreen screen = ale.getScreen();
	

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

	if(m_buffer && m_bufferCount >= SIZE){
		m_bufferCount = 0;
		m_transitions[m_bufferCount] = tran;
		m_bufferCount++;
	}else if (m_buffer){
		m_transitions[m_bufferCount] = tran;
		m_bufferCount++;
	}else if (size <= SIZE){
		m_transitions[size] = tran;
	}else{
		m_buffer = true;
		m_bufferCount++;
	}
	
}

vector<transition> ReplayMem::GetMiniBatch(){
	vector<transition> batch;
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