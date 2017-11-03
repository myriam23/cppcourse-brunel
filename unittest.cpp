#include "network.hpp" 
#include <iostream> 
#include "gtest/gtest.h" 
#include <cmath>
#include <array> 

/*
TEST(NeuronTest,MembranePotential) 
{ 
	std::array<double, 2> interval = {0, 20};
	Neuron* neuron = new Neuron(interval, 0.1,1.5, 0.1, 2, true, 5); 
	neuron->set_iext(1); 
	neuron->update_state_(); 
	
	EXPECT_EQ(20*(1-std::exp(-0.1/20.0)), neuron->get_v_m()); 
	delete neuron;
	neuron = nullptr;
		
} */

TEST(ConnectionTest, numberConnection) 
{
	unsigned int number_connections(0);
	std::array<double, 2> interval = {0, 20};
	Network* net = new Network(interval, 0.1, 1.5, 0.1, 20, 80, 2,5);
	
	for(auto& element : net->getPopulation_()) 
	{ 
		number_connections += element->getMyTargets().size(); 
	}
	EXPECT_EQ(1000, number_connections); 
	delete net; 
	net = nullptr;
}

/*
TEST(BufferTest, writeBuffer) 
{
	
	std::array<double, 2> interval = {0, 20};
	Network* net = new Network(interval, 0.1, 1.5, 0.1, 20, 80, 2, 5);
	Neuron* N = new Neuron(interval, 0.1,1.5, 0.1, 2, true, 5);
	N = net->getPopulation_()[0];
	N->set_iext(2);
	bool spiking = false; 
	do{ 
		spiking = N->update_state_(); 
	}while(!spiking);
	
		unsigned int t_spike = N->time_to_steps(N->getspiketime());
		std::cout << "temps spike " << t_spike << std::endl; 
		
		unsigned int index = (t_spike + 15)%16; 		
		std::cout << "index " << index << std::endl; 

		int target_one = N->getMyTargets()[0]; 		
		std::cout << "target" << target_one << std::endl; 
		Neuron* N2 = new Neuron(interval, 0.1,1.5, 0.1, 2, true);
		N2 = net->getPopulation_()[target_one]; 
		N2->write_bufferTest(N->getweight(), index); 
		std::cout << "wrote in buffer" << std::endl;
		std::vector<double> temp = N2->getBuffer(); 
		
		ASSERT_EQ(16, temp.size()); 
		double value = temp[index];
		std::cout << value << std::endl;
		bool type = N->Is_it_excitatory(); 
		EXPECT_EQ(0.1, value); 
	
	delete N; 
	N = nullptr; 
	delete N2; 
	N2 = nullptr;
	delete net; 
	net = nullptr; 
	
}*/

int main(int argc, char **argv) 
{ 
	::testing::InitGoogleTest(&argc, argv); 
	return RUN_ALL_TESTS(); 

} 
