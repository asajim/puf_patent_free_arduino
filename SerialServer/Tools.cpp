//
// Created by ade on 9-11-17.
//

#include "Tools.h"

Tools::Tools() {}

std::string Tools::hex_char_to_bin(char c) {
    // TODO handle default / error
    switch (toupper(c)) {
        case '0':
            return "0000";
        case '1':
            return "0001";
        case '2':
            return "0010";
        case '3':
            return "0011";
        case '4':
            return "0100";
        case '5':
            return "0101";
        case '6':
            return "0110";
        case '7':
            return "0111";
        case '8':
            return "1000";
        case '9':
            return "1001";
        case 'A':
            return "1010";
        case 'B':
            return "1011";
        case 'C':
            return "1100";
        case 'D':
            return "1101";
        case 'E':
            return "1110";
        case 'F':
            return "1111";
        default:
            return "";
    }
}

std::string Tools::hex_str_to_bin_str(const std::string &hex) {
    // TODO use a loop from <algorithm> or smth
    std::string bin;
    for (unsigned i = 0; i != hex.length(); ++i)
        bin += hex_char_to_bin(hex[i]);
    return bin;
}

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

int *Tools::readFileSimple(string address, int count) {
    FILE *myFile;
    myFile = fopen(address.c_str(), "r");

    int *numberArray = (int*)malloc(sizeof(int) * count);
    int i;

    if (myFile == NULL) {
        printf("Error Reading File\n");
        exit(0);
    }

    for (i = 0; i < count; i++)
        fscanf(myFile, "%u", &numberArray[i]);

    fclose(myFile);
    return numberArray;
}

int *Tools::convertStringToIntArray(string input, int length) {
    int *b = (int*) malloc(sizeof(int)*length);
    int i = 0;
    for(int j = 0;j<length;j++) {
        char c = input[j];
        b[i++] = c - '0';
    }
    return b;
}

void Tools::saveToFile(int* input, int length, string filename) {
    std::ofstream os(filename);
    if (!os) { std::cerr<<"Error writing to ..."<<std::endl; } else {
        for (int i=0;i<length;i++){
            os << input[i];
        }
    }
}

void Tools::saveToFile(string input, int length, string filename) {
    std::ofstream os(filename);
    if (!os) { std::cerr<<"Error writing to ..."<<std::endl; } else {
        os << input;
    }
}

void Tools::printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i=size-1;i>=0;i--)
    {
        for (j=7;j>=0;j--)
        {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}