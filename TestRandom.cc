/*
 * TestRandom.cc
 *
 *  Created on: 2014年11月10日
 *      Author: qmwx
 */
#include <boost/random.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/scoped_array.hpp>
#include <iostream>
#include <boost/random.hpp>
#include <boost/shared_array.hpp>
#include <algorithm>
#include <iterator>
#include "Person.h"
using namespace std;
using namespace boost;


void func(){
	for(int i = 0; i < 20; i++){
		scoped_ptr<Person> p(new Person);
		//cerr << p->getKey() << "\n";
	}
	int *ap = new int [20];
	scoped_array<int> sa(ap);
	for(int i = 0; i < 20; i++){
		sa[i] = i*5;
	}
	for(int i = 0; i < 20; i++){
		cerr << sa[i] << "\t";
	}
	cerr << "\n";
}


#ifdef TEST_RANDOM
int main ( )
  {
  uniform_int<> distribution(1, 10) ;
  mt19937 engine ;
  variate_generator<mt19937, uniform_int<> > myrandom (engine, distribution);

  for (int i=0; i<10; ++i)
    cerr << myrandom() << endl;

  shared_ptr<Person> ptr(new Person());
  cerr << "key = "  << ptr->getKey() << endl;
  cerr << ptr.use_count() << endl;
  shared_ptr<Person> my = ptr;
 cerr << "key = " <<  my->getKey() << endl;
  cerr << ptr.use_count() << endl;
  for(int i = 0; i < 10; i++){
	  std::cerr << i << " \t" ;
  }
  std::cerr << endl;

  shared_array<int> aptr(new int[10]);
  shared_array<int>  p = aptr;
for(int i = 0; i < 10; i++){
	aptr[i] = i*3;
}


copy(aptr.get(), aptr.get() + 10,  ostream_iterator<int>(cerr, "\t"));

cerr << "\ncount = " << p.use_count() << endl;

func();
  return 0;
  }
#endif

