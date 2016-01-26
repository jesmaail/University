#pragma once
#include <vector>

using std::vector;

//ALE now outputs grayscale(?)
class Preprocessor{
private:

public:
	Preprocessor(vector<vector<int>>);

	~Preprocessor(){};

	vector<vector<int>> GetPPImg();
};