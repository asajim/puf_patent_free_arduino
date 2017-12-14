//
// Created by Ade Setyawan on 10/25/17.
//

#ifndef BCH_BCH_H
#define BCH_BCH_H

#include "Tools.h"

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

    // int m = 7;
    // uint16_t n = 127;
    // int k = 8;
    // int t = 31;
    // int d = 63;

    // int8_t *p;
    // int8_t *alpha_to;
    // int8_t *index_of;
    // int8_t *g;
    int8_t p[6];
    int8_t alpha_to[64];
    int8_t index_of[64];
    int8_t g[56];

    int8_t row = 37;

    Tools tools;

public:
    BCH();

    void
    initialize();

    void
    initialize_p();

    void
    generate_gf();

    void
    gen_poly();

    void
    encode_bch(uint8_t *input, uint8_t *result);

    void
    decode_bch(uint8_t *input, uint8_t *result);

    void decode_bch_old(int8_t *input, uint8_t *result);

    int get_row();

    int
    get_key_length();

    int
    get_n();

    int
    get_t();

    int
    get_m();

    void
    clean();
};

#endif //BCH_BCH_H
