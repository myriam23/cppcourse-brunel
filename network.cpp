#include "network.hpp"


Network::Network(std::array< double, 2> temp, double e, double g) 
:nbre_excitatory_(10000), nbre_inhibitory_(2500), dt(0.1)
{
	network_time = temp[0];
	end_simulation = temp[1];
	/** This loop allows the creation of the neurons simultaneously to the creation of pointers on them. 
	 * It will first run for all excitatory neurons of the network and then the inhibitory ones. This allows for an
	 * easier indexation and later access of the neurons depending on their type*/
	for(unsigned int i = 0; i < nbre_excitatory_; ++i) 
	{ 
		Neuron* N = new Neuron(temp, e,g ,true); 
		add_to_network(N); 	
	} 
	
	for(unsigned int j = 0; j < nbre_inhibitory_; ++j) 
	{ 
		Neuron* N = new Neuron(temp, e,g ,false); 
		add_to_network(N); 
	}
	create_connections(); 
}

Network::Network(std::array< double, 2> temp,  double h,  double del, double w, int Ni, int Ne,  double e, double g)
: nbre_excitatory_(Ne), nbre_inhibitory_ (Ni)
{ 
	dt = h;
	network_time = temp[0];
	end_simulation = temp[1];
	
	for(unsigned int i = 0; i < nbre_excitatory_; ++i) ///the first Ne elements of Populations_ will be excitatory neurons
	{ 
		Neuron* N = new Neuron(temp, h, del, w, e, g,true); 
		add_to_network(N); 	
	} 
	for(unsigned int j = 0; j < nbre_inhibitory_; ++j) 
	{ 
		Neuron* N = new Neuron(temp, h, del, w, e, g, false); 
		add_to_network(N); 
	}
	
	create_connections();	
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

/** This method induces the update of the Network and all its neurons every time incrementation through the 
 * call to the update_state_() method of the neurons. 
 * Everytimes a neuron is updated, the method checks whether or not it has spiked and if so, 
 * the spike is sent to all targets of the neuron that has spiked. The sending of the spike 
 * consists of saving the efficiency of the spiking neuron in every Ring_Buffer of its targets at 
 * the correct index. Thus the index has to take into account the delay of the spike as it has been defined 
 * during the construction of the network and all its neurons.
 * Moreover, for the first 50 neurons spiking, the time at which they spiked is saved in a text file. 
 * */
void Network::update()
{	 
	unsigned int size_pop = getPop();
	std::vector< int>* temp(nullptr);
	bool spiking(false);
	unsigned int size(0);
	double g(0);
	unsigned int line(0);
	std::ofstream Spiketime("spikeTime.txt"); 

	while(network_time < end_simulation) 
	{
		for(unsigned int i = 0; i < size_pop; ++i) 
		{ 
			spiking = Population_[i]->update_state_(); 
			
			if(spiking) 
			{ 
				if(i < 50) 
				{
					
					if(Spiketime.is_open()) 
					{ 
						Spiketime << network_time << '\t' << i << '\n' ; 
					}else 
					{ 
						std::cerr << "Could not save spike time." << std::endl; 
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
}

unsigned int Network::getPop() const
{
	return Population_.size(); 	
}

void Network::add_to_network(Neuron* n) 
{
	Population_.push_back(n); 	
}			
/** This method return a uniformly distributed number in the range taken as argument. 
 * It is used mainly during the creation of the connections. However, it is a method, because I use it for testing as well. 
 * The random device and generator have been declared as static to allow for a faster execution of the call to the method. 
 * Nevertheless, the distribution itself must not be declared static or it will be identical for all calls. 
 * */
unsigned int Network::roll(int min, int max)
{
	static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(min, max);
	return dis(gen);
}
/** The first loop will go over the whole population of the network and 
 * for each neuron it will randomly choose 10% percent of the population as sources of inputs. 
 * Each neuron will thus receive an input from 10% of the inhibitory neurons of 
 * the population and 10% of the excitatory neurons. 
 * To allow for a faster execution of the simulation, the second for loop has been replaced
 * by a condition check. 
 * Once a neuron has been selected as source, its target vector must be accessed so that
 * the source knows to whom it must send the input.
 * */
void Network::create_connections()
{ 
	static unsigned int max_ex = 0.1 * nbre_excitatory_; 
	static unsigned int max_in = 0.1 * nbre_inhibitory_;
	unsigned int id_ex = 0;  
	unsigned int id_inhib = 0;
	
	for(unsigned int i = 0; i < getPop(); ++i) 
	{	
		for(unsigned int index = 0; index < max_ex; ++index)
		{
			id_ex = roll(0, nbre_excitatory_ -1);   	
			assert(id_ex < getPop()); 
			Population_[id_ex]->changeMyTargets(i);
			
			if(index < max_in) 
			{ 			
				id_inhib = roll(nbre_excitatory_, getPop()-1); 	
				assert(id_inhib < getPop());
				Population_[id_inhib]->changeMyTargets(i);	
			}				
		}	
	}
}

