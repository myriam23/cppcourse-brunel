#include "experiment.hpp" 
#include <string> 
#include <iostream>
#include <fstream> 
#include <array>

Experiment::Experiment()
{
	std::string answer = "N"; 
	do {
		std::cout << "Welcome ! Would you like to simulate the 4 experiences simultaneously ? (Y or N)" << std::endl; 
		std::cin >> answer; }while((answer != "Y") && (answer != "N"));
		if(answer == "Y") 
		{ 
			ExperimentA(); 
			ExperimentB(); 
			ExperimentC(); 
			ExperimentD(); 
		}else{ 
			std::cout << "Would you like to simulate an experience with your own parameters ? (Y or N)" << std::endl; 
			std::cin >> answer; 
			if(answer == "Y") 
			{ 
				std::array<double, 2> interval({0,0}); 
			int c(0); 
			int d(0);
			double nu(0); 
			double g(0);
			double h(0); 
			double del(0); 
			double j(0); 
			std::cout << "What is your time interval for the simulation run [ms] ?" << std::endl; 
			std::cin >>interval[0];
			std::cin >> interval[1];
			std::cout<<"How many excitatory neurons do you want in your network ?" << std::endl; 
			std::cin >>c;
			std::cout<<"How many inhibitory neurons do you want in your network ?" << std::endl; 
			std::cin >> d;
			std::cout<<"What is your excitatory neurons efficiency ?" << std::endl; 
			std::cin >> j;
			std::cout<<"What is the ratio between the excitatory neurons' efficiency and the inhibitory's one (J_ex/J_in) ?" << std::endl; 
			std::cin >> g;
			std::cout<<"What is the delay of input of your neurons' spikes ?" << std::endl; 
			std::cin >> del; 
			std::cout << "What is the ratio between the firing rate of the external connections and the threshold firing rate of your network (nu_ext/nu_th) ? " << std::endl; 
			std::cin >> nu;
			std::cout<< "Under which rate would you like to update your network [/ms] ? " << std::endl; 
			std::cin >> h; 
			std::cout<< "Under which name would you like to save your output text file (no space in name) ? " << std::endl; 
			std::cin >> file; 
			h = 1/h; 
			Network* Net1 = new Network(interval, h, del, j, d, c, nu, g, file); 
			Net1->update();
		}else{
			std::cout << "Which experience would you like to simulate (A or B or C or D) ?" << std::endl; 
			std::cin >> answer; 
			if(answer == "A") { ExperimentA(); }
			if(answer == "B") { ExperimentB(); }
			if(answer == "C") { ExperimentC(); }
			if(answer == "D") { ExperimentD(); }
			
		}	
	}
}
Experiment::~Experiment(){}

/** Figure A will have a ratio between the firing rate of the external connections and the threshold firing rate of the network of 2 
 * and a ratio between the excitatory neurons' efficiency and the inhibitory's one of 3. **/ 
void Experiment::ExperimentA()
{
	file = "FigureA.txt";
	std::array<double, 2> time = {0, 1000};
	Network* Net1 = new Network(time, 2.0, 3.0, file); 
	Net1->update(); 
	
	delete Net1; 
	Net1 = nullptr; 
}

/** Figure B will have a ratio between the firing rate of the external connections and the threshold firing rate of the network of 4
 * and a ratio between the excitatory neurons' efficiency and the inhibitory's one of 6. **/ 
void Experiment::ExperimentB()
{
	file = "FigureB.txt";
	std::array<double, 2> time = {0, 1000};
	Network* Net1 = new Network(time, 4, 6, file); 
	
	Net1->update(); 
	
	delete Net1; 
	Net1 = nullptr; 
}

/** Figure C will have a ratio between the firing rate of the external connections and the threshold firing rate of the network of 2 
 * and a ratio between the excitatory neurons' efficiency and the inhibitory's one of 5. **/ 
void Experiment::ExperimentC()
{
	file = "FigureC.txt"; 
	std::array<double, 2> time = {0, 1000};
	Network* Net1 = new Network(time, 2, 5, file); 
	Net1->update(); 
	
	delete Net1; 
	Net1 = nullptr;
}

/** Figure D will have a ratio between the firing rate of the external connections and the threshold firing rate of the network of 0.9 
 * and a ratio between the excitatory neurons' efficiency and the inhibitory's one of 4.5. **/ 
void Experiment::ExperimentD()
{
		
	file = "FigureD.txt";
	std::array<double, 2> time = {0, 1000};
	Network* Net1 = new Network(time, 0.9, 4.5, file); 
	Net1->update(); 
	
	delete Net1; 
	Net1 = nullptr; 
}
