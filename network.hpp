#include "neuron.hpp" 
#include <vector>


#ifndef NETWORK_HPP
#define NETWORK_HPP

class Network {
	
	public: 
	Network(std::array<double, 2>, double, double, double, double, int, int, int); 
	Network(std::array<double, 2> ); 
	~Network(); 

	void update(); 
	int roll(int, int); 
	void add_to_network(Neuron*);
	void write(); 
	unsigned int getPop() const; 
	void current_buffers(); 
	void create_connections();
	
	
	private:
	std::vector<Neuron*> Population_; ///vector of pointers on all neurons in the network 
	std::vector<std::vector<double>> MyConnections_; ///double will show number of connections between neurons. 
	int nbre_excitatory_; 
	int nbre_inhibitory_; 
	


};

#endif
