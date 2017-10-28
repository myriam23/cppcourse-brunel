#include "neuron.hpp" 
#include <vector>


#ifndef NETWORK_HPP
#define NETWORK_HPP

class Network {
	
	public: 
	Network(double, double, double, double, double, int, int); 
	Network(); 
	~Network(); 

	void update(); 
	int roll(int, int); 
	void add_to_network(Neuron*);
	void write(); 
	int getPop(); 
	void current_buffers(); 
	void create_matrix();
	void refine_network(); 
	
	
	private:
	std::vector<Neuron*> Population_; ///vector of pointers on all neurons in the network 
	std::vector<std::vector<double>> MyConnections_; ///double will show number of connections between neurons. 
	int nbre_excitatory_; 
	int nbre_inhibitory_; 
	std::vector<std::vector<int>> TheMatrix_;


};

#endif
