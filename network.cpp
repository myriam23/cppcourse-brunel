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

	} 
	
	for(int j = 0; j < nbre_inhibitory_; ++j) 
	{ 
		Neuron* N = new Neuron(); 
		add_to_network(N); 
		N->set_type(false); 

	}
	create_matrix(); 
	
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
	} 
	
	for(int j = 0; j < nbre_inhibitory_; ++j) 
	{ 
		Neuron* N = new Neuron(global, t, i, del, w); 
		add_to_network(N); 
		N->set_type(false);
	}
	 
	create_matrix(); 		
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
		bool spiking = element->update_state_(); 
		
		if(spiking) 
		{ 
			for (int row = 0; row < getPop(); ++row) 
			{ 
					int g = 1; 
					if(element->Is_it_excitatory() == false) 
					{ 
						g *= -5; 
					}
					int j = TheMatrix_[line][row];  
					Population_[row]->write_buffer(g*j); 
					
				}
			}
			++line; 
	}
			
}


int Network::getPop()
{
	return Population_.size(); 	
}

void Network::write()
{	
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


int Network::roll(int min, int max)
{
	std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    
	return dis(gen);
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
		std::vector<int> temp(getPop(), 0); 
		for(int line = 0; line < getPop(); ++line)
		{
			int i = 0; 
			int max_ex = nbre_excitatory_ / 10; 
			while(i < max_ex)
			{ 
				int column = roll(0, nbre_excitatory_ -1); 
				int random = roll(0,10);
				if(temp[column]== 0) 
				{
					temp[column]  = random;
					++i;
				}
			}
			int j = nbre_excitatory_; 
			int Max_in = nbre_inhibitory_ / 10; 
			while(j < Max_in) 
			{
				int column = roll(nbre_excitatory_, getPop()); 
				int random = roll(0,10); 
				if(temp[column] == 0) 
				{ 
					temp[column] = random; 
					++j;
				}
			}
				
			TheMatrix_[line] = temp; 
		}
		//refine_network();
}
	

void Network::refine_network()
{
	for(int column = 0; column < getPop(); ++column) 
	{
		int i = nbre_excitatory_; 
		int max = nbre_excitatory_ / 10; 
		std::cout << "max ex " << max << std::endl; 
		while(i > max) 
		{
			
			int row = roll(0, nbre_excitatory_); 
			if(TheMatrix_[row][column] != 0)
			{
				std::cout << "changing matrix for ex " << std::endl; 
				TheMatrix_[row][column] = 0; 
				--i;
			}
		}
		
		int j = nbre_inhibitory_; 
		int Max = nbre_inhibitory_ / 10; 
		while(j > Max) 
		{ 
			
			int row = roll(nbre_excitatory_ + 1, getPop()); 
			if(TheMatrix_[row][column] != 0)
			{ 
				std::cout << "row " << row << " col " << column << " " << std::endl; 
				TheMatrix_[row][column] = 0; 
				--j;
			}
			std::cout << " j " <<j << std::endl; 
		} 
	}
}

	

