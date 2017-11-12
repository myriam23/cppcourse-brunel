#include "network.hpp" 

#ifndef EXPERIMENT_HPP
#define EXPERIMENT_HPP
class Experiment /*!<This class allows to simulate the different networks discussed in the Brunel paper.*/ 
{
	public:
	Experiment(); 
	~Experiment(); 
	void ExperimentA(); 
	void ExperimentB();
	void ExperimentC(); 
	void ExperimentD(); 
	
	private: 
	std::string file; 
}; 

#endif
