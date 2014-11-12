/*
 * TestPool.cc
 *
 *  Created on: 2014年11月10日
 *      Author: qmwx
 */

#include <iostream>
#include <boost/pool/object_pool.hpp>
#include "Person.h"
using namespace std;
using namespace boost;


#include <iostream>
#include <boost/filesystem.hpp>
using namespace boost::filesystem;

#ifdef TEST_POOL
int main(int argc, char* argv[])
{
  path p (argv[1]);   // p reads clearer than argv[1] in the following code

  try
  {
    if (exists(p))    // does p actually exist?
    {
      if (is_regular_file(p))        // is p a regular file?
        cout << p << " size is " << file_size(p) << '\n';

      else if (is_directory(p))      // is p a directory?
      {
        cout << p << " is a directory containing:\n";

        typedef vector<path> vec;             // store paths,
        vec v;                                // so we can sort them later


      copy(directory_iterator(p), directory_iterator(), back_inserter(v));

        sort(v.begin(), v.end());             // sort, since directory iteration
                                              // is not ordered on some file systems

        for (vec::const_iterator it (v.begin()); it != v.end(); ++it)
        {
          cout << "   " << it->filename() << '\n';
        }
      }

      else
        cout << p << " exists, but is neither a regular file nor a directory\n";
    }
    else
      cout << p << " does not exist\n";
  }

  catch (const filesystem_error& ex)
  {
    cout << ex.what() << '\n';
  }

  return 0;
}



int objectSize()
{

	cerr << "sizeof int = " << sizeof(int) << endl;
	cerr << "sizeof long = " << sizeof(long) << endl;
	cerr << "sizeof double = " << sizeof(double) << endl;
	cerr << "sizeof float = " << sizeof(float) << endl;
	cerr << "sizeof point=" << sizeof(int*) << endl;
	cerr << "sizeof char= " << sizeof(char) << endl;
	cerr << "sizeof bool = " << sizeof(bool) << endl;
	return 0;
}

int test1()
{
	object_pool<Person> pl;
	for(int i = 0; i < 1024; i++){
		pl.malloc();

	}

	cerr << "endl";
}
#endif

