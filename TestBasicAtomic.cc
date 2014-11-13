/*
 * TestBasicAtomic.cc
 *
 *  Created on: 2014年11月13日
 *      Author: keyming
 */

#include <boost/thread.hpp>
#include <iostream>
#include <string>
#include "BasicAtomic.h"



void printing(boost::mutex& mu, BasicAtomic<int> & x, const std::string& str){
	for(int i = 0; i < 30; i++){
		mu.lock();
		std::cerr << str << ++x <<  std::endl;
		mu.unlock();
		boost::this_thread::sleep_for(boost::chrono::milliseconds(2));
	}

}
#ifdef TEST_TESTBASICATOIC
int main()
{
	BasicAtomic<int> x;
	boost::mutex mu;
	boost::thread(printing, ref(mu), boost::ref(x), "hello");
	boost::thread(printing, ref(mu), boost::ref(x), "boost");
	boost::thread(printing, ref(mu), boost::ref(x), "world");
	boost::this_thread::sleep_for(boost::chrono::seconds(2));
}
#endif

