#include "neuron_inhibitory.hpp" 

static unsigned int nbre_inhibitory_ = 0; 

Inhibitory::Inhibitory(double t = 20, double j = 10, double x = 0)
: Neuron(t, j, x) 
{
	++nbre_inhibitory_;
}

Inhibitory::~Inhibitory(){}
