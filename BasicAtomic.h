/*
 * BasicAtomic.h
 *
 *  Created on: 2014年11月13日
 *      Author: keyming
 */

#ifndef BASICATOMIC_H_
#define BASICATOMIC_H_

#include <boost/utility.hpp>
#include <boost/noncopyable.hpp>
#include <boost/thread.hpp>

template<typename T>
class BasicAtomic : boost::noncopyable
{
private:
	T n;
	typedef boost::mutex mutex_t;
	mutex_t mu;
public:
	BasicAtomic(T x = T()): n(x){

	}
	T operator++(){
		mutex_t::scoped_lock  lock(mu);
		return ++n;
	}
	operator T (){
		mutex_t::scoped_lock lock(mu);
		return n;
	}
};




#endif /* BASICATOMIC_H_ */
