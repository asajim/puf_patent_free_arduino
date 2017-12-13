//
// Created by Ade Setyawan on 10/25/17.
//
#include "Tools.h"

Tools::Tools() {}

int Tools::compareArrays(int a[], int b[], int n) {
    int ii;
    for (ii = 0; ii < n; ii++) {
        if (a[ii] != b[ii]) {
            printf("index %d", ii);
            return 0;
        }
    }
    return 1;
}

int8_t Tools::xor_int(int8_t a, int8_t b) {
    return a == b ? 0 : 1;
}

void Tools::xor_array(int8_t a[], int8_t b[], int8_t result[], int size) {
    for (int i = 0; i < size; i++) {
        result[i] = xor_int(a[i], b[i]);
    }
}

void Tools::print_array(int8_t input[], int size, int gap) {
    for (int i = 0; i < size; i++) {
        Serial.print(input[i]);
        if (i != 0 && (i + 1) % gap == 0)
            Serial.print(" ");
    }
    Serial.println();
    Serial.flush();
}

void Tools::print_array2(int8_t input[], int size, int gap) {
    for (int i = 0; i < size; i++) {
        Serial.print(input[i]);
        if (i != 0 && (i + 1) % gap == 0)
            Serial.println();
    }
    Serial.println();
    Serial.flush();
}

void Tools::initialize_array(int8_t input[], int size, int8_t value) {
    for (int i = 0; i < size; i++) {
        input[i] = value;
    }
}

int Tools::difference_array(int8_t a[], int8_t b[], int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (a[i] != b[i]) {
            count++;
        }
    }
    return count;
}

void Tools::inverse_bit(int8_t* input){
    if (*input == 0) {
        *input = 1;
    } else {
        *input = 0;
    }
}

void Tools::inverse_array(int8_t* input, int8_t* index, int8_t length){
    for(int8_t i=0;i<length;i++){
        inverse_bit(&input[index[i]]);
    }
}

void Tools::print(String s){
  Serial.print(s);
  Serial.flush();
}

void Tools::println(String s){
  Serial.println(s);
  Serial.flush();
}
