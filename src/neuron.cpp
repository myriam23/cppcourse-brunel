#include "neuron.hpp"
#include <vector>
#include <cmath>
#include <fstream> 
#include <iostream> 
#include <array>

using namespace std; 

Neuron::Neuron(double time = 0, double h = 0.1) 
{

	actual_time_ = time; 
	time_increment_ = h; 
	membrane_potential_ = 0; 
	number_spikes_ = 0; 
	time_of_spike_ = 0; 
	arriving_current_ = 1.01;
	delay_ = 1.5; 
	weight_ = 0.1;
	refractory_ = false; 

	int size = time_to_steps(delay_) + 1; 
	
	std::cout << "taille buffer " << size << std::endl; 
	
	for (int i = 0; i < size; ++i)  /// tried to initialize with ring_buffer_(size, 0.0) but did not work
	{
		
		Ring_buffer_.push_back(0.0);
	
	}
	
	for (int i = 0; i < 10; ++i)  /// tried to initialize with ring_buffer_(size, 0.0) but did not work
	{
		
		MyTargets_.push_back(0.0);
		//membranepot_spiketime_.push_back(0); 
	}
	
} 
Neuron::~Neuron(){} 

bool Neuron::update_state_()
{			
		if (!refractory_) 
		{ 
			
			//std::cout << "not ref and mem pot = " << membrane_potential_ << std::endl;  

			
			membrane_potential_= ((exp(-time_increment_/tau_) * membrane_potential_) + (arriving_current_ * membrane_resistance_ * (1 - exp(-time_increment_/tau_)))) + read_buffer();//  + poisson gen = vext * J * h * Ce + ADD WEIGHT OF INCOMING SPIKES  
			
			std::cout << "mon ring buffer contient " << read_buffer() << std::endl; 
			
			
			actual_time_ += time_increment_;
			
			std::cout << "AU TEMPS " << actual_time_ << " MON POT MEMB EST " << membrane_potential_ << std::endl; 
			
			if(membrane_potential_ > spike_potential_) 
			{ 
				//std::cout << "on spike" << std::endl; 
				
				number_spikes_ += 1; 
				
				save_spike(membrane_potential_, actual_time_); 
				
				refractory_ = true; 
				
				time_of_spike_ = actual_time_; 
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
	temp[0] = v; 
	temp[1] = t;
	membranepot_spiketime_.push_back(temp); 
					
}
void Neuron::write_in_file()  //considering calling the method in update_state rather than in main() 
{
	if(number_spikes_ != 0) { 
		ofstream mySpikes("mySpikes.txt"); 
		if(mySpikes.is_open())
		{
			int i;
			int j; 
			
			for(i = 0; i <= number_spikes_; ++i) 
				{ 
					for(j = 0; j <2; ++j) 
						{
				mySpikes << membranepot_spiketime_[i][j] << endl; 
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
	//std::cout << "l'index actuel est " << time_to_steps(actual_time_) % (time_to_steps(delay_) + 1) << std::endl; 
	
	return time_to_steps(actual_time_) % (time_to_steps(delay_) + 1);
	
}

void Neuron::write_buffer(int n) 
{ 
	int delay_step = time_to_steps(delay_);
	
	Ring_buffer_[(current_index() + delay_step) % (delay_step + 1)] += n * weight_; 
	
	//std::cout<< " le step actuel est " << time_to_steps(actual_time_) << std::endl; 
	
	
	//std::cout << " le buffer numer " << ((current_index() + delay_step) % (delay_step + 1))<< " est rempli " << std::endl; 
	
	
} 
		
