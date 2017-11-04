#include "network.hpp" 
#include "gtest/gtest.h" 
#include <cmath>
#include <array> 

/*
TEST(NeuronTest,MembranePotential) 
{ 
	std::array<double, 2> interval = {0, 20};
	Neuron* neuron = new Neuron(interval, 0.1, 1.5, 0.1, 2, 5, true); 
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

TEST(ConnectionTest, typeConnection) 
{
	unsigned int number_connections(0);						
	std::array<double, 2> interval = {0, 20};
	Network* net = new Network(interval, 0.1, 1.5, 0.1, 20, 80, 2,5);
	double random = net->roll(0,99); 
	unsigned int input_ex(0); 
	unsigned int input_in(0);
	for(unsigned int i = 0; i < net->getPop(); ++i)  
	{ 
		std::vector<int> temp = net->getPopulation_()[i]->getMyTargets(); //targets of the source 
		double w = net->getPopulation_()[i]->getweight(); //type of the source 
														//should be positive for i < 80 then negative 
		for(unsigned int row = 0; row <temp.size(); ++row) 
		{ 
			unsigned int target = temp[row];  //name of the targets of the source 

			if((random == target)&& ( w == -0.5)) { ++input_in; } //if the source tarhets the random neurone chosen && the source isinhibitory then add that to the sum of inhibitory sources targeting random 
			if((random == target)&& (w == 0.1)) { ++input_ex; }
		}
	} 
		EXPECT_EQ(2, input_in); 
		EXPECT_EQ(8, input_ex); 
	
}

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
		
		unsigned int index = (t_spike + 15)%16; 		

		int target_one = N->getMyTargets()[0]; 		
		Neuron* N2 = new Neuron(interval, 0.1,1.5, 0.1, 2, true, 5);
		N2 = net->getPopulation_()[target_one]; 
		N2->write_bufferTest(N->getweight(), index); 
		std::vector<double> temp = N2->getBuffer(); 
		
		ASSERT_EQ(16, temp.size()); 
		ASSERT_EQ(16, temp.size()); 
		ASSERT_EQ(16, temp.size()); 
		ASSERT_LE(index, temp.size()); 
		double value = temp[index]; 
		EXPECT_EQ(0.1, value); 
	
		delete net; 
		net = nullptr; 
}

int main(int argc, char **argv) 
{ 
	::testing::InitGoogleTest(&argc, argv); 
	return RUN_ALL_TESTS(); 

} 
