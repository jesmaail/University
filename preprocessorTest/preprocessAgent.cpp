//Example Agent for the Arcade Learning Environment 
//Joseph Shihab Esmaail

#include <iostream>
#include <ale_interface.hpp>
#include <vector>
#ifdef __USE_SDL
  #include <SDL.h>
#endif

using namespace std;

int main(int argc, char** argv){
	int epCount = 3;	//how many episodes to perform
	int highscore = 0;	//initialise highscore
	bool screenshot = false;
	int width, height;
	fstream fout;
	fout.open("screen.dat");
	fout.clear();

	ALEInterface ale;	//Initialise Arcade Learning Environment

	#ifdef __USE_SDL	//Simple Direct Media Layer, for observing game as it is played
		ale.setBool("display_screen", false);
		ale.setBool("sound", false);
	#endif

	ale.loadROM(argv[1]);	//load game specified game ROM
	ActionVect legalActions = ale.getLegalActionSet(); //get legal game actions

	for(int ep = 0; ep<epCount; ep++){
		float totalReward = 0;
		int count = 0;
		while(!ale.game_over()){			
			Action a;

			if(count % 10 == 0 || count == 0){	//Perform actions
				a = legalActions[1];
			}else if(count < 101){
				a = legalActions[3];
			}else if (count < 201){
				a = legalActions[4];
				if(!screenshot){
					ALEScreen screen = ale.getScreen();
					width = screen.width();
					height = screen.height();
					int img [height][width];

					fout << screen.get(50, 50);

					for(int j=0; j<height; j++){
						for(int i=0; i<width; i++){
							pixel_t pix = screen.get(j, i);
							int intPix = screen.get(j, i);
							img[j][i] = intPix;

							//fout << pix;
							//fout << " ";
							// if(pix < 5)
							// 	pix = ' ';
							// else
							// 	pix = '#';

							if(j < 32 || j >= (height-18)){								
								//printf("%d",intPix);
							}							
						}				
						//printf("\n");
						//fout << "NEWLINE" << endl;
						//fout << endl;
					}
					screenshot = true;
					fout.close();
				}
			}else{
				count = -1;
			}
			count++;

			float reward = ale.act(a); 	//Apply action and get reward
			totalReward += reward;		//Adjust total reward
		}		
		//Output total score of the episode
		cout <<"Episode " << ep << " ended with a score of " << totalReward << endl;

		if(totalReward > highscore){	//Get highscore
			highscore = totalReward;
		}
		ale.reset_game();	//Reset game for next episode

	}
	cout <<"Highest score achieved: " << highscore << endl;
	return 0;
}