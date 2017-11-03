#include "network.hpp"
#include <cassert> 
#include <iostream> 
#include <fstream> 



Network::Network(std::array< double, 2> temp, double g) ///default constructor
:nbre_excitatory_(10000), nbre_inhibitory_(2500), dt(0.1)
{
	network_time = temp[0];
	end_simulation = temp[1];
 
	for(unsigned int i = 0; i < nbre_excitatory_; ++i) ///the first Ne elements of Populations_ will be excitatory neurons
	{ 
		Neuron* N = new Neuron(temp, true,g); 
		add_to_network(N); 
	} 
	
	for(unsigned int j = 0; j < nbre_inhibitory_; ++j) 
	{ 
		Neuron* N = new Neuron(temp, false,g); 
		add_to_network(N); 
	 
	}
	create_connections(); 
	std::cout<<"done creating connections." <<std::endl;
}

Network::Network(std::array< double, 2> temp,  double h,  double del, double w, int Ni, int Ne,  double e, double g)
: nbre_excitatory_(Ne), nbre_inhibitory_ (Ni)
{ 
	dt = h;
	network_time = temp[0];
	end_simulation = temp[1];
	
	for(unsigned int i = 0; i < nbre_excitatory_; ++i) ///the first Ne elements of Populations_ will be excitatory neurons
	{ 
		Neuron* N = new Neuron(temp, h, del, w, e, true,  g); 
		add_to_network(N); 
		

	} 
	
	for(unsigned int j = 0; j < nbre_inhibitory_; ++j) 
	{ 
		Neuron* N = new Neuron(temp, h, del, w, e, false,  g); 
		add_to_network(N); 
	
	}

	create_connections();
	 	std::cout<<"done creating connections." <<std::endl;	
}

Network::~Network()
{
	for(auto& element : Population_ ) 
	{ 
		 delete element; 
		 element = nullptr;
	}
	Population_.erase(Population_.begin(), Population_.end()); 
	
}

std::vector<Neuron*> Network::getPopulation_() const
{
	return Population_; 
} 

void Network::update()
{	 
	unsigned int size_pop = getPop();
	std::vector< int>* temp(nullptr);
	bool spiking(false);
	unsigned int size(0);
	double g(0);
	unsigned int line(0);
	std::ofstream Spiketime("spikeTime.txt"); 
	std::ofstream checkref("checkref.txt"); 
	std::ofstream checkpot("checkpot.txt"); 

	while(network_time < end_simulation) 
	{
		for(unsigned int i = 0; i < size_pop; ++i) 
		{ 
			spiking = Population_[i]->update_state_(); 
			
			if(spiking) 
			{ 
				if(i < 50) 
				{
					
					/*if(checkref.is_open())
					{ 
						checkref << "neurone " << i << " ";
						for(int j=0; j < Population_[i]->tempspike.size(); ++j) 
						{
							checkref << Population_[i]->tempspike[j] << '\t'; 
						} 
					checkref << '\n'; 
					}
					if(checkpot.is_open()) 
					{ 
						checkpot << "neuron " << i << " " ;
						for(int r = 0; r < Population_[i]->potentieltemps.size(); ++r) 
						{
						checkpot << Population_[i]->potentieltemps[r] << '\t'; 
						}
					}checkpot << '\n'; */
					
					if(Spiketime.is_open()) 
					{ 
						Spiketime << network_time << '\t' << i << '\n' ; 
					}else 
					{ 
						std::cerr << "could not save spike time " << std::endl; 
					}
				}
					
					temp = new std::vector< int>(Population_[i]->getMyTargets()) ; 
					size = temp->size();
					g = Population_[i]->getweight(); 
					for(unsigned int row = 0; row < size; ++row) 
					{ 
						line = temp->at(row); 
						assert(line < size_pop);
						Population_[line]->write_buffer(g); 
					}
					
					delete temp;
					temp = nullptr;
			}

		}
		network_time += dt; 
	};
	Spiketime.close();
	checkref.close();
	checkpot.close();
			
}

void Network::savetime(unsigned int t) 
{ 
	
}
 unsigned int Network::getPop() const
{
	return Population_.size(); 	
}

void Network::add_to_network(Neuron* n) 
{
	Population_.push_back(n); 	
}			


unsigned int Network::roll(int min, int max)
{
	static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(min, max);
    
	return dis(gen);
}

void Network::create_connections()
{ 
	static unsigned int max_ex = 0.1 * nbre_excitatory_; 
	static unsigned int max_in = 0.1 * nbre_inhibitory_;
	unsigned int id; 
	unsigned int id2;
	
	for(unsigned int i = 0; i < getPop(); ++i) 
	{		
		for(unsigned int index = 0; index < max_ex; ++index)
		{
			id = roll(0, nbre_excitatory_ -1 );   
			id2 = roll(nbre_excitatory_, getPop()-1); 
			assert(id < getPop()); 
			assert(id2 < getPop()); 
			Population_[id]->changeMyTargets(i);
			if(index < max_in) { Population_[id2]->changeMyTargets(i); }	

		}	
	}
}

