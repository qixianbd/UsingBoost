/*
 * TestProducerConsumer.cc
 *
 *  Created on: 2014年11月13日
 *      Author: keyming
 */

#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include "Random.h"
using namespace boost;

const int BUFFER_SIZE = 32;


char *end = NULL;
void produceFunc(boost::mutex& mu, char* buf){
	Random r;
	while(1){
		mu.lock();
		int used = end - buf;
			int left  = BUFFER_SIZE - used;
			if(left > 0){
				int num = r.nextInt(0, BUFFER_SIZE*2);
				int appendSize = (num <= left ? num : left);

				char *p = end;
				std::cerr << "produce string:" << "\t";
				for(int i = 0; i < appendSize; i++){
					*p= r.nextInt('a', 'z' +1);
					std::cerr << *p;
					p++;
					end++;
				}
				std::cerr << "\n";
				mu.unlock();
				boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
			}
			else{
				std::cerr << "The buffer have already full" << std::endl;
				mu.unlock();
				boost::this_thread::sleep_for(boost::chrono::milliseconds(200));
			}
	}



}

void consumeFunc(boost::mutex& mu, char* buf){
	Random r;

	while(1){
		mu.lock();
		int used = end - buf;
		if(used > 0){
			int num = r.nextInt(0, BUFFER_SIZE*2);
			int consumeSize = (num <= used ? num : used);

			std::cerr << "consuming  string:" << "\t";
			char *p = end-1;
			for(int i = 0; i < consumeSize; i++){
				std::cerr << *p--;
				end--;
			}
			std::cerr << "\n";
			mu.unlock();
			boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
		}
		else{
			std::cerr << "The buffer have is empty." << std::endl;
			mu.unlock();
			boost::this_thread::sleep_for(boost::chrono::milliseconds(200));
		}

	}
}


int main()
{

	char buffer[BUFFER_SIZE];
	strncpy(buffer, "threadtesting", strlen("threadtesting"));
	end  = buffer;
	//end +=  strlen("threadtesting");
	boost::mutex mu;
	boost::thread(produceFunc, ref(mu), buffer);
	boost::thread(consumeFunc, ref(mu), buffer);
	sleep(1000);
	return 0;
}



