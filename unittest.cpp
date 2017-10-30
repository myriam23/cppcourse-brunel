#include "neuron.hpp" 
#include <iostream> 
#include "gtest/gtest.h" 
#include <cmath>

TEST(NeuronTest,MembranePotential) 
{ 
	/*Neuron neuron(0, 0.1, 1, 1.5, 0.1); 
	neuron.set_i_ext(1.0); 
	neuron.update_state_(); 
	
	EXPECT_EQ(20*(1.0-std::exp(-0.1/20.0)), neuron.get_v_m()); */
	
	
} 



int main(int argc, char **argv) 
{ 
	::testing::InitGoogleTest(&argc, argv); 
	return RUN_ALL_TESTS(); 

} 
