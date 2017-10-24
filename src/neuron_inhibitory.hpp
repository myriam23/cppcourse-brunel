#include "neuron.hpp" 

#ifndef NEURON_INHIBITORY_HPP
#define NEURON_INHIBITORY_HPP

class Inhibitory: public Neuron 
{ 
 
	Inhibitory(double, double); 
	~Inhibitory(); 
	
	
	private: 
	static unsigned int nbre_inhibitory_; 
};

#endif

