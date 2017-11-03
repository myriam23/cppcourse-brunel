#include "neuron.hpp"
#include <vector>
#include <cmath>
#include <fstream> 
#include <iostream> 
#include <array>
#include <random>
#include <iomanip> 

Neuron::Neuron(std::array<double, 2> temp, bool type, double g)
: membrane_potential_(0), time_of_spike_(0),
neuron_time_(temp[0]), time_increment_(0.1),
delay_(1.5), refractory_(false), arriving_current(0),
Ring_buffer_(16,0), eta_(2) ///have to manually put the size of the ring buffer for the default constructor
{
	static double c1 = exp(-time_increment_/tau_);
	static double c2 = membrane_resistance_ *(1-c1);
	excitatory_ = type;
	if(excitatory_ ==false) { weight_ = -g* 0.1;}else{ weight_ = 0.1;}
}

Neuron::Neuron(std::array<double, 2> temp,  double h,  double del, double w,  double e, bool type, double g) 
: membrane_potential_(0), time_of_spike_(0), refractory_(false), arriving_current(0)
{
	static double c1 = exp(-time_increment_/tau_);
	static double c2 = membrane_resistance_ *(1-c1);
	excitatory_ = type;
	neuron_time_ = temp[0];
	eta_ = e;
	time_increment_ = h; 	
	delay_ = del; 
	if(excitatory_ ==false) { weight_ = -g* w;}else{ weight_ = w;}
	
	delaySteps = time_to_steps(delay_);	
	Buffer_size = delaySteps + 1; 
	for(unsigned int a = 0; a < Buffer_size; ++a) 
	{ 
		Ring_buffer_.push_back(0);
	}	
} 
Neuron::~Neuron(){} 

void Neuron::set_iext(double i) 
{ 
	arriving_current = i; 
}
bool Neuron::update_state_()
{	
		if (!refractory_) 
		{ 	///left constants as calcultation because otherwise I would get 1 for the exponential instead of 0.9
			membrane_potential_= (exp((-1 * time_increment_/tau_)) * membrane_potential_) + (arriving_current * membrane_resistance_ *(1- exp((-1 * time_increment_/tau_)))) + read_buffer() + random_input();  
			reset_buffer(current_index());	
			
			if(membrane_potential_ > spike_potential_) 
			{ 
				//potentieltemps.push_back(membrane_potential_); 
				//potentieltemps.push_back(neuron_time_);
				
				refractory_ = true; 
				time_of_spike_ = neuron_time_;
				membrane_potential_ = 0; 
				neuron_time_ += time_increment_;
			
				return true; 
			}
			time_of_spike_ = 0;
			neuron_time_ += time_increment_;
			return false;
				
		}else
		{
			if(neuron_time_ - time_of_spike_ > refractory_period_)
			{
				//tempspike.push_back(time_of_spike_); 
				//tempspike.push_back(neuron_time_);
				membrane_potential_ = 0; //ne devrait pas etre necessaire 
				refractory_ = false; 
				time_of_spike_ = 0;
			} 
		
			reset_buffer(current_index());
			neuron_time_ += time_increment_;
			return false; 
		}
	
}

unsigned int Neuron::time_to_steps(double t) 
{ 
	return static_cast<unsigned long>(std::ceil(t/time_increment_)); 	
}

double Neuron::read_buffer()  
{ 
	unsigned int i = current_index();
	assert(i < Buffer_size);
	return Ring_buffer_[i];
	
} 

void Neuron::reset_buffer(unsigned int c) 
{
	Ring_buffer_[c] = 0; 
}

unsigned int Neuron::current_index() 
{ 	
	unsigned int current = time_to_steps(neuron_time_) % (Buffer_size);
	return current;	
}

void Neuron::write_buffer(double w) 
{ 	
	unsigned int index = (current_index() + delaySteps) % (Buffer_size);
	assert(index < Buffer_size);
	Ring_buffer_[index] += w; 		
} 
//not used anywhere but unitest
double Neuron::get_v_m() const
{
	return membrane_potential_; 
} 
double Neuron::getspiketime() const
{
	return time_of_spike_;
}

double Neuron::getweight() const
{
	return weight_; 
}
bool Neuron::Is_it_excitatory() const
{ 
	return excitatory_; 
} 


double Neuron::random_input() 
{	
	static std::random_device number_random; 
	static std::mt19937 engine(number_random()); //random number generator 
	static int v =  (eta_* spike_potential_)/(weight_ * tau_); 
	static std::poisson_distribution<int> poisson(v*time_increment_); //generate a poisson distribution with mean value = mean rate of firing v. 
	int input = poisson(engine); //will call the poisson distribution on a randomly generated number 
	return input;
}

std::vector< int> Neuron::getMyTargets() const
{
	return MyTargets_;
}

void Neuron::changeMyTargets(unsigned int target_id) 
{
	MyTargets_.push_back(target_id);
}

std::vector<double> Neuron::getBuffer() const
{
	return Ring_buffer_; 
}

void Neuron::write_bufferTest(double g, int i)
{ 
	assert(i < Buffer_size);
	Ring_buffer_[i] += g; 	
}
