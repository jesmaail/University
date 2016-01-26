#include <vector>

using std::vector;


//This is where the Neural Network will be run from, containing the Network, ALE and Q-Table
class Main{
private:
	//ALE m_ale;
	NeuralNetwork m_nn;

public:

	
};



//Performs the preperation steps to prepare input data to the neural network from ALE
class Preprocessor{
private:

public:
	Preprocessor(vector<vector<int>>);

	~Preprocessor(){};

	vector<vector<int>> GetPPImg();
};



//The Neural Network
class NeuralNetwork{
private:
	vector<ConvLayer> m_convLayers;
	vector<FullConnLayer> m_fcLayers;
	ConvLayer m_inputLayer;		//Need getters/setters
	ConvLayer m_secondLayer;
	ConvLayer m_thirdLayer;
	FullConnLayer m_fourthLayer;
	FullConnLayer m_outputLayer;

public:
	NeuralNetwork();

	~NeuralNetwork(){};

	void populateInputLayer(vector<vector<int>> img);
	void populateSecondLayer();
	void populateThirdLayer();
	void populateFourthLayer();
	void populateOutputLayer();

	ConvLayer GetInputLayer();
	ConvLayer GetSecondLayer();
	ConvLayer GetThirdLayer();
	FullConnLayer GetFourthLayer();
	FullConnLayer GetOutputLayer();

	void SetInputLayer(ConvLayer l);
	void SetSecondLayer(ConvLayer l);
	void SetThirdLayer(ConvLayer l);
	void SetFourthLayer(FullConnLayer l);
	void SetOutputLayer(FullConnLayer l);

	vector<ConvLayer> GetConvLayers();
	void SetConvLayers(vector<ConvLayer> layers);

	vector<FullConnLayer> GetFullConnLayers();
	void SetFullConnLayers(vector<FullConnLayer> layers);
};



//Basic Neuron 
class Neuron{
private:
	float m_bias;
	float m_value;
	vector<Connection> m_connections;

public:
	Neuron();
	Neuron(float bias);

	~Neuron(){};

	float Activation();
	float CalculateValue();

	float GetValue();
	void SetValue(float value);

	float GetBias();
	void SetBias(float bias);

	vector<Connection> GetConnections();
	void SetConnections(vector<Connection> conns);
};


//Convolutional Neuron 
class ConvNeuron : Neuron{
private:
	float m_bias;
	float m_value;
	vector<vector<float>> m_weights;
	vector<Connection> m_connections;

public:
	ConvNeuron();
	~ConvNeuron(){};

	float GetBias();
	void SetBias(float b);

	float GetValue();
	void SetValue(float v);

	void SetWeights(vector<vector<float>> weights);
	vector<vector<float>> GetWeights();

	void SetConnections(vector<Connection> c);
	vector<Connection> GetConnections();
};



//Connection
class Connection{
private:
	Neuron *m_neuron;
	float m_weight;

public:
	Connection(Neuron *n, float weight);

	~Connection(){};


	Neuron GetNeuron();
	void SetNeuron(Neuron &n);

	float GetWeight();
	void SetWeight(float weight);
};



//Basic Layer
class Layer{
private:
	float m_bias;
	vector<Neuron> m_neurons;

public:
	Layer();

	~Layer(){};


	float GetBias();
	void SetBias(float bias);

	vector<Neuron> GetNeurons();
	void AddNeuron(Neuron n);
	void AddNeuronVector(vector<Neuron> ns);
};


//Convolutional Layer
class ConvLayer : Layer{
private:
	float m_bias;

	int m_filterNum;
	int m_filterSize;
	int m_stride;

	vector<vector<ConvNeuron>> m_neurons;

public:
	ConvLayer();

	~ConvLayer(){};

	float GetBias();
	void SetBias(float bias);

	int GetFilterNum();
	void SetFilterNum(int num);

	int GetFilterSize();
	void SetFilterSize(int size);

	int GetStride();
	void SetStride(int stride);

	vector<vector<ConvNeuron>> GetNeurons();
	void SetNeurons(vector<vector<ConvNeuron>> neurons);
};


//Fully Connected Layer --- May be redundant!
class FullConnLayer : Layer{
private:
	float m_bias;
	vector<Neuron> m_neurons;

public:
	FullConnLayer();
	
	~FullConnLayer(){};
};
