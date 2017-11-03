#include <vector>
#include <array>
#include <string> 
#include <random>
#include <iomanip> 
#include <vector> 
#include <cassert>
#include <cmath> 
#ifndef NEURON_HPP
#define NEURON_HPP

class Neuron {
	
	public:
	Neuron(std::array<double, 2>, double, double, double, double, bool, double);  
	Neuron(std::array<double, 2>, bool, double);
	~Neuron();
	
	bool update_state_();
	double random_input();
	
	///buffer methods 
	double read_buffer(); 
	void write_buffer(double); 
	void reset_buffer(unsigned int);
	std::vector<double> getBuffer() const; 
	void write_bufferTest(double, int);
	///time and steps conversion
	unsigned int time_to_steps(double); 
	unsigned int current_index(); 
	double neuron_time_; 
	
	///getters and setters
	double get_v_m() const; 
	std::vector<int> getMyTargets() const; 
	void changeMyTargets(unsigned int); 
	bool Is_it_excitatory() const; 
	double getweight() const;
	void set_iext(double);
	double getspiketime() const;
	
std::vector<double> potentieltemps;
	std::vector<double> tempspike;
	

	protected:
	std::vector< int> MyTargets_; 
	std::vector<double> Ring_buffer_;

double arriving_current; 
	unsigned int Buffer_size;
	 double eta_;
	double membrane_potential_;  
	 double time_of_spike_; 
	bool refractory_; 
	bool excitatory_; 
	
	 double time_increment_; 
	 double delay_; 
	unsigned int delaySteps;
	
	
	const static int spike_potential_ = 20; 
	const static int membrane_resistance_ = 20; 
	const static int refractory_period_ = 2; //ms 
	const static int teta_ = 20; 
	const static int tau_ = 20; 
	
	double c1 = 0;
	double c2 = 0;
	double weight_; 
	

	
	
};

#endif
