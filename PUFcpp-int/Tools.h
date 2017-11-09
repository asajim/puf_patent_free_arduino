//
// Created by Ade Setyawan on 10/25/17.
//

#ifndef PUF_TOOLS_H
#define PUF_TOOLS_H

#include "BCH.h"
#include <string>
#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <cinttypes>

using namespace std;

class Tools {
public:
    Tools();

    int compareArrays(int a[], int b[], int n);

    int xor_int(int a,int b);

    int *xor_array(int a[], int b[], int size);

    void print_array(int input[], int size);

    void initialize_array(int input[], int size, int value);

    int difference_array(int a[], int b[], int size);

    int *readFile(string address, int count);
};

#endif //PUF_TOOLS_H
