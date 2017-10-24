#include "neuron.hpp" 

#ifndef NEURON_EXCITATORY_HPP
#define NEURON_EXCITATORY_HPP

class Excitatory: public Neuron 
{ 
 
	Excitatory(double, double); 
	~Excitatory(); 
	
	
	private: 
	static unsigned int nbre_excitatory_; 
};

#endif
