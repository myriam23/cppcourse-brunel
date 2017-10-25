#include "network.hpp"
#include <cassert> 
#include <iostream> 
#include <fstream> 

Network::Network() ///default constructor
:nbre_excitatory_(10000), nbre_inhibitory_(2500)
{
	for(int i = 0; i < nbre_excitatory_; ++i) ///the first Ne elements of Populations_ will be excitatory neurons
	{ 
		Neuron* N = new Neuron(); 
		add_to_network(N); 

	} 
	
	for(int j = 0; j < nbre_inhibitory_; ++j) 
	{ 
		Neuron* N = new Neuron(); 
		add_to_network(N); 
		N->set_type(false); 

	}
	
	//assert Population_.size() == nbre_excitatory_ + nbre_inhibitory_; 
	create_connexions();  
	
	
}

Network::Network(double global, double t, double i, double del, double w, int Ni, int Ne)
: nbre_excitatory_(Ne), nbre_inhibitory_ (Ni)
{ 
	for(int i = 0; i < nbre_excitatory_; ++i) ///the first Ne elements of Populations_ will be excitatory neurons
	{ 
		Neuron* N = new Neuron(global, t, i, del, w); 
		add_to_network(N); 

	} 
	
	for(int j = 0; j < nbre_inhibitory_; ++j) 
	{ 
		Neuron* N = new Neuron(global, t, i, del, w); 
		add_to_network(N); 
		N->set_type(false); 

	}
	
	//assert Population_.size() == nbre_excitatory_ + nbre_inhibitory_; 
	create_connexions();  
			
}

Network::~Network()
{
	for(auto element : Population_ ) 
	 { 
		 delete element; 
		element = nullptr; 
	}
	Population_.erase(Population_.begin(), Population_.end()); 
	
}

void Network::update()
{		
		for(auto& element : Population_) 
			{ 
				bool target = element->update_state_(); 
				
				if(target) 
				{ 
					//std::cout << "IL A SPIKE" << std::endl; 
					
					for (int i = 0; i < element->get_MyTargets_().size(); ++i) 
					{ 
						if(element->get_MyTargets_()[i] != 0) 
						{ 
							//std::cout << "mon target est " << element->get_MyTargets_()[i] << std::endl; 
							
							Population_[i]->write_buffer(element->get_MyTargets_()[i]); 
							
						}
					}
				}
				
		}
}

void Network::getPop()
{
	std::cout << "Your population size is " << Population_.size() << std::endl; 
	
}

void Network::write()
{
	std::ofstream myTargets("myTargets.txt"); 
	for(auto& element: Population_) 
	{
		for(int i = 0; i < element->get_MyTargets_().size(); ++i) 
		{
			if(myTargets.is_open())
			{ 
				std::cout << "FILE OPEN " << std::endl; 
				
				myTargets << element->get_MyTargets_()[i] << std::endl; 
				myTargets << "HELLO" << std::endl; 
				
				std::cout << " THIS IS Mytarget " << element->get_MyTargets_()[i]  << " " << std::endl; 
			}
			
			
		}
		
	}
		myTargets.close();
}

void Network::add_to_network(Neuron* n) 
{
	Population_.push_back(n); 
	
}			

void Network::create_connexions() 
{ 
	//for(int i = 0; i < Population_.size(); ++i) { 
		
		//std::cout << "on travaille sur le neurone numero " << i << std::endl; 
	for(auto& element : Population_)  
	{ 
		//std::cout << "la taille de mon tab target est " << element->MyTargets_.size() << std::endl; 
		
		for(int j = 0; j < element->get_MyTargets_().size(); ++j) 
		{
			element->get_MyTargets_()[j] = roll(0, 10); 
			
			
			
			//std::cout << "mon nombre de connextions est " << element->get_MyTargets_()[j] << std::endl; 
		}
	}
}

int Network::roll(int min, int max)
{
   // x is in [0,1[
   double x = rand()/static_cast<double>(RAND_MAX+1); 

   // [0,1[ * (max - min) + min is in [min,max[
   int that = (min + static_cast<int>( x * (max - min)) * (-1));
   //std::cout << "le random " << that << std::endl; 
   
   return that;
}
