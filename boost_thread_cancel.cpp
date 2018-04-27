#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <unistd.h>

void boost_thread(int a)
{
	int tmp = a;
	while(true)
	{
		boost::this_thread::disable_interruption di;
		{
			boost::this_thread::restore_interruption ri(di);
			std::cout<<"------------------"<<std::endl;
			std::cout<<"a:"<<tmp<<std::endl;
			std::cout<<"++++++++++++++++++"<<std::endl;
			tmp++;
			boost::this_thread::interruption_point();			
		}

	}
}


int main(void)
{
	std::cout<<"haha"<<std::endl;
	boost::thread thread(&boost_thread,1);
	sleep(1);

	//std::cout<<"lalala"<<std::endl;
	thread.interrupt();
	thread.join();
	return 0;
}