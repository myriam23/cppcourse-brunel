#include "neuron.hpp" 
#include <vector>


#ifndef NETWORK_HPP
#define NETWORK_HPP

class Network {
	
	public: 
	Network(std::array< double, 2>,  double,  double, double,  int,  int,  double, double); 
	Network(std::array< double, 2>, double ); 
	~Network(); 

	void update(); 
	unsigned int roll(int, int); 
	void add_to_network(Neuron*);
	void savetime(unsigned int); 
	std::vector<Neuron*> getPopulation_() const;
	 unsigned int getPop() const; 
	void create_connections();
	
	private:
	std::vector<Neuron*> Population_; ///vector of pointers on all neurons in the network 
	 int nbre_excitatory_; 
	 int nbre_inhibitory_; 
	 double network_time;
	 double end_simulation;
	 double dt;
	
	
};

#endif
