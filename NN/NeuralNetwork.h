#include <vector>

using std::vector;
//#################################################################################################################################################

//This is where the Neural Network will be run from, containing the Network, ALE and Q-Table
class Main{
private:
	//ALE m_ale;
	NeuralNetwork m_nn;

public:

	
};
//#################################################################################################################################################


//Performs the preperation steps to prepare input data to the neural network from ALE
class Preprocessor{
private:

public:
	Preprocessor();

	~Preprocessor(){};
};
//#################################################################################################################################################


//The Neural Network
class NeuralNetwork{
private:
	vector<ConvLayer> m_convLayers;
	vector<FullConnLayer> m_fcLayers;

public:
	NeuralNetwork();

	~NeuralNetwork(){};


	vector<ConvLayer> GetConvLayers();
	void SetConvLayers(vector<ConvLayer> layers);

	vector<FullConnLayer> GetFullConnLayers();
	void SetFullConnLayers(vector<FullConnLayer> layers);
};
//#################################################################################################################################################


//Basic Neuron 
class Neuron{
private:
	float m_bias;
	float m_value;
	vector<Connection> m_connections;

public:
	Neuron();
	Neuron(float bias);
	//Neuron(Neuron const &n);

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

public:
	ConvNeuron();

	~ConvNeuron(){};
};
//#################################################################################################################################################


//Connection
class Connection{
private:
	Neuron *m_neuron;
	float m_weight;

public:
	Connection(Neuron *n, float weight);
	//Connection(Connection const &conn);

	~Connection(){};


	Neuron GetNeuron();
	void SetNeuron(Neuron &n);

	float GetWeight();
	void SetWeight(float weight);
};
//#################################################################################################################################################


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
	void AddNeuron(Neuron *n);
	void AddNeuronVector(vector<Neuron> ns);
};


//Convolutional Layer
class ConvLayer : Layer{
private:
	int m_filterNum;
	int m_filterSize;
	int m_stride;

public:
	ConvLayer();

	~ConvLayer(){};


	int GetFilterNum();
	void SetFilterNum(int num);

	int GetFilterSize();
	void SetFilterSize(int size);

	int GetStride();
	void SetStride(int stride);
};


//Fully Connected Layer
class FullConnLayer : Layer{
private:

public:
	FullConnLayer();
	
	~FullConnLayer(){};
};
//#################################################################################################################################################