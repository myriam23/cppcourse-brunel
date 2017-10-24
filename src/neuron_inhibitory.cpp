#include "neuron_inhibitory.hpp" 

static unsigned int nbre_inhibitory_ = 0; 

Inhibitory::Inhibitory(double g, double t)
: Neuron(g, t) 
{
	++nbre_inhibitory_;
}

Inhibitory::~Inhibitory(){}
