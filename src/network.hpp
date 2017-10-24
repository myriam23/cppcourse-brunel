#include "neuron.hpp" 
#include <vector> 

#ifndef NETWORK_HPP
#define NETWORK_HPP

class Network {
	
	public: 
	Network(double, double); 
	~Network(); 
	
	

	double nbre_excitatory_;
	double neurons_spiking_; 
	double neurons_refractory_;
	double neurons_buffering_; 
	std::vector<Neuron*> Population_; //vector of pointers on all neurons in the network 
	
	std::vector<std::vector<double>> MyConnections_; //double will show number of connections between neurons. 
	
	//methods; 
	void update(); 
	int roll(int, int); 
	void add_to_network(Neuron*);
	void create_connexions(); 

	

};

#endif
