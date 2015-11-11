//Example Agent for the Arcade Learning Environment
//Joseph Shihab Esmaail 2015

#include <iostream>
#include "src/ale_interface.hpp"

#ifdef __USE_SDL
  #include <SDL.h>
#endif

using namespace std;

int main(int argc, char** arg){

	int epCount = 100;

	ALEInterface ale;

	ale.setInt("random_seed", 123);
	ale.setFloat("repeat_action_probability", 0.25);

	#ifdef __USE_SDL
		ale.setBool("display_screen", true);
		ale.setBool("sound", true);
	#endif

	ale.loadROM("spcinvad.bin");	//load game ROM

	ActionVect legalActions = ale.getLegalActionSet(); //get legal game actions

	for(int ep = 0; ep<epCount; ep++){
		float totalReward = 0;
		while(!ale.game_over()){
			Action a = legalActions[rand() % legalActions.size()]; //select random action
			float reward = ale.act(a); //Apply action and get reward
			totalReward += reward;
		}
		cout <<"Episode " << ep << " ended with a score of " << totalReward << endl;
		ale.reset_game();		
	}

	return 0;
}