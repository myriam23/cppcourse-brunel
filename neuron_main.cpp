#include <array>
#include "neuron.hpp" 
#include <cmath> 
#include <iostream>
#include <vector> 
#include "neuron_excitatory.hpp"

using namespace std; 

int main()
{
	double start_time_(0);
	double stop_time(1000); 
	double time_increment_(10); 
	double simulation_clock(0); 
	double input_current_; 
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
		cout << "b " << b << endl; 
		cout << " intervalle main " << time_interval_[0] << " " << time_interval_[1] << endl;
		} while ((time_interval_[0] < start_time_) or (time_interval_[1] > stop_time));  
	
	simulation_clock = time_interval_[0]; 
	
	/*Neuron sample_; 
	//cout << " intervalle main " << time_interval_[1] << " " << time_interval_[2] << endl; 
	sample_.update_state_(time_interval_, input_current_, time_increment_); 
	sample_.write_in_file(); 
	//cout << "input current " << input_current_ << endl; */
	
	Neuron sample_1(simulation_clock); 
	Neuron sample_2(simulation_clock); 
	
	if(simulation_clock < time_interval_[1]) { 
		sample_1.update_state_(time_increment_, simulation_clock, time_interval_, input_current_); 
		
		sample_1.interact(sample_2); 
		
		sample_2.update_state_(time_increment_, simulation_clock); 
		simulation_clock += time_increment_; 
	}else{ 
		cout << "The simulation has ended." << endl;
	
	
	
}

}
