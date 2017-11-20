//
// Created by ade on 9-11-17.
//

#ifndef SERIALSERVER_TOOLS_H
#define SERIALSERVER_TOOLS_H

#include <iostream>
#include <sstream>
#include <bitset>
#include <string>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Tools {
public:
    Tools();

    std::string hex_str_to_bin_str(const std::string& hex);

    std::string hex_char_to_bin(char c);

    int compareArrays(int a[], int b[], int n);

    int xor_int(int a,int b);

    int *xor_array(int a[], int b[], int size);

    void print_array(int input[], int size);

    void initialize_array(int input[], int size, int value);

    int difference_array(int a[], int b[], int size);

    int *readFile(std::string address, int count);

    int* convertStringToIntArray(string input, int length);

    void saveToFile(int* input, int length, string filename);

    void saveToFile(string input, int length, string filename);

    int *readFileSimple(string address, int count);

    void printBits(size_t const size, void const * const ptr);
};


#endif //SERIALSERVER_TOOLS_H
