#include "network.hpp" 

#ifndef EXPERIMENT_HPP
#define EXPERIMENT_HPP
class Experiment 
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
