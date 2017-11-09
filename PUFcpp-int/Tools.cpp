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
        // better:
        // if(fabs(a[ii]-b[ii]) < 1e-10 * (fabs(a[ii]) + fabs(b[ii]))) {
        // with the appropriate tolerance
    }
    return 1;
}

int Tools::xor_int(int a, int b) {
    return a == b ? 0 : 1;
}

int *Tools::xor_array(int a[], int b[], int size) {
    int *result = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        result[i] = xor_int(a[i], b[i]);
    }
    return result;
}

void Tools::print_array(int input[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d", input[i]);
        if (i != 0 && (i + 1) % 50 == 0)
            printf("\n");
    }
    printf("\n");
}

void Tools::initialize_array(int input[], int size, int value) {
    for (int i = 0; i < size; i++) {
        input[i] = value;
    }
}

int Tools::difference_array(int a[], int b[], int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (a[i] != b[i]) {
            count++;
        }
    }
    return count;
}

int *Tools::readFile(string address, int count) {
    FILE *myFile;
    myFile = fopen(address.c_str(), "r");

    int *numberArray = (int*)malloc(sizeof(int) * count);
    int i;

    if (myFile == NULL) {
        printf("Error Reading File\n");
        exit(0);
    }

    for (i = 0; i < count; i++)
        fscanf(myFile, "%u ", &numberArray[i]);

    fclose(myFile);
    return numberArray;
}