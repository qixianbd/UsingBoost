/*
 * Utility.h
 *
 *  Created on: 2014年11月3日
 *      Author: qmwx
 */

#ifndef UTILITY_H_
#define UTILITY_H_

/**
 * @Note this return type is long long int.
 * @return return the seconds us seconds that present know.
 */
long long usec(void);

/**
 * get the description of binary bit form of the given number.
 * @param number
 * @return
 */

std::string longToBinaryString(long number);

std::string longToString(long number);

void memSwap(void* a, void* b, size_t length);

void stringConverse(char *str);

int stringCmpIngoreCase(const char* str1, const char* str2);

bool startWithSubString(const std::string& str, const std::string& sub);
bool endWithSubString(const std::string& str, const std::string& sub);

bool isAllDigit(const std::string& str);

#endif /* UTILITY_H_ */
