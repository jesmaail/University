//Example Agent for the Arcade Learning Environment 
//Joseph Shihab Esmaail

#include <iostream>
#include <ale_interface.hpp>
#include <vector>
#ifdef __USE_SDL
  #include <SDL.h>
#endif

using namespace std;

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

int main(int argc, char** argv){
	int epCount = 3;	//how many episodes to perform
	int highscore = 0;	//initialise highscore
	bool screenshot = false;
	int width, height;
	fstream fout;
	fout.open("screen.txt");
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
					int img[height][width];
					int x = 0;

					for(int j=32; j<height-18; j++){
						for (int i=0; i<width; i++){
							int intPix = screen.get(j, i);
							img[x][i] = grayscaleValue[intPix];
							fout << img[x][i];
							fout << " ";
						}
						x++;
						fout << endl;
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
		ale.reset_game();	//Reset game for next episode

	}
	return 0;
}