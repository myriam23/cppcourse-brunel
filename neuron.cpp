#include "neuron.hpp"
#include <array>
#include <vector>
#include <cmath>

Neuron::Neuron() {} 
Neuron::~Neuron(){} 

void Neuron::update_state_(std::array<double,2> tab, double i, double dt)
{ 
	double tau(20); 
	double current_time_(tab[1]); 
	while (current_time_ < tab[2]) {
		if (refractory_state_ == true) { 
			membrane_potential_ = 0; 
		} else { 
			membrane_potential_= (exp(-dt/tau) * membrane_potential_) + i * membrane_resistance_ * (1 - exp(-dt/tau));
			current_time_ += dt; 
		} 
		if(membrane_potential_ > spike_potential_) { 
			spike_time_.push_back(current_time_); 
		}	
}

double Neuron::spikes_number() 
{
	return spike_time_.size(); 
	
}
