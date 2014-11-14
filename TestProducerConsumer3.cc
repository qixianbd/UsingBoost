/*
 * TestProducerConsumer3.cc
 *
 *  Created on: 2014年11月13日
 *      Author: keyming
 */
#include <iostream>
#include <boost/thread.hpp>
#include <boost/algorithm/string.hpp>
#include "HashTable.h"
#include "Person.h"
#include "Random.h"
#include "Utility.h"
using namespace boost;
typedef long long llong ;



void insertData(HashTable<Person> & ht){
	Random r;
	for(int i = 0; i < 20*1024; i++){
		std::string st = r.getFixLengthString(13);
		std::string upst = r.getPhoneNum(11);
		Person p(st, upst);
		ht.put(p.getKey(), p);
	}

}

void deleteData(HashTable<Person> & ht){
	Random r;
	for(int i = 0; i < 10*100; i++){
		std::string st = r.getFixLengthString(13);
		std::string upst = r.getPhoneNum(11);
		Person p(st, upst);
		ht.deleteElement(p.getKey(), p);
	}
}


#ifdef TEST_PRODUCERCONSUMER_3
int main()
{
	HashTable<Person> personHt;

	for(int i = 0; i < 20; i++){
		thread(insertData, ref(personHt));
	}
	thread(deleteData, ref(personHt));
	this_thread::sleep_for(chrono::seconds(120));
	personHt.print(std::cerr);
	std::cerr << "***************This is  The End **********" << std::endl;
	return 0;
}
#endif

