#include <vector>
#include <array>
#include <string> 

#ifndef NEURON_HPP
#define NEURON_HPP

class Neuron {
	public:
	Neuron(double);  
	~Neuron();
	
	//std::vector<std::array<double,2>> membranepot_spiketime_; 
	
	protected:
	enum class State:short { 
		Buffering, 
		Spiking, 
		Refractory
	}; 
	
	struct Spike { 
		double delay_ = 10; 
		double time_of_spike_; 
		double time_at_arrival_ = time_of_spike_ + delay_;
		double efficacy_; 
		//double exiting_current_; what the neuron sends --> in spike ? 
	};
	
	Spike spike_; 
	
	//parameters according to brunnel: 
	
	double excitatory_connections_ = 4 * inhibitory_connections_; 
	double inhibitory_connections_ = 10; //random number for now 
	double external_connections_ = excitatory_connections_; 
	
	double arriving_current_ = 0;  //what the neuron receives 
	double exiting_current_ = 0; //what the neuron sends 
	
	double threshold_frequency_ = teta_ / (spike_.efficacy_ * excitatory_connections_ * tau_); //define tau and efficacy for each subclass (inhibitory or excitatory) 
	
	
	//values should be given in each subclass 
	double tau_; 
	
	
	double teta_ = 20; //in mV, compute accordingly in all equations 
	//double rest_membrane_potential_ = 0; //mV
	
	double external_input_frequency_; //sum of excitatory inputs and inhibitory
	double excitatory_input_frequency_; 
	double inhibitory_input_frequency_; 
	double transmission_delay_; 
	
	double number_spikes_; 
	const static int spike_potential_ = 20; 
	const static int membrane_resistance_ = 20; 
	const static int refractory_period_ = 2; //ms 
	double membrane_potential_; 

	//bool refractory_state_=false; 
	State current_state_;
	double actual_time_; 
	
	public:
	void update_state_(double, double, std::vector<double> tab = {0, 1000}, double i = 0);
	void write_in_file(); 
	void interact(Neuron&); 
};

#endif
