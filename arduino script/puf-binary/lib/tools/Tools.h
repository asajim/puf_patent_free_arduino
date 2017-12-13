//
// Created by Ade Setyawan on 10/25/17.
//

#ifndef PUF_TOOLS_H
#define PUF_TOOLS_H

#include "BCH.h"

using namespace std;

class Tools {
public:
    Tools();

    int compareArrays(int a[], int b[], int n);

    int8_t xor_int(int8_t a,int8_t b);

    void xor_array(int8_t a[], int8_t b[], int8_t result[], int size);

    void print_array(int8_t input[], int size, int gap);

    void print_array2(int8_t input[], int size, int gap);

    void initialize_array(int8_t input[], int size, int8_t value);

    int difference_array(int8_t a[], int8_t b[], int size);
};

#endif //PUF_TOOLS_H
