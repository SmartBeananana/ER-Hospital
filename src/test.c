/**
 * @file test.c
 * @author Xiangyuan Lian
 * @date July 2018
 * @brief File containing implementation of unit testing
 */
#include <stdio.h>
#include <stdlib.h>
#include "test.h"

int printPassFail(const int result)
{
    if (result)
    {
        printf("Testing passed.\n\n");
        return result;
    }

    printf("Testing failed.\n\n");

    return result;
}

void printTestInfo(int testNum, char *testInfo)
{
    printf("Test Number: %d\n", testNum);
    printf("Testing infomation: %s\n ", testInfo);
}
