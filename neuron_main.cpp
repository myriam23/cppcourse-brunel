#include <array>
#include "neuron.hpp" 
#include <cmath> 
#include <iostream>
#include <vector> 
#include "network.hpp"

using namespace std; 


int main()
{
	double stop_time(1000); 
	double time_inc(0.1); 
	double simulation_clock(0); 
	double input_current_ = 0; 
	vector<double> time_interval_; 
	double wei(0); 
	double del(0); 
	string ans = "yes"; 
	
	cout << "Welcome to neurone simulation. Would you like to choose your own parameters instead of the default ones ? " << endl;
	cin>> ans; 
	
	if(ans == "yes") 
	{ 
		cout << "Please input the current you would like to apply." << endl; 
		cin >> input_current_; 
		cout << "What are the delay and weight of your neurons ? " << endl; 
		cin >> del; 
		cin >> wei;
		int c; 
		int d;
		do { 
			cout << "How long do you want your simulation to run in [ms] (Note: no more than 1000 ms) ? " << endl;  
			double b; 
			cin >> b; 
			time_interval_.push_back(0);
			time_interval_.push_back(b); 
			
			cout<<"How many excitatory neurons do you want in your network ?" << endl; 
			cin >>c;
			cout<<"How many inhibitory neurons do you want in your network ?" << endl; 
			cin >> d;
			
		 
		 } while ((time_interval_[1] > stop_time));  
	
			simulation_clock = time_interval_[0];										
			Network network(simulation_clock, time_inc, input_current_, del, wei, d, c );
			
			while(simulation_clock < time_interval_[1]) 
			{ //specified here instead of inside the method update so I dont need to give the interval tab
				
				network.update(); 
				simulation_clock += time_inc; 	 

			}
			network.write();
			network.current_buffers(); 

		} else { 
			
			/*Network network(); 
			
			while(simulation_clock < time_interval_[1]) 
			{ 
				network.update(); 
				simulation_clock += time_inc; 	 
			}
			network.write();
			network.current_buffers();
		*/
		}  
	
	cout << "The simulation has ended." << endl;
	
}


