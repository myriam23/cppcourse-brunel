#include <array>
#include "neuron.hpp" 
#include <cmath> 
#include <iostream>

using namespace std; 

int main()
{
	double start_time_(0);
	double stop_time(1000); 
	double time_increment_(10); 
	double input_current_; 
	array<double,2> time_interval_{0,0}; 
	
	cout << "Welcome to neurone simulation. Please input the current you would like to apply." << endl; 
	cin >> input_current_; 
	
	do { 
		cout << "Which interval, between 0 and 1000ms, would you like to consider ? " << endl; 
		cin >> time_interval_[1]; 
		cin >> time_interval_[2]; 
		
		} while ((time_interval_[1] < start_time_) or (time_interval_[2] > stop_time));  
		
	Neuron sample_; 
	sample_.update_state_(time_interval_, input_current_, time_increment_); 
	
	
}
