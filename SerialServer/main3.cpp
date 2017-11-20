//
// Created by ade on 9-11-17.
//

#include <unistd.h>
#include <ctime>
#include <iostream>
#include <chrono>
#include "Tools.h"
#include <stdint.h>
#include <stdlib.h>
#include <cstdio>
#include <cstdint>
#include <string>
#include <cinttypes>

using namespace std;
using namespace std::chrono;

int main(){
//    uint8_t a = 0xFF;
//    uint8_t b = 0x00;
//    uint8_t c = 0xFF;
//    uint8_t d = 0x00;
//    uint32_t e =(uint32_t) (a << 24 | b << 16 | c << 8 | d);
//    cout << hex << +a << "\n";
//    cout << hex << +b << "\n";
//    cout << hex << +c << "\n";
//    cout << hex << +d << "\n";
//    cout << hex << +e << "\n";
//
//    Tools t;
//    t.printBits(sizeof(a), &a);
//    t.printBits(sizeof(a), &b);
//    t.printBits(sizeof(a), &c);
//    t.printBits(sizeof(a), &d);
//    t.printBits(sizeof(e), &e);
//
//    uint64_t
//    uint8_t f[4];
//    f[0] = 0xFF;
//    f[1] = 0x00;
//    f[2] = 0xFF;
//    f[3] = 0x00;
//
//    uint32_t* g = (uint32_t*) &f;
//    cout << hex << +g << "\n";
//    t.printBits(sizeof(g), &g);
//
//    uint32_t h =(uint32_t) (f[0] << 24 | f[1] << 16 | f[2] << 8 | f[3]);
//    t.printBits(sizeof(h), &h);
//    cout << hex << +h << "\n";
    uint32_t a = 16843009;
    printf("%08x", a);
}