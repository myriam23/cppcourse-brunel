#include "neuron.hpp" 
#include <iostream> 
#include <fstream> 
#include <string> 

#ifndef NETWORK_HPP
#define NETWORK_HPP


class Network {
	
	public: 
	Network(std::array< double, 2>,  double,  double, double,  int,  int,  double, double, std::string);  /*! < This constructor allows the user to choose the update rate of the simulation (time increment) and the size of the population. It also allows the user to define the delay and efficiency of its neurons' spikes. */
	Network(std::array< double, 2>, double, double, std::string); 
	~Network(); 
	
	void add_to_network(Neuron*);	
	void create_connections();
	void update();
	std::vector<Neuron*> getPopulation_() const;
	unsigned int getPop() const; 
	 
	
	private:
	std::vector<Neuron*> Population_; /*!<This vector contains pointers on all neurons that are part of the network.*/
	unsigned int nbre_excitatory_;   /*!<Number of excitatory neurons in the network */
	unsigned int nbre_inhibitory_; 	/*!<Number of inhibitory neurons in the network */
	unsigned int network_step;
	unsigned int end_step; 	/*!< Time the simultation must end*/
	std::string filename; 
	
};

#endif
