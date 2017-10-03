#include "neuron.hpp"
#include <array>
#include <vector>
#include <cmath>
#include <fstream> 
#include <iostream> 

using namespace std; 
Neuron::Neuron() {} 
Neuron::~Neuron(){} 

void Neuron::update_state_(std::vector<double> tab, double i, double dt)
{ 
	cout << "IN UPDATE " << endl; 
	double tau(20); 
	double current_time_(tab[0]); 
	
	while (current_time_ < tab[1]) {
		if (refractory_state_ == true) { 
			
			membrane_potential_ = 0; 
			
		} else { 
			
			membrane_potential_= ((exp(-dt/tau) * membrane_potential_) + (i * membrane_resistance_ * (1 - exp(-dt/tau))));
			
			current_time_ = current_time_ + dt; 
						
			//cout << "current_time" << current_time_ << endl; 
			cout << "membrane pot " << membrane_potential_ << endl; 
			if(membrane_potential_ > spike_potential_) 
			{ 
				cout << "SPIKING " << endl; 
			
			spike_time_.push_back(current_time_); 
			}	
		}
	}
			
}

double Neuron::spikes_number() 
{
	return spike_time_.size(); 
	
}

void Neuron::write_in_file() 
{
	if(spikes_number() != 0) { 
		ofstream mySpikes("mySpikes.txt"); 
		if(mySpikes.is_open())
		{
			int i;
		//cout << "nombre spike " << spikes_number() << endl;
			for(i = 0; i <= spikes_number(); ++i) 
		{ 
			//cout << "writing loop " << endl; 
		mySpikes << spike_time_[i] << endl; 
		}
		mySpikes.close();
		//cout << "CLOSED " << endl; 
		}else{ 
				cout << "Unable to save spike time." << endl; 
			} 
	} 
}
