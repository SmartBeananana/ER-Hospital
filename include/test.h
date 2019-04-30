/**
 * @file test.h
 * @author Xiangyuan Lian
 * @date July 2018
 * @brief File containing the function definitions of unit testing
 */

#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdlib.h>

/**Function for testing the implementation function of doubly linked list
 *@return a integer '0' means test failed and '1' means test passed
 *@param result a constant integer to evaluate the implementation function of doubly linked list
**/
int printPassFail(const int result);

/**Function for providing the number of the test and the information of the implementation Function
 *@param testNum a integer that represent the number of the test
 *@param testInfo a pointer point to the introduction of the function that will be tested
**/
void printTestInfo(int testNum, char *testInfo);

#endif
