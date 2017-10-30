#include "network.hpp"
#include <cassert> 
#include <iostream> 
#include <fstream> 



Network::Network(std::array<double, 2> temp) ///default constructor
:nbre_excitatory_(10000), nbre_inhibitory_(2500)
{
	int pop = nbre_excitatory_+ nbre_inhibitory_; 
 
	for(int i = 0; i < nbre_excitatory_; ++i) ///the first Ne elements of Populations_ will be excitatory neurons
	{ 
		Neuron* N = new Neuron(temp); 
		add_to_network(N); 

	} 
	
	for(int j = 0; j < nbre_inhibitory_; ++j) 
	{ 
		Neuron* N = new Neuron(temp); 
		add_to_network(N); 
		N->set_type(false); 
		 


	}
	create_connections(); 
	
}

Network::Network(std::array<double, 2> temp, double h, double i, double del, double w, int Ni, int Ne, int e)
: nbre_excitatory_(Ne), nbre_inhibitory_ (Ni)
{ 
	int pop = nbre_excitatory_+ nbre_inhibitory_;
	
	for(int i = 0; i < nbre_excitatory_; ++i) ///the first Ne elements of Populations_ will be excitatory neurons
	{ 
		Neuron* N = new Neuron(temp, h, i, del, w, e); 
		add_to_network(N); 
		

	} 
	
	for(int j = 0; j < nbre_inhibitory_; ++j) 
	{ 
		Neuron* N = new Neuron(temp, h, i, del, w, e); 
		add_to_network(N); 
		N->set_type(false); 
	}
	 
	create_connections(); 		
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
		bool spiking = element->update_state_(); 
		
		if(spiking) 
		{ 
			std::vector<unsigned int> temp = element->getMyTargets(); 
			int g = 1; 
			if(element->Is_it_excitatory() == false) { g = -5; }
			
			for (unsigned int row = 0; row < temp.size(); ++row) 
			{ 
					Population_[temp[row]]->write_buffer(g); 			
			}
		}
	}
			
}


unsigned int Network::getPop() const
{
	return Population_.size(); 	
}

void Network::write()
{	
	std::ofstream matrix("mymatrix.txt"); 
	if(matrix.is_open())
	{
		unsigned int i = 0; 
		for(auto& element : Population_) 
		{
			std::vector<unsigned int> temp = element->getMyTargets(); 
			matrix << "Neurone " << i << " has the following targets" << '\t';
			unsigned int max = temp.size(); 
			
			for(unsigned int index = 0; index < max; ++index) 
			{
				matrix << temp[index] << '\t';
			}
			matrix << '\n';
			++i;
		}
	}else{ std::cerr << "Could not open matrix file." << std::endl; }
	matrix.close();
	
	std::ofstream theSpikes("Spikes.txt"); 
	if(theSpikes.is_open())
	{
		for(auto& element :Population_) 
		{
			for(unsigned int i = 0; i < element->getTheSpikes().size(); ++i)
			{
				theSpikes << '\t' << element->getTheSpikes()[i] << '\t' << '\n'; 
			}
		}
	}else { std::cerr << "Could not save spikes of network. " << std::endl; 
	}
	theSpikes.close(); 
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
			for(int j=0; j < element->buffer_size(); ++j) 
			{ 
			
			Buffers << element->get_buffer(j) << " "; 
			
			
			}
			++i; 
			Buffers << std::endl;
			
		} 
	}else{ std::cerr << "Could not open Buffer file." << std::endl; } 
	
	Buffers.close();
}

void Network::create_connections()
{ 
	std::cout << "creating connections " << std::endl; 
	
	for(unsigned int i = 0; i < getPop(); ++i) 
	{	
		unsigned int max_ex = 0.1 * nbre_excitatory_; 
		unsigned int max_in = 0.1 * nbre_inhibitory_;
			
		for(unsigned int index = 0; index < max_ex; ++index)
		{
			int id = roll(0, nbre_excitatory_ -1 );   
			
			Population_[id]->changeMyTargets(i);
 
		}
		
		for(unsigned int index = 0; index < max_in; ++index)
		{
			int id = roll(nbre_excitatory_, getPop()-1);   
		
			Population_[id]->changeMyTargets(i);	
		}	
	}	
}
	
	

