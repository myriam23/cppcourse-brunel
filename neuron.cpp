#include "neuron.hpp"
#include <vector>
#include <cmath>
#include <fstream> 
#include <iostream> 
#include <array>
using namespace std; 


Neuron::Neuron(double time = 0) 
{
	actual_time_ = time; 
	tau_ = 20; 
	spike_.efficacy_ = 5; 
	membrane_potential_ = 0; 
	number_spikes_ = 0; 
	current_state_ = Buffering; 
	
	} 
Neuron::~Neuron(){} 

void Neuron::update_state_(double dt, double clock, std::vector<double> tab, double i)
{
	if((tab[0] != 0) and (i != 0)) {
		actual_time_ = tab[0]; 
		arriving_current_ = i; 
	}
	
	
	while (actual_time_ < tab[1]) {
		if (current_state_ == Buffering) { 
			
			membrane_potential_= ((exp(-dt/tau_) * membrane_potential_) + (arriving_current_ * membrane_resistance_ * (1 - exp(-dt/tau_))));
			
			actual_time_ += dt; 
			
			if(membrane_potential_ >= spike_potential_) 
				{ 
					number_spikes_ += 1; 
			
					/*std::array<double, 2> temp; //not needed anymore for interaction
					temp[0] = membrane_potential_; 
			
					temp[1] = actual_time_;
			 
					membranepot_spiketime_.push_back(temp); */
					
					
					current_state_ = Spiking; //differentiate between spiking and refractory vecause spiking bbecause spiking will interact
					
					spike_.time_of_spike_ = actual_time_; 
					
					exiting_current_ = 500; //not sure how the exiting current is defined yet
			
			}
			
		}
		if(spike_.time_of_spike_ + refractory_period_ > clock) { 
			current_state_ = Buffering; 
		} 

	}
		cout << "You have reached the end of your interval. " << endl; 
			
}

void Neuron::interact(Neuron& post_syn) 
{
	if(this->current_state_ == Spiking) { 
		post_syn.actual_time_ = this->spike_.time_at_arrival_;
		post_syn.arriving_current_ = this->exiting_current_; 
		this-> current_state_ = Refractory; //will have to change this to make it possible to spike multiple neurons at the same time before turning refractory 
		
	}else{ 
		cout << "These neurons cannot interact at the moment." << endl; 
	}
}

/*double Neuron::spikes_number() 
{
	return spike_time_.size(); 
	
}
*/
/*void Neuron::write_in_file() 
{
	if(number_spikes_ != 0) { 
		ofstream mySpikes("mySpikes.txt"); 
		if(mySpikes.is_open())
		{
			int i;
			int j; 
			
			cout << " lingne 1 " << membranepot_spiketime_[0][0] << "...." << membranepot_spiketime_[0][1] << endl; 
		//cout << "nombre spike " << spikes_number() << endl;
			for(i = 0; i <= number_spikes_; ++i) 
				{ 
					for(j = 0; j <2; ++j) 
						{
			//cout << "writing loop " << endl; 
				mySpikes << membranepot_spiketime_[i][j] << endl; 
		}
	}
		mySpikes.close();
		//cout << "CLOSED " << endl; 
		}else{ 
				cout << "Unable to save spike time and membrane potential." << endl; 
			} 
	} 
}*/
