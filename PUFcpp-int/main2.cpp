//
// Created by Ade Setyawan on 28/11/17.
//

#include <iostream>
#include <random>
#include "Tools.h"

using namespace std;

bool is_array_contain(int *array, int length, int val) {
    for (int i = 0; i < length; i++) {
        if (array[i] == val)
            return true;
    }
    return false;
}

int *generate_random(int range_from, int range_to, int count) {
    int *result = (int *) malloc(count * sizeof(int));
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<int> distr(range_from, range_to);

    int a = 0;
    for (int i = 0; i < count; ++i) {
        a = distr(generator);
        while (is_array_contain(result, i, a))
            a = distr(generator);
        result[i] = a;
    }
    std::sort(result,result+count, std::greater<int>());
    return result;
}

int flip(int a, int* error, int count){
    for (int i=0;i<count;i++){
        a = a ^ ((1<<error[i]));
    }
    return a;
}

int * int_to_binary(int value, int length){
    int * result = (int*)malloc(sizeof(int)*length);
    for (int i = 0; i < length; ++i) {
        result[length-1-i] = (value >> i) & 1;
    }

    return result;
}

int main() {
    Tools tools;
    BCH bch;

    int m = bch.get_m();
    int n = bch.get_n();
    int k = bch.get_key_length();
    int t = bch.get_t();
    printf("m %d n %d k %d t %d\n", m, n, k, t);
    int *encoded = (int *) malloc(sizeof(int) * n);

    bch.initialize();               /* Read m */

    int total_diff = 0;
    int total_trial = 0;

//    for (int f=0;f<pow(2,k);f++) {
        int * key = int_to_binary(1,k);
//        printf("f %d\n",f);
//        tools.print_array(key, k);

        bch.encode_bch(key, encoded);           /* encode data */
    tools.print_array(encoded, n);


//        int diff_input, diff_key;
//        for (int g = 0; g < 100; g++) {
//            int range_from = 0;
//            int range_to = n;
//            for (int h=1;h<=t;h++) {
//                int count = h;
//                int *errors = generate_random(range_from, range_to, count);
//
//                int *encoded_r = (int *) malloc(sizeof(int) * n);
//                memcpy(encoded_r, encoded, sizeof(int) * n);
//                for (int i = 0; i < count; i++) {
//                    encoded_r[errors[i]] = encoded_r[errors[i]] == 1 ? 0 : 1;
//                }
//
////            diff_input = tools.difference_array(encoded, encoded_r, n);
////            printf("DIFFERENCE INPUT %d\n", diff_input);
//
//                int *key_r = (int *) malloc(sizeof(int) * k);
//                bch.decode_bch(encoded_r, key_r);
//
//                diff_key = tools.difference_array(key, key_r, k);
////                printf("DIFFERENCE KEY %d\n\n", diff_key);
//                if (diff_key > 0)
//                    total_diff += 1;
//                total_trial += 1;
//            }
//        }
//    }
//    printf("TOTAL TRIAL: %d\n", total_trial);
//    printf("TOTAL DIFF: %d\n", total_diff);

    /************************************
     ********** FREE MEMORY *************
     ************************************/
//    bch.clean();
//    free(input_enrollment);
//    free(input_reconstruction);
//    free(helper_data_padded);
//    free(xor_enroll);
//    free(xor_reproduction);
//    free(reconstructed_key);
//    free(encoded);
//    free(key);
    return 0;
}