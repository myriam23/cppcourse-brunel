#include <vector>
#include <array>

#ifndef NEURON_HPP
#define NEURON_HPP

class Neuron {
	public:
	Neuron();
	~Neuron();
	std::vector<double> spike_time_; 
	double spikes_number(); 
	void update_state_(std::array<double,2>, double, double);
	
	private:
	double spike_potential_; 
	double membrane_resistance_; 
	double membrane_potential_; 
	bool refractory_state_=false; 

};

#endif
