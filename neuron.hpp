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
	void update_state_(std::vector<double>, double, double);
	void write_in_file(); 
	
	private:
	double spike_potential_ = 10000; 
	double membrane_resistance_ = 30; 
	double membrane_potential_ = 60; 
	bool refractory_state_=false; 

};

#endif
