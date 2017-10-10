#include "neuron.hpp"
#include <vector>
#include <cmath>
#include <fstream> 
#include <iostream> 
#include <array>
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
			number_spikes += 1; 
			
			std::array<double, 2> temp; 
			temp[0] = membrane_potential_; 
			
			temp[1] = current_time_;
			
			cout << "pote membrane " << temp[0] << endl; 
			cout << " temps " << temp[1] << endl; 
			 
			membranepot_spiketime_.push_back(temp); 
			
			}	
		}
	}
		cout << "You have reached the end of your interval. " << endl; 
			
}

/*double Neuron::spikes_number() 
{
	return spike_time_.size(); 
	
}
*/
void Neuron::write_in_file() 
{
	if(number_spikes != 0) { 
		ofstream mySpikes("mySpikes.txt"); 
		if(mySpikes.is_open())
		{
			int i;
			int j; 
			
			cout << " lingne 1 " << membranepot_spiketime_[0][0] << "...." << membranepot_spiketime_[0][1] << endl; 
		//cout << "nombre spike " << spikes_number() << endl;
			for(i = 0; i <= number_spikes; ++i) 
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
}
