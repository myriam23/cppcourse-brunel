#include <vector>
#include <array>

#ifndef NEURON_HPP
#define NEURON_HPP

class Neuron {
	public:
	Neuron();
	~Neuron();
	std::vector<std::array<double,2>> membranepot_spiketime_; 
	
	//std::vector<double> spike_membrane_; 
	//double spikes_number(); 
	double number_spikes; 
	void update_state_(std::vector<double>, double, double);
	void write_in_file(); 
	
	private:
	double spike_potential_ = 8000; 
	double membrane_resistance_ = 30; 
	double membrane_potential_ = 60; 
	bool refractory_state_=false; 

};

#endif
