#include "network.hpp" 
#include "gtest/gtest.h" 
#include <cmath>
#include <array> 

/*!<Allows to test the computation of the potential membrane with an external current and no random input from external connections.*/
TEST(NeuronTest,MembranePotential) 
{ 
	Neuron* neuron = new Neuron(0, 0.1, 1.5, 0.1, 2, 5, true); 
	neuron->set_iext(1.01); 
	neuron->update_state_(); 
	
	EXPECT_EQ(1.01*20*(1-std::exp(-0.1/20.0)), neuron->get_v_m()); 
	delete neuron;
	neuron = nullptr;	
} 

/*!<Checks that neurons have an average of targets of 10% of the population.*/
TEST(ConnectionTest, NumberConnection) 
{
	unsigned int number_connections(0);
	std::array<double, 2> interval = {0, 20};
	std::string file = "NumberConnectionTest.txt"; 
	Network* net = new Network(interval, 0.1, 1.5, 0.1, 20, 80, 2,5, file);
	
	for(auto& element : net->getPopulation_()) 
	{ 
		number_connections += element->getMyTargets().size(); 
	}
	EXPECT_EQ(1000, number_connections); 
	delete net; 
	net = nullptr;
}

/*!<Will make sure that inhibitory and exciatory neurons have a certain efficiency and that each neuron receives 4 times more excitatory inputs than inhibitory ones.*/
TEST(ConnectionTest, TypeConnection) 
{
	unsigned int number_connections(0);						
	std::array<double, 2> interval = {0, 20};
	std::string file = "TypeConnectionTest.txt"; 
	Network* net = new Network(interval, 0.1, 1.5, 0.1, 20, 80, 2,5, file);
	
	static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> roll(0,99);
 
	int random = roll(gen); 
	unsigned int input_ex(0); 
	unsigned int input_in(0);
	for(unsigned int i = 0; i < net->getPop(); ++i)  
	{ 
		std::vector<int> temp = net->getPopulation_()[i]->getMyTargets();
		double w = net->getPopulation_()[i]->getweight(); 
													
		for(unsigned int row = 0; row <temp.size(); ++row) 
		{ 
			unsigned int target = temp[row];  

			if((random == target)&& ( w == -0.5)) { ++input_in; }
			if((random == target)&& (w == 0.1)) { ++input_ex; }
		}
	} 
		EXPECT_EQ(2, input_in); 
		EXPECT_EQ(8, input_ex); 
	
}

/*!<Checks that when a spike occurs, the neuron writes correctly in the buffer of its targets, and the buffers are correctly read and reset.*/
TEST(BufferTest, WriteReadReset) 
{

	Network* net = new Network({0, 20}, 0.1, 1.5, 0.1, 20, 80, 2, 5, "BufferTest.txt");
	Neuron* source = new Neuron(0, 0.1,1.5, 0.1, 2, true, 5);
	Neuron* Ni = new Neuron(0, 0.1,1.5, 0.1, 2, 5, true);

	bool spiking = false; 
	for(unsigned int j = 0; j < net->getPop(); ++j) 
	{
			source = net->getPopulation_()[j];
			source->set_iext(2);
			 
			do{ 
				spiking = source->update_state_(); 
			}while(!spiking);
			
			unsigned int index = (source->getspiketime() + 15)%16; 		
			
			for(unsigned int i = 0; i < source->getMyTargets().size(); ++i) 
			{
				int target_i = source->getMyTargets()[i]; 		
								
				Ni = net->getPopulation_()[target_i]; 
				Ni->set_step(source->getspiketime()); 				
				Ni->write_buffer(source->getweight()); 
				std::vector<double> temp = Ni->getBuffer(); 
				
				ASSERT_EQ(16, temp.size());  
				ASSERT_LE(index, temp.size()); 
				
				Ni->set_step(15); 
				double value = Ni->read_buffer(); 				
				Ni->reset_buffer(); 					
				if(source->Is_it_excitatory()) 
				{ EXPECT_EQ(0.1, value); }else{ EXPECT_EQ(-0.5, value); }; 
				EXPECT_EQ(0, Ni->read_buffer()); 
			}
	}
		delete net; 
		net = nullptr; 
}
/*!<Checks that all parameters change according to the neuron's state.*/
TEST(State, BufferingRefractory) 
{
	Network* net = new Network({0, 20}, 0.1, 1.5, 0.1, 20, 80, 2, 5, "StateTest.txt");
	unsigned int step = 0;
	for(auto& element : net->getPopulation_()) 
	{
		do { 
			element->update_state_(); 
			++step;
		}while(step < 150); 
		if(element->Is_it_refractory()) 
		{ EXPECT_EQ(0, element->get_v_m()); EXPECT_LE(150 - element->getspiketime(), 20) ;}	
		else{ EXPECT_GE(element->get_v_m(), 0); EXPECT_GT(150-element->getspiketime(), 20); }
		
	}
	delete net; 
	net = nullptr; 
}

int main(int argc, char **argv) 
{ 
	::testing::InitGoogleTest(&argc, argv); 
	return RUN_ALL_TESTS(); 

} 
