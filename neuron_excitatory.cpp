#include "neuron_excitatory.hpp"
#include <cmath>

static unsigned int nbre_excitatory_ = 0; 

Excitatory::Excitatory(double t = 20, double j = 5, double x = 0) //check value for j 
: Neuron(t, j,x) 
{
	++nbre_excitatory_;
}

Excitatory::~Excitatory(){} 
