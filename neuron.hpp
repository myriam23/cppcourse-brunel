#include <vector>
#include <array>
#include <cmath>
#include <random>
#include <cassert> 

#ifndef NEURON_HPP
#define NEURON_HPP

class Neuron {
	
	public:
	Neuron(std::array<double, 2>, double, double, double, double, double, bool);  
	Neuron(std::array<double, 2>, double, double, bool);
	~Neuron();
	
	bool update_state_();
	double random_input() const;

	double read_buffer(); 
	void write_buffer(double); 
	void reset_buffer();
	std::vector<double> getBuffer() const; 
	void write_bufferTest(double, int);

	unsigned int time_to_steps(double); 
	unsigned int current_index(); 
	
	void changeMyTargets(unsigned int);
	void set_iext(double);
	double get_v_m() const; 
	std::vector<int> getMyTargets() const; 
	bool Is_it_excitatory() const; 
	double getweight() const;
	double getspiketime() const;
	
	private:
	std::vector< int> MyTargets_; /*!< This vector contains the name of its targets. Indeed, the neurons' name are actually their indexes on the network's population. In other words, the first neuron created is called 0. */
	std::vector<double> Ring_buffer_; /*!< The indexes of the Ring buffer contain the summed up spikes that were sent at time - delay, where time is the current time and delay is the spiking delay the user chooses at the beginning of the simulation.*/
	unsigned int Buffer_size; /*!< This has been declared as attribute for gain of time, it will be constant throughout the simulation and thus calling the size of the buffer multiple times will not be necessary.*/
	double neuron_time_; /*!<The neuron's clock is in ms and "runs" one time incrementation faster than the network clock. In other words, the neuron clock is incremented before the network's.*/
	double arriving_current; /*!<Neurons can receive an external current; this can be set in the main through set_iext().*/

	double eta_; /*!< This parameter represents the ration between the firing rate of the external connection and the threshold firing rate.*/
	double membrane_potential_;  /*!< This is the current membrane potential of the neuron.*/
	double time_of_spike_; /*!<This is the last time the neurone spiked.*/
	bool refractory_; /*!<States of neuron: refractory means it cannot receive any stimulation.*/
	bool excitatory_; /*!<Represents the type of the neuron.*/
	
	double time_increment_; 
	double delay_; 
	unsigned int delaySteps;/*!<This is the conversion of the delay into steps; it is declared as attribute so the method time to steps is called only once; this value is used multiple times. */
	
	double weight_; /*!< This is the efficiency with which the neuron sends its spikes. It is chosen by the user.*/
	
	/*!< The following parameters are defined in the Brunnel.*/
	const static int spike_potential_ = 20; 
	const static int membrane_resistance_ = 20; 
	const static int refractory_period_ = 2; 
	const static int teta_ = 20; 
	const static int tau_ = 20; 
	 	
};

#endif
