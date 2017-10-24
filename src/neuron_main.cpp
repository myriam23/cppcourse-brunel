#include <array>
#include "neuron.hpp" 
#include <cmath> 
#include <iostream>
#include <vector> 
#include "network.hpp"

using namespace std; 


int main()
{
	double start_time_(0);
	double stop_time(1000); 
	double time_inc(0.1); 
	double simulation_clock(0); 
	double input_current_ = 0; 
	vector<double> time_interval_; 
	
	cout << "Welcome to neurone simulation. Please input the current you would like to apply." << endl; 
	cin >> input_current_; 
	
	do { 
		cout << "Which interval, between 0 and 1000ms, would you like to consider ? " << endl; 
		double a; 
		double b; 
		cin >> a;
		cin >> b; 
		time_interval_.push_back(a);
		time_interval_.push_back(b); 
	 
	 } while ((time_interval_[0] < start_time_) or (time_interval_[1] > stop_time));  
	
	simulation_clock = time_interval_[0];
	
														
	
	Network network(simulation_clock, time_inc);
	
	while(simulation_clock < time_interval_[1]) { //specified here instead of inside the method update so I dont need to give the interval tab
		
		network.update(); 

		simulation_clock += time_inc; 
	}
	
		cout << "The simulation has ended." << endl;
	
}


