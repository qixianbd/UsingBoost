/*
 * TestRandom.cc
 *
 *  Created on: 2014年11月10日
 *      Author: qmwx
 */
#include <boost/random.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <iostream>
#include <boost/random.hpp>
#include <boost/shared_array.hpp>
#include <algorithm>
#include <iterator>
using namespace std;
using namespace boost;

class Person{
		std::string key;
		std::string personName;
	public:
		Person():key("1234"), personName("wqm"){

		}
		Person(const std::string& id, const std::string& name): key(id), personName(name){

		}
		~Person(){
			cerr << "delete the object. " << endl;
		}
		std::string getKey()const{
			return key;
		}
		friend std::ostream& operator<<(std::ostream& os, const Person& p);
};
std::ostream& operator<<(std::ostream& os, const Person& p){
	os << p.key << "\t" << p.personName << "\t";
	return os;
}

void func(){
	for(int i = 0; i < 20; i++){
		scoped_ptr<Person> p(new Person);
		cerr << p->getKey() << "\n";
	}
}


int main ( )
  {
  uniform_int<> distribution(1, 10) ;
  mt19937 engine ;
  variate_generator<mt19937, uniform_int<> > myrandom (engine, distribution);

  for (int i=0; i<10; ++i)
    cout << myrandom() << endl;

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


copy(&aptr[0], &aptr[10], ostream_iterator<int>(cerr, "\t"));

cerr << "\ncount = " << p.use_count() << endl;

func();
  return 0;
  }


