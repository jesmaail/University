#include <ale_interface.hpp>
#include <vector>
#include <iostream>
/*
#ifdef __USE_SDL
	#include <SDL.h>
#endif
	*/

using namespace std;

//int main(int argc, char* argv[]) {

int holdplacer(int argc, char* argv[]){

	int epCount = 3;	//how many episodes to perform
	int highscore = 0;	//initialise highscore
	bool screenshot = false;
	//int width, height;

	ALEInterface ale;

	// Get & Set the desired settings
	//ale.setInt("random_seed", 123);
	//The default is already 0.25, this is just an example
	//ale.setFloat("repeat_action_probability", 0.25);

	#ifdef __USE_SDL	//Simple Direct Media Layer, for observing game as it is played
		ale.setBool("display_screen", true);
		ale.setBool("sound", false);
	#endif

		ale.loadROM(argv[1]);

	ActionVect legalActions = ale.getLegalActionSet(); //get legal game actions

	for (int ep = 0; ep<epCount; ep++){
		float totalReward = 0;
		int count = 0;
		while (!ale.game_over()){
			Action a = legalActions[0];

			if (count % 10 == 0 || count == 0){	//Perform actions
				a = legalActions[1];
			}
			else if (count < 101){
				a = legalActions[3];
			}
			else if (count < 201){
				a = legalActions[4];
			}
			else{
				count = -1;
			}
			count++;

			float reward = ale.act(a); 	//Apply action and get reward
			totalReward += reward;		//Adjust total reward
		}
		//Output total score of the episode
		cout << "Episode " << ep << " ended with a score of " << totalReward << endl;

		if (totalReward > highscore){	//Get highscore
			highscore = totalReward;
		}
		ale.reset_game();	//Reset game for next episode
	}
	cout << "Highest score achieved: " << highscore << endl;

	return 0;
}