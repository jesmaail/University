
class preprocess{
private:
	int grayscaleValue[256];

public:
	preprocess();

	int** preprocessImage(int in[210][160]);

};