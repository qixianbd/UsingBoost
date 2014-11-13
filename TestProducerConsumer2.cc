/*
 * TestProducerConsumer2.cc
 *
 *  Created on: 2014年11月13日
 *      Author: keyming
 */

/*
 * TestProducerConsumer.cc
 *
 *  Created on: 2014年11月13日
 *      Author: keyming
 */

#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/algorithm/string.hpp>
#include <queue>
#include <string>
#include "Random.h"
using namespace boost;
using namespace std;


void produceFunc(boost::mutex& mu, std::queue<std::string> *strVec){
	std::string str;
	std:: cerr << "put into a low case string:" << std::endl;
	while(1){
		std::cin >> str;
		mu.lock();
		strVec->push(str);
		mu.unlock();
		boost::this_thread::sleep_for(boost::chrono::milliseconds(50));
	}
}

void consumeFunc(boost::mutex& mu, std::queue<std::string> *strVec){
	std::string str;
	while(1){
		mu.lock();
		if(!strVec->empty()){
			str = strVec->front();
			strVec->pop();
			mu.unlock();
			std:: cerr << "Your input string is :" << std::endl;
			std::cerr << to_upper_copy(str) << std::endl;
			boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
		}
		else{
			mu.unlock();
			//std:: cerr << "The queue is empty. " << std::endl;
			boost::this_thread::sleep_for(boost::chrono::milliseconds(200));
		}
	}

	return ;
}


int main()
{

	std::queue<std::string> strVec;
	boost::mutex mu;
	boost::thread(produceFunc, ref(mu), &strVec);
	boost::thread(consumeFunc, ref(mu), &strVec);
	sleep(1000);
	return 0;
}






