#include <array>
#include "neuron.hpp" 
#include <cmath> 
#include <iostream>
#include <vector> 
#include "network.hpp"
#include <string> 
using namespace std; 


int main()
{
	
	double time_inc(0.1); 
	array< double, 2> time_interval_; 
	double wei(0); 
	 double del(0); 
	 double et(0);
	 double g(0);
	string ans = "yes"; 
	
	cout << "Welcome to neurone simulation. Would you like to choose your own parameters instead of the default ones ? " << endl;
	cin>> ans; 
	
	if(ans == "yes") 
	{ 
		cout << "What are the delay and weight your neurons ? " << endl; 
		cin >> del; 
		cin >> wei;
		cout << "What is your ratio (v_ext/v_th) and g your neurons ? " << endl; 
		cin >> et;
		cin >> g;
		int c; 
		int d;
		
			cout << "How long do you want your simulation to run in [ms] (Note: no more than 1000 ms) ? " << endl;  
			double a; 
			cin >>a;
			double b; 
			cin >> b; 
			time_interval_[0] = a; 
			time_interval_[1] = b; 
			cout<<"How many excitatory neurons do you want in your network ?" << endl; 
			cin >>c;
			cout<<"How many inhibitory neurons do you want in your network ?" << endl; 
			cin >> d;
			
										
			Network* network = new Network(time_interval_, time_inc, del, wei, d, c, et, g );
			
			network->update(); 
			
		} else { 
			cout << "Simulating default network. " << endl;
			cout << "What is you time interval ?" << endl; 
			int a; 
			cin >> a; 
			int b; 
			cin >> b;
			 
			cout << "What is your ratio (v_ext/v_th) and g your neurons ? " << endl; 
			cin >> et;
			cin >> g;
			time_interval_[0] = a; 
			time_interval_[1] = b; 
			Network* network = new Network(time_interval_, et, g); 
		}  
	
	cout << "The simulation has ended." << endl;
	
}


