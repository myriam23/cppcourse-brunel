#include "neuron_excitatory.hpp"
#include <cmath>

static unsigned int nbre_excitatory_ = 0; 

Excitatory::Excitatory(double g, double t) //check value for j 
: Neuron(g, t) 
{
	++nbre_excitatory_;
}

Excitatory::~Excitatory(){} 
