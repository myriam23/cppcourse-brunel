#include <array>
#include "neuron.hpp" 
#include <cmath> 
#include <iostream>
#include <vector> 
using namespace std; 

int main()
{
	double start_time_(0);
	double stop_time(1000); 
	double time_increment_(10); 
	double input_current_; 
	vector<double> time_interval_; 
	
	cout << "Welcome to neurone simulation. Please input the current you would like to apply." << endl; 
	cin >> input_current_; 
	
	do { 
		cout << "Which interval, between 0 and 1000ms, would you like to consider ? " << endl; 
		int a; 
		int b; 
		cin >> a;
		cin >> b; 
		time_interval_.push_back(a);
		time_interval_.push_back(b); 
		cout << "b " << b << endl; 
		cout << " intervalle main " << time_interval_[0] << " " << time_interval_[1] << endl;
		} while ((time_interval_[0] < start_time_) or (time_interval_[1] > stop_time));  
		
	Neuron sample_; 
	//cout << " intervalle main " << time_interval_[1] << " " << time_interval_[2] << endl; 
	sample_.update_state_(time_interval_, input_current_, time_increment_); 
	sample_.write_in_file(); 
	//cout << "input current " << input_current_ << endl; 
	
}
