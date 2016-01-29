#pragma once
#include <vector>

using std::vector;

typedef vector<vector<int>> Image;

//ALE now outputs grayscale(?)
class Preprocessor{
private:

public:
	Preprocessor(Image i);

	~Preprocessor(){};

	Image GetPPImg();
};