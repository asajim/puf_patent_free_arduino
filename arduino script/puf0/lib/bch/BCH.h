//
// Created by Ade Setyawan on 10/25/17.
//

#ifndef BCH_BCH_H
#define BCH_BCH_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "string.h"

class BCH {
private:
//    int8_t m = 4;
//    int8_t n = 15;
//    int8_t k = 5;
//    int8_t t = 3;
//    int8_t d = 7;

    int m = 6;
    uint16_t n = 63;
    int k = 7;
    int t = 15;
    int d = 31;

    int8_t *p;
    int8_t *alpha_to;
    int8_t *index_of;
    int8_t *g;
    int8_t row = ceil(256/k);

public:
    BCH();

    void initialize();

    void
    initialize_p();

    void
    generate_gf();

    void
    gen_poly();

    void
    encode_bch(int8_t *input, int8_t *result);

    void
    decode_bch(int8_t *input, int8_t *result);

    int get_row();

    int get_key_length();

    int get_n();

    int get_t();

    int get_m();

    void clean();
};

#endif //BCH_BCH_H
