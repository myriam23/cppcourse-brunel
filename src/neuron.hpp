#include <vector>
#include <array>
#include <string> 



#ifndef NEURON_HPP
#define NEURON_HPP

class Neuron {
	public:
	Neuron(double, double);  
	~Neuron();
	
	
	
	public:
	bool update_state_();
	
	void write_in_file(); 
	void save_spike(double, double); 
	
	double read_buffer(); 
	void write_buffer(int); 
	
	double current_step(); 
	int time_to_steps(double); 
	int current_index(); 
	
	

	std::vector<int> MyTargets_;  
	
	protected:
	
	double time_of_spike_; 
	bool refractory_; 
	double membrane_potential_; 
	double actual_time_; 
	double number_spikes_; 
	
	double time_increment_; //ms 
	double arriving_current_;
	double delay_; 
	double weight_; 
	
	
	std::vector<double> Ring_buffer_;
	std::vector<std::array<double,2>> membranepot_spiketime_; 

	
	
	/*///Parameters according to brunnel: 
		///Connections 
		double excitatory_connections_ = 4 * inhibitory_connections_; 
		double inhibitory_connections_ = 10; //random number for now 
		double external_connections_ = excitatory_connections_; 
		///Currents 
		  //what the neuron receives 
		double exiting_current_ = 0; //what the neuron sends 
		///Frequencies
		double threshold_frequency_ = teta_ / (spike_.efficacy_ * excitatory_connections_ * tau_); //define tau and efficacy for each subclass (inhibitory or excitatory) 
		double external_input_frequency_; //sum of excitatory inputs and inhibitory
		double excitatory_input_frequency_; 
		double inhibitory_input_frequency_; */
	
	
	const static int spike_potential_ = 20; 
	const static int membrane_resistance_ = 20; 
	const static int refractory_period_ = 2; //ms 
	const static int teta_ = 20; 
	const static int tau_ = 20; 
	

	
	
};

#endif