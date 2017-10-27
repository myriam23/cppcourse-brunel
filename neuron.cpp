#include "neuron.hpp"
#include <vector>
#include <cmath>
#include <fstream> 
#include <iostream> 
#include <array>

using namespace std; 

Neuron::Neuron()
: membrane_potential_(0), number_spikes_(0), time_of_spike_(0),
actual_time_(0), time_increment_(0.1), arriving_current_(1), 
delay_(1.5), weight_(0.1), refractory_(false), excitatory_(true), 
MyTargets_(10, 1), 
Ring_buffer_(16,0) ///have to manually put the size of the ring buffer for the default constructor
{
}

Neuron::Neuron(double time, double h, double i, double del, double w) 
: membrane_potential_ (0), number_spikes_(0), time_of_spike_(0),
refractory_(false), excitatory_(true)
{

	actual_time_ = time; 
	time_increment_ = h; 	
	arriving_current_ = i;
	delay_ = del; 
	weight_ = w;
	
	int size = time_to_steps(delay_) + 1; 
	
	for(int a = 0; a < size; ++a) 
	{ 
		Ring_buffer_.push_back(0);
	}
	
	for(int a = 0; a < 10; ++a) 
	{ 
		MyTargets_.push_back(1);
		}
	
} 
Neuron::~Neuron(){} 

bool Neuron::update_state_()
{			
		if (!refractory_) 
		{ 
			
			membrane_potential_= ((exp(-time_increment_/tau_) * membrane_potential_) + (arriving_current_ * membrane_resistance_ * (1 - exp(-time_increment_/tau_)))) + read_buffer();//  + poisson gen = vext * J * h * Ce + ADD WEIGHT OF INCOMING SPIKES  
			
			actual_time_ += time_increment_;
			
			
			if(membrane_potential_ > spike_potential_) 
			{ 
				
				number_spikes_ += 1; 

				refractory_ = true; 
				
				time_of_spike_ = actual_time_;
				save_spike(membrane_potential_, time_of_spike_);  
				write_in_file(); 
				membrane_potential_ = 0; 
				
				return true; 
			}
			
		}else{
			if(time_of_spike_ + refractory_period_ > actual_time_) 
			{ 
				//std::cout << "on est réfractaire" << std::endl;
				refractory_ = false; 
			} 
			
			return false; 
		}
	return false;
}
			

void Neuron::save_spike(double v, double t) 
{ 
	std::array<double, 2> temp;
	temp[0] = t; 
	temp[1] = v;
	membranepot_spiketime_.push_back(temp); 
					
}
void Neuron::write_in_file()  //considering calling the method in update_state rather than in main() 
{
	if(number_spikes_ != 0) 
	{ 
		ofstream mySpikes("mySpikes.txt"); 
		if(mySpikes.is_open())
		{
			int i;
			int j; 
			
			for(i = 0; i < number_spikes_; ++i) 
			{ 
				for(j = 0; j < 2; ++j) 
				{
					if(j ==0 )
					{ mySpikes << "the Neuron spiked at " << membranepot_spiketime_[i][j]; 
						} else { mySpikes << " with a membrane potential at " << membranepot_spiketime_[i][j] << endl;
				} 
				 
		}
	}
		mySpikes.close();
		
		}else{ 
				cout << "Unable to save spike time and membrane potential." << endl; 
			} 
	} 
}


int Neuron::time_to_steps(double t) 
{ 
	
	return static_cast<unsigned long>(std::ceil(t/time_increment_)); 
	
}

double Neuron::read_buffer() //gives the J for the current step 
{ 
	return Ring_buffer_[current_index()]; 
} 

int Neuron::current_index() 
{ 	
	return time_to_steps(actual_time_) % (time_to_steps(delay_) + 1);	
}

void Neuron::write_buffer(int n) 
{ 
	int delay_step = time_to_steps(delay_);
	
	Ring_buffer_[(current_index() + delay_step) % (delay_step + 1)] += n * weight_; 
		
} 

void Neuron::set_i_ext(double i) 
{ 
	arriving_current_ = i; 
	
} 
double Neuron::get_v_m() const
{
	return membrane_potential_; 
} 

std::vector<int> Neuron::get_MyTargets_() 
{
	return MyTargets_; 
	
}

bool Neuron::Is_it_excitatory() const
{ 
	return excitatory_; 
} 
void Neuron::set_type(bool f)
{ 
	excitatory_ = f; 
	/*if(!excitatory_) 
	{ 
		weight_ *= (-5);
	}*/
}

void Neuron::set_MyTargets(int t) 
{ 
	MyTargets_.resize(t); 
}

void Neuron::fill_MyTargets(int i, int  v) 
{
	MyTargets_[i] = v; 
}

double Neuron::get_buffer(int i) const
{
	return Ring_buffer_[i]; 
} 

std::vector<double> Neuron::get_buffer2() const
{
	return Ring_buffer_; 
}
