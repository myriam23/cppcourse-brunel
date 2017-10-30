#include "neuron.hpp"
#include <vector>
#include <cmath>
#include <fstream> 
#include <iostream> 
#include <array>
#include <random>
#include <iomanip> 

using namespace std; 

Neuron::Neuron(std::array<double, 2> temp)
: membrane_potential_(0), number_spikes_(0), time_of_spike_(0),
actual_time_(temp[0]), time_increment_(0.1), arriving_current_(0), 
delay_(1.5), weight_(0.1), refractory_(false), excitatory_(true), 
Ring_buffer_(16,0), eta_(2) ///have to manually put the size of the ring buffer for the default constructor
{
	int final_ = temp[1]; 
	int init_ = temp[0];
	int max = (final_ - init_) / time_increment_;
	for(int i = 0; i < max; ++i) 
	{
		Spike.push_back(0); 
	}
}

Neuron::Neuron(std::array<double, 2> temp, double h, double i, double del, double w, int e) 
: membrane_potential_ (0), number_spikes_(0), time_of_spike_(0),
refractory_(false), excitatory_(true)
{
	eta_ = e;
	time_increment_ = h; 	
	arriving_current_ = i;
	delay_ = del; 
	weight_ = w;
	
	int final_ = temp[1]; 
	int init_ = temp[0];
	int max = (final_ - init_) / time_increment_;
	for(int i = 0; i < max; ++i) 
	{
		Spike.push_back(0); 
	}
	int size = time_to_steps(delay_) + 1; 
	
	for(int a = 0; a < size; ++a) 
	{ 
		Ring_buffer_.push_back(0);
	}
	
} 
Neuron::~Neuron(){} 

bool Neuron::update_state_()
{			
		if (!refractory_) 
		{ 			
			membrane_potential_= ((exp(-time_increment_/tau_) * membrane_potential_) + (arriving_current_ * membrane_resistance_ * (1 - exp(-time_increment_/tau_)))) + read_buffer() + random_input();  
			
			actual_time_ += time_increment_;
			
			if(membrane_potential_ > spike_potential_) 
			{ 
				number_spikes_ += 1; 

				refractory_ = true; 
				
				time_of_spike_ = actual_time_;
				save_spike(membrane_potential_);  
				membrane_potential_ = 0; 
				
				return true; 
			}
			
		}else{
			if(time_of_spike_ + refractory_period_ > actual_time_) 
			{ 
				refractory_ = false; 
			} 
			
			return false; 
		}
	return false;
}
			

void Neuron::save_spike(double v) 
{ 
	int i = time_to_steps(actual_time_); ///the spike will be saved in the corresponding index; index number = number of the step 
	Spike[i] = v;
					
}

unsigned int Neuron::time_to_steps(double t) 
{ 
	return static_cast<unsigned long>(std::ceil(t/time_increment_)); 	
}

unsigned int Neuron::read_buffer()  
{ 
	unsigned int i = current_index();
	assert(i < Ring_buffer_.size());
	unsigned int buffer_state = Ring_buffer_[i];
	Ring_buffer_[i] = 0;
	return  buffer_state;
} 

unsigned int Neuron::current_index() 
{ 	
	unsigned int current = time_to_steps(actual_time_) % (time_to_steps(delay_) + 1);
	return current;	
}

void Neuron::write_buffer(int n) 
{ 	
	unsigned int delay_step = time_to_steps(delay_);
	
	unsigned int index = (current_index() + delay_step) % (delay_step + 1);
	assert(index < Ring_buffer_.size());
	Ring_buffer_[index] += n * weight_; 
		
} 

void Neuron::set_i_ext(double i) 
{ 
	arriving_current_ = i; 
	
} 
double Neuron::get_v_m() const
{
	return membrane_potential_; 
} 

bool Neuron::Is_it_excitatory() const
{ 
	return excitatory_; 
} 
void Neuron::set_type(bool f)
{ 
	excitatory_ = f; 

}


double Neuron::get_buffer(int i) const
{
	return Ring_buffer_[i]; 
} 

double Neuron::buffer_size() const
{
	return Ring_buffer_.size(); 
}


double Neuron::random_input() 
{	
	static std::random_device number_random; 
	static std::mt19937 engine(number_random()); //random number generator 
	
	int v = (eta_* spike_potential_)/(weight_ * tau_); 
	static std::poisson_distribution<int> poisson(v*time_increment_); //generate a poisson distribution with mean value = mean rate of firing v. 
	
	int input = poisson(engine); //will call the poisson distribution on a randomly generated number 
	return input;
}
vector<double> Neuron::getTheSpikes() const
{
	return Spike; 
} 

std::vector<unsigned int> Neuron::getMyTargets() const
{
	return MyTargets_;
}

void Neuron::changeMyTargets(unsigned int target_id) 
{
	MyTargets_.push_back(target_id);
}
