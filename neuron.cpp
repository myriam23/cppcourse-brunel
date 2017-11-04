#include "neuron.hpp"


Neuron::Neuron(std::array<double, 2> temp,  double e, double g,bool type)
: membrane_potential_(0), time_of_spike_(0),
neuron_time_(temp[0]), time_increment_(0.1),
delay_(1.5), refractory_(false), arriving_current(0),
Ring_buffer_(16,0.0)  
{
	eta_ = e;
	excitatory_ = type;
	if(!excitatory_) 
	{ 
		weight_ = -g* 0.1;
	}else{ 
		weight_ = 0.1;}
}

Neuron::Neuron(std::array<double, 2> temp,  double h,  double del, double w,double e,double g, bool type)
: membrane_potential_(0), time_of_spike_(0), refractory_(false), arriving_current(0)
{
	excitatory_ = type;
	neuron_time_ = temp[0];
	eta_ = e;
	time_increment_ = h; 	
	delay_ = del; 
	if(!excitatory_ ) 
	{ 
		weight_ = -g* w;
	}else{ 
		weight_ = w;}
	
	delaySteps = time_to_steps(delay_);	
	Buffer_size = delaySteps + 1; 
	for(unsigned int a = 0; a < Buffer_size; ++a) 
	{ 
		Ring_buffer_.push_back(0);
	}	
} 
Neuron::~Neuron(){} 
/** This update method is called at every step for every neuron of the network.
 * First, it checks the neurone state; buffering or refractory ?
 * If the neuron is buffering, it reads its buffer at the correct index thus taking into consideration
 * all inputs from the network to compute the new membrane potential. Once that is done, the buffer at the current index
 * is reset.
 * Then, the spiking conditon is checked: if the neuron spikes, its time of spike is saved, its potential membrane is 
 * reset, its states turns from buffering to refractory and the clock is incremented. 
 * The method returns the spike condition as true. 
 * If the neurone does not spike, the clock is incremented and the method returns the spike condition as false.S
 * If the neurone is refractory, the condition on the refractory period is checked. If the refractory period since the 
 * last spike has elapsed then the state is changed from refractory to buffering. 
 * Afterwards, the ring buffer at the current time is reset; indeed all inputs received at that instant will not
 * be taking into account as the neuron was in a refractory state. The clock is then incremented and the spiking condition
 * returned as false. 
 * */
bool Neuron::update_state_()
{	
		if (!refractory_) 
		{ 
			membrane_potential_= (exp((-1 * time_increment_/tau_)) * membrane_potential_) + (arriving_current * membrane_resistance_ *(1- exp((-1 * time_increment_/tau_)))) + read_buffer() + 0.1*random_input();  
			reset_buffer();	

			if(membrane_potential_ > spike_potential_) 
			{ 
				refractory_ = true; 
				time_of_spike_ = neuron_time_;
				membrane_potential_ = 0; 
				neuron_time_ += time_increment_;

				return true; 
			}
			neuron_time_ += time_increment_;
			return false;
				
		}else
		{
			if(neuron_time_ - time_of_spike_ > refractory_period_)
			{
				refractory_ = false; 
			} 
			reset_buffer();
			neuron_time_ += time_increment_;
			return false; 
		}
}
/**This return a random number according to the Poisson probability which is initialized with 
 * an average depending on the initialized parameters. 
 * */
double Neuron::random_input() const
{	
	static std::random_device number_random; 
	static std::mt19937 engine(number_random());  
	static int v =  (eta_* spike_potential_)/(weight_ * tau_); 
	static std::poisson_distribution<> poisson(v*time_increment_); 
	int input = poisson(engine);  
	return input;
}


/** This method is called during the update of the neuron. It reads the buffer at the correct index 
 * by converting the current time to the corresponding index. To do so, there is a call to current_index(). 
 * The returned value is the sum of all spikes that arrive at the current time.
 * */
double Neuron::read_buffer()  
{ 
	unsigned int i = current_index();
	assert(i < Buffer_size);
	return Ring_buffer_[i];
} 
/** This method is called when the sources of the neuron spike in the update method of the network. 
 * The argument is the efficiency of the source neuron that has spiked and thus sent its spike to its targets.
 * The stimulation is written in the Ring buffer of the target while taking into account the delay of the spike.
 * */
void Neuron::write_buffer(double w) 
{ 	
	unsigned int index = (current_index() + delaySteps) % (Buffer_size);
	assert(index < Buffer_size);
	Ring_buffer_[index] = Ring_buffer_[index] + w; 		
} 

/**This method is used to test whether or not the writing in the buffer is done correctly. 
 * The difference to write_buffer() is it takes the index in which it must write as argument. 
 * Nonetheless, the computation of the index is done the same way, only outside of the method
 * for practical reasons. 
 * */
void Neuron::write_bufferTest(double g, int i)
{ 
	assert(i < Buffer_size);
	Ring_buffer_[i] += g; 	
}
/** At every time step, the ring buffer must reset its current index to 0.  
 * */
void Neuron::reset_buffer() 
{
	Ring_buffer_[current_index()] = 0.0; 
}
/** Returns the buffer of the neuron while ensuring it is not modified.
 *
 * */
std::vector<double> Neuron::getBuffer() const
{
	return Ring_buffer_; 
}
/** Returns the targets of the neuron while ensuring they are not modified.
 * */
std::vector< int> Neuron::getMyTargets() const
{
	return MyTargets_;
}

/**This method is called only while creating the connections in the Network. 
 * It adds the targets' number/name in the vector. 
 * */
void Neuron::changeMyTargets(unsigned int target_id) 
{
	MyTargets_.push_back(target_id);
}

/** Gives the index of the Ring buffer corresponding to the current time.
 * */
unsigned int Neuron::current_index() 
{ 	
	return time_to_steps(neuron_time_) % (Buffer_size);
}

double Neuron::get_v_m() const
{
	return membrane_potential_; 
} 
double Neuron::getspiketime() const
{
	return time_of_spike_;
}

double Neuron::getweight() const
{
	return weight_; 
}
bool Neuron::Is_it_excitatory() const
{ 
	return excitatory_; 
} 
void Neuron::set_iext(double i) 
{ 
	arriving_current = i; 
}

unsigned int Neuron::time_to_steps(double t) 
{ 
	return static_cast<unsigned long>(std::ceil(t/time_increment_)); 	
}




