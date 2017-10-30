#include <vector>
#include <array>
#include <string> 
#include <random>
#include <iomanip> 
#include <vector> 
#include <cassert>

#ifndef NEURON_HPP
#define NEURON_HPP

class Neuron {
	
	public:
	Neuron(std::array<double, 2>, double, double, double, double, int);  
	Neuron(std::array<double, 2>);
	~Neuron();
	
	bool update_state_();
	double random_input();
	
	///buffer methods 
	unsigned int read_buffer(); 
	void write_buffer(int); 
	double get_buffer(int) const; 
	double buffer_size() const; 
	
	///time and steps conversion
	unsigned int time_to_steps(double); 
	unsigned int current_index(); 
	
	///getters and setters
	void set_i_ext(double); 
	double get_v_m() const; 

	bool Is_it_excitatory() const; 
	void set_type(bool); 
	std::vector<double> Spike; 
	std::vector<double> getTheSpikes() const; 
	std::vector<unsigned int> getMyTargets() const; ///not const because will be changed
	///methods for txt files 
	void save_spike(double); 
	void changeMyTargets(unsigned int); 

	
	
	
	
	protected:
	double membrane_potential_; 
	double number_spikes_; 
	double time_of_spike_; 
	bool refractory_; 
	bool excitatory_; 
	double actual_time_; 
	std::vector<unsigned int> MyTargets_; 
	
	double time_increment_; 
	double arriving_current_;
	double delay_; 
	double weight_; 
	
	std::vector<double> Ring_buffer_;
	const static int spike_potential_ = 20; 
	const static int membrane_resistance_ = 20; 
	const static int refractory_period_ = 2; //ms 
	const static int teta_ = 20; 
	const static int tau_ = 20; 
	int eta_;
	

	
	
};

#endif
