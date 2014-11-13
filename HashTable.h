/*
 * HashTable.h
 *
 *  Created on: 2014年11月4日
 *      Author: qmwx
 */

#ifndef HASHTABLE_H_
#define HASHTABLE_H_
#include <string>
#include <list>
#include <vector>
#include <iostream>
#include <algorithm>
#include <boost/thread.hpp>
#include "stdexcept"
#include "assert.h"

template<typename T>
class HashTable{
private:
	typedef boost::mutex mutex_t;
	typedef boost::shared_mutex shared_mutex_t;
	enum{INIT_SIZE = 4099};
	struct HashBucket{
		std::list<T>* basePtr;
		size_t listLength;
		mutex_t mu;
	};

public:
	HashTable();
	void put(const std::string& key, const T& element);
	T get(const std::string& key);
	void deleteElement(const std::string& key, const T& element);
	bool contains(const std::string& key);
	~HashTable();
	void print(std::ostream& os = std::cout)const;
private:
	HashTable(const HashTable& ht);
	HashTable operator=(const HashTable& ht);

	unsigned long hashFunction(const std::string& key);
	unsigned long hashFunc(const std::string& key, size_t hashSize);

	void insert(HashBucket* bucket, size_t hashSize, const std::string& key, const T& element);
	double calculateBalanceFactor();
	void rehash();
	void finalize();


	static unsigned int rehashCount;
	unsigned long size;
	unsigned long capility;
	double balanceFactor;
	mutable shared_mutex_t smu;

	HashBucket* bucketPtr;
};

template<typename T>
unsigned int HashTable<T>::rehashCount = 0;

template<typename T>
HashTable<T>::HashTable(): size(INIT_SIZE), capility(0), balanceFactor(0), bucketPtr(NULL){
	bucketPtr = new HashBucket [size];
	for(size_t i = 0; i < size; i++){
		bucketPtr[i].basePtr = NULL;
		bucketPtr->listLength = 0;
	}
}

template<typename T>
void HashTable<T>::put(const std::string& key, const T& element) {
	smu.lock_shared();
	insert(bucketPtr, size, key, element);
	++capility;
	smu.unlock_shared();
	if(calculateBalanceFactor() > 5){
		rehash();
	}

}

template<typename T>
T HashTable<T>::get(const std::string& key) {
	unsigned long keyIndex = hashFunction(key);
	std::list<T>* listPtr = bucketPtr[keyIndex].basePtr;
	if(NULL == listPtr){
		throw std::runtime_error("Not contains key in the table.");
	}
	std::list<T>* pl = listPtr;
	typename std::list<T>::const_iterator it;
	for(it = pl->begin(); it != pl->end(); it++){
		if(it->getKey() == key){
			return *it;
		}
	}
	assert(0);
	return T();
}

template<typename T>
bool HashTable<T>::contains(const std::string& key) {
	unsigned long keyIndex = hashFunction(key);
	std::list<T>* listPtr = bucketPtr[keyIndex].basePtr;
	if(NULL == listPtr){
		return false;
	}
	std::list<T>* pl = listPtr;
	typename std::list<T>::const_iterator it;
	for(it = pl->begin(); it != pl->end(); it++){
		if(it->getKey() == key){
			return true;
		}
	}
	return false;
}

template<typename T>
double HashTable<T>::calculateBalanceFactor(){
	 balanceFactor = capility /(double) size;
	 return balanceFactor;
}

template<typename T>
void HashTable<T>::rehash() {
	smu.lock();
	size_t newSize = size*2;
	HashBucket* newBucketPtr = new HashBucket [newSize];
	for(size_t i = 0; i < newSize; i++){
		newBucketPtr[i].basePtr = NULL;
		newBucketPtr[i].listLength = 0;
	}

	for(size_t i = 0; i < size; i++){
		std::list<T>* pl = newBucketPtr[i].basePtr;
		if(NULL == pl){
			continue;
		}
		typename std::list<T>::const_iterator it;
		for(it = pl->begin(); it != pl->end(); it++){
			T t = *it;
			insert(newBucketPtr, newSize, t.getKey(), t);
		}
	}
	finalize();
	bucketPtr = newBucketPtr;
	size = newSize;
	calculateBalanceFactor();
	rehashCount++;
	smu.unlock();
}


template<typename T>
unsigned long HashTable<T>::hashFunc(const std::string& key, size_t hashSize){
	int hashVal = 0;
	int len = key.length();
	for(int i = 0; i < len; i++){
		hashVal = 37*hashVal + key[i];
	}
	hashVal %= hashSize;
	if(hashVal < 0){
		hashVal += hashSize;
	}
	return hashVal;
}

template<typename T>
unsigned long HashTable<T>::hashFunction(const std::string& key) {
	return hashFunc(key, size);
}

template<typename T>
void HashTable<T>::print(std::ostream& os)const{
	smu.lock();
	std::vector<unsigned int> hashChainLengthList;
	for(size_t i = 0; i < size; i++){
		hashChainLengthList.push_back(bucketPtr[i].listLength);
		std::list<T>* listPtr = bucketPtr[i].basePtr;
		std::list<T>* pl = listPtr;
		if(NULL == pl){
			continue;
		}
		typename std::list<T>::const_iterator it;
		for(it = pl->begin(); it != pl->end(); it++){
			os << (*it) << "\n";
		}
	}
	os << "size = " << size << std::endl;
	os << "capbility = " << capility << std::endl;
	os << "banlanceFactor = " << balanceFactor << std::endl;
	os << "rehashCount = " << rehashCount << std::endl;

	std::sort(hashChainLengthList.begin(), hashChainLengthList.end(), std::greater<unsigned int>());
	for(int i = 0; i < 50;i++){
		os << hashChainLengthList[i] << std::endl;
	}
	smu.unlock();
}

template<typename T>
inline void HashTable<T>::insert(HashTable<T>::HashBucket* bucketBase, size_t hashSize, const std::string& key,
		const T& element) {
	unsigned long keyIndex = hashFunc(key, hashSize);
	(bucketBase[keyIndex]).mu.lock();
	std::list<T>* &base = (bucketBase[keyIndex]).basePtr;

	if(NULL == base ){
		base = new std::list<T>();
		(bucketBase[keyIndex]).listLength = 0;
	}
	base->push_back(element);
	bucketBase[keyIndex].listLength++;
	(bucketBase[keyIndex]).mu.unlock();
	return ;
}

template<typename T>
inline void HashTable<T>::deleteElement(const std::string& key,
		const T& element) {
	unsigned long keyIndex = hashFunc(key, size);
	smu.lock_shared();
	(bucketPtr[keyIndex]).mu.lock();
	std::list<T>*& base = (bucketPtr[keyIndex]).basePtr;
	if(NULL == base){
		(bucketPtr[keyIndex]).mu.unlock();
		smu.unlock_shared();
		return ;
	}
	base->remove(element);
	(bucketPtr[keyIndex]).listLength--;
	if((bucketPtr[keyIndex]).listLength <= 0){
		delete base;
		base = NULL;
	}
	(bucketPtr[keyIndex]).mu.unlock();
	smu.unlock_shared();
	return ;
}

template<typename T>
void HashTable<T>::finalize(){
	for(size_t i = 0; i < size; i++){
		delete bucketPtr[i].basePtr;
	}
	delete[] bucketPtr;
}

template<typename T>
HashTable<T>::~HashTable(){
	finalize();
}

#endif /* HASHTABLE_H_ */
