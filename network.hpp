#include "neuron.hpp" 

class Network {
	public: 
	Network(); 
	~Network(); 
	
	//states of neurons; 
	
	struct New { 
		State state_neuron_; 
		// type of neuron; excitatory or inhibtory ? 
		
	}; 
	double nbre_excitatory_;
	double neurons_spiking_; 
	double neurons_refractory_;
	double neurons_buffering_; 
	
	//methods; 
	void neurons_interact(); 
	

};
