#include "network.hpp"
#include <cassert> 
#include <iostream> 
#include <fstream> 


Network::Network(double global, double t)
{ 
	for(int i = 0; i < 10; ++i) 
	{ 
		Neuron* N = new Neuron(global, t); 
		add_to_network(N); 
		
	}	
	std::cout << "la population est de la taille" << Population_.size() << std::endl; 
	create_connexions(); 
	
/*	
	for(int j = 1001; j<=12500; ++j) 
	{ 
		Inhibitory* */
		

	/*for(int i = 0; i < MyConnections_.size(); ++i) { 
		for(int j = 0; i < MyConnections_[i].size(); ++j) { 
			//assert that if(i == j) { MyConnections_[i][j] = 0; }
		}
	}*/
			
		

}

Network::~Network()
{
	for (auto element : Population_ ) 
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
					
					for (int i = 0; i < element->MyTargets_.size(); ++i) 
					{ 
						if(element->MyTargets_[i] != 0) 
						{ 
							//std::cout << "mon target est " << element->MyTargets_[i] << std::endl; 
							
							Population_[i]->write_buffer(element->MyTargets_[i]); 
							
						}
					}
				}
				
				/*for(int i = 0; i < element->MyTargets_.size(); ++i) 
				{
					std::cout << " on écrit " << std::endl; 
					std::ofstream myTargets("myTargets.txt"); 
					if(myTargets.is_open())
					{ 
						myTargets << element->MyTargets_[i] << std::endl; 
					}
					myTargets.close();
				
				}*/
				
		}
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
		
		for(int j = 0; j < element->MyTargets_.size(); ++j) 
		{
			element->MyTargets_[j] = roll(0, 10); 
			
			
			
			//std::cout << "mon nombre de connextions est " << element->MyTargets_[j] << std::endl; 
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
