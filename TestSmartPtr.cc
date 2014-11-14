/*
 * SmartPtr.cc
 *
 *  Created on: 2014年11月11日
 *      Author: qmwx
 */
#include <boost/smart_ptr.hpp>
#include <iostream>
#include "Random.h"
#include "Utility.h"

int testSharedArray(){
	typedef long long llong;
	llong start, end;
	start = myutility::usec();
	const int ARRAYSIZE = 100*1024;
	boost::shared_array<int> sa(new int[ARRAYSIZE]);
	end = myutility::usec();
	std::cerr << "Initialize the scoped_array take time " << end- start << std::endl;

	Random r;
	start = myutility::usec();
	boost::shared_array<int> sb( r.generateUniqueIntArray(0, ARRAYSIZE));
	end = myutility::usec();
	std::cerr << "Generate  the scoped_array take time " << end- start << std::endl;
	for(int i = 0; i < ARRAYSIZE;i++){
		std::cerr << sb[i] << std::endl;
	}
	std::cerr << sb.use_count() << std::endl;
	std::cerr << sa.use_count() << std::endl;
	return 0;
}

int testSharedPtr(){
	boost::shared_ptr<int>  sp(new int);
	return 0;
}

#ifdef TEST_SMARTPTR
int main()
{
	testSharedArray();
	testSharedPtr();
}
#endif

