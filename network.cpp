#include "network.hpp"
#include <cassert> 
#include <iostream> 
#include <fstream> 

Network::Network() ///default constructor
:nbre_excitatory_(10000), nbre_inhibitory_(2500)
{
	int pop = nbre_excitatory_+ nbre_inhibitory_; 
	TheMatrix_.resize(pop); 
	for(int i = 0; i < nbre_excitatory_; ++i) ///the first Ne elements of Populations_ will be excitatory neurons
	{ 
		Neuron* N = new Neuron(); 
		add_to_network(N); 
		N->set_MyTargets(pop);

	} 
	
	for(int j = 0; j < nbre_inhibitory_; ++j) 
	{ 
		Neuron* N = new Neuron(); 
		add_to_network(N); 
		N->set_type(false); 
		N->set_MyTargets(pop); 

	}
	
	create_connexions();  
	create_matrix();
	refine_network(); 
	
}

Network::Network(double global, double t, double i, double del, double w, int Ni, int Ne)
: nbre_excitatory_(Ne), nbre_inhibitory_ (Ni)
{ 
	int pop = nbre_excitatory_+ nbre_inhibitory_;
	TheMatrix_.resize(pop);
	for(int i = 0; i < nbre_excitatory_; ++i) ///the first Ne elements of Populations_ will be excitatory neurons
	{ 
		Neuron* N = new Neuron(global, t, i, del, w); 
		add_to_network(N); 
		N->set_MyTargets(pop); 

	} 
	
	for(int j = 0; j < nbre_inhibitory_; ++j) 
	{ 
		Neuron* N = new Neuron(global, t, i, del, w); 
		add_to_network(N); 
		N->set_type(false);
		N->set_MyTargets(pop);  

	}
	
	create_connexions();  
	create_matrix(); 
	refine_network(); 		
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
	int line = 0; 
	for(auto& element : Population_) 
	{ 
		bool target = element->update_state_(); 
		
		if(target) 
		{ 
			for (int row = 0; row < getPop(); ++row) 
			{ 
				if(TheMatrix_[line][row] != 0) 
				{ 
					int g = 1; 
					if(element->Is_it_excitatory() == false) 
					{ 
						g *= -5; 
					}
					Population_[row]->write_buffer(g*(TheMatrix_[line][row])); 
					
				}
			}
		}
			
	}
}

int Network::getPop()
{
	return Population_.size(); 
	
}

void Network::write()
{
	std::ofstream myTargets("myTargets.txt"); 
	if(myTargets.is_open())
	{
		for(int j = 0; j < Population_.size(); ++j) /// used this type of loop instead of element because I want the number of the neuron
		{
			myTargets <<  "Neuron number " << 1+ j << " has the following connections:"  ; 
			
			for(int i = 0; i < Population_[j]->get_MyTargets_().size(); ++i) 
			{		
					myTargets << " " << Population_[j]->get_MyTargets_()[i] << " "; 
					
			}
			
			myTargets << " " << std::endl; 
		}
		
	}else{ 
		std::cerr << "Could not open MyTargets file." << std::endl; 
		}
	myTargets.close();
	
	std::ofstream matrix("mymatrix.txt"); 
	if(matrix.is_open())
	{
		for(int i = 0; i < getPop(); ++i) 
		{
			for(int j = 0; j < getPop(); ++j) 
			{ 
				matrix << " " << TheMatrix_[i][j] << " " ; 
			}
			matrix << std::endl; 
		}
		
	}else{ 
		std::cerr << "Could not open matrix file." << std::endl; 
		}
	matrix.close();
}

void Network::add_to_network(Neuron* n) 
{
	Population_.push_back(n); 	
}			

void Network::create_connexions() ///allows to fill the target tab of every neuron in the population by calling their setter. I dont want my neurons to have connections to themselves. 
{ 
	std::cout << "in create connex" << std::endl; 
	
	
	
	/*int i = 0; 	
	for(auto& element : Population_)  
	{ 	
		for(int j = 0; j < element->get_MyTargets_().size(); ++j) 
		{
			int random = roll(1,10);	
			if(i ==j) {random = 0;} 						
			element->fill_MyTargets(j, random); 			
		}
	++i; 
	}*/
}

int Network::roll(int min, int max)
{
	double x = rand()/static_cast<double>(RAND_MAX+1); 
	int that = (min + static_cast<int>( x * (max - min)) * (-1));
	
	return that;
}

void Network::current_buffers() ///buffers content at the end of the simulation
{
	std::ofstream Buffers("Buffers.txt");
	
	if(Buffers.is_open()) 
	{
		int i = 1; 
		for(auto& element : Population_) 
		{ 
			Buffers << "The neuron " << i << " buffer contains " ;
			for(int j=0; j < element->get_buffer2().size(); ++j) 
			{ 
			
			Buffers << element->get_buffer(j) << " "; 
			
			
			}
			++i; 
			Buffers << std::endl;
			
		} 
	}else{ std::cerr << "Could not open Buffer file." << std::endl; } 
	
	Buffers.close();
}

void Network::create_matrix()
{ 
		std::cout << "in create matric" << std::endl; 
		for(int i = 0; i < getPop(); ++i) 
		{ 
			for(int j = 0; j < getPop(); ++j) 
			{ 
				if( i = j) { TheMatrix_[i][j] = 0; }
				else { TheMatrix_[i][j] = 1; }
			}
		}
	/*	
	int i = 0; 
	for(auto& element : Population_) 
	{ 
		TheMatrix_[i] = element->get_MyTargets_(); 	
		++i;
	} */
}

void Network::refine_network()
{
	
	for(int j = 0; j < getPop(); ++j) 
	{
		int i = getPop(); 
		int max = i/10; 

		while(i > max)
		{
			int rand = roll(0, getPop()); ///cannot use i here as it is decremented 			
				if((j != rand) and (TheMatrix_[rand][j] != 0))  
				{
						--i; 
					TheMatrix_[rand][j] = 0; 
				}
		}
		
	}
}
