#include <iostream>
#include "Tools.h"

using namespace std;

int main() {
    Tools tools;
    BCH bch;

    int *input_enrollment = tools.readFile("/Users/ades17/Documents/Thesis/Software/pycharm/23LC1024/171017D/1.c",
                                               33726);
    int *input_reconstruction = tools.readFile(
            "/Users/ades17/Documents/Thesis/Software/pycharm/23LC1024/171017D/2.c",
            33726);
//    int key[31] = {1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1};
//    int key[31] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1};

    tools.print_array(input_enrollment, 100);
    int row = bch.get_row();
    int n = bch.get_n();
    int k = bch.get_key_length();

    /************************************
     ****** GENERATION PROCEDURE ******
     ************************************/
    bch.initialize();               /* Read m */

//    int *encoded = (int *) malloc(sizeof(int) * n);
//    bch.encode_bch(key, encoded);           /* encode data */
//    tools.print_array(encoded, n);

    int *key = (int *) malloc(sizeof(int) * k * row);
    int *encoded = (int *) malloc(sizeof(int) * n * row);
    for (int i = 0; i < row; i++) {
        memcpy(&key[i * k], &input_enrollment[i * n], k * sizeof(int));
        bch.encode_bch(&key[i * k], &encoded[i * n]);           /* encode data */
    }

    bch.encode_bch(key, encoded);           /* encode data */


    printf("KEY\n");
    tools.print_array(key, k*row);
    printf("ENCODED\n");
    tools.print_array(encoded, n*row);

    int *xor_enroll = tools.xor_array(encoded, input_enrollment, n * row);

    int *helper_data = (int *) malloc(sizeof(int) * (n - k) * row);
    for (int i = 0; i < row; i++) {
        memcpy(&helper_data[i * (n - k)], &xor_enroll[i * n], (n - k) * sizeof(int));
    }


    /************************************
     ****** REPRODUCTION PROCEDURE ******
     ************************************/
    int *helper_data_padded = (int *) malloc(sizeof(int) * n * row);
    tools.initialize_array(helper_data_padded, n * row, 0);
    for (int i = 0; i < row; i++) {
        memcpy(&helper_data_padded[i * n], &helper_data[i * (n - k)], (n - k) * sizeof(int));
    }

//    printf("HELPER DATA\n");
//    tools.print_array(helper_data_padded, n*row);

    int *xor_reproduction = tools.xor_array(input_reconstruction, helper_data_padded, n * row);
//    printf("XOR REPRODUCTION\n");
//    tools.print_array(xor_reproduction, n*row);

    int *reconstructed_key = (int *) malloc(sizeof(int) * k * row);
    for (int i = 0; i < row; i++) {
        bch.decode_bch(&xor_reproduction[i * n], &reconstructed_key[i * k]);
    }
//    printf("XOR REPRODUCTION\n");
//    tools.print_array(xor_reproduction, n);
//    printf("XOR REPRODUCTION\n");
//    tools.print_array(&xor_reproduction[n-k], k);

    int total_diff = 0;
    int diff_input, diff_key;
    for (int i = 0; i < row; i++) {
        diff_input = tools.difference_array(&input_enrollment[i * n], &input_reconstruction[i * n], n);
        printf("DIFFERENCE INPUT %d\n", diff_input);
//        printf("KEY\n");
//        tools.print_array(&key[i * k], k);
//        printf("RECONSTRUCTED KEY\n");
//        tools.print_array(&reconstructed_key[i * k], k);
        diff_key = tools.difference_array(&key[i * k], &reconstructed_key[i * k], k);
        printf("DIFFERENCE KEY %d\n", diff_key);
        if (diff_key > 0)
            total_diff++;
//        printf("DIFFERENCE INPUT %d\n",
//               tools.difference_array(&input_enrollment[i * n], &input_reconstruction[i * n], n));
//        printf("KEY\n");
//        tools.print_array(&key[i * k], k);
//        printf("RECONSTRUCTED KEY\n");
//        tools.print_array(&reconstructed_key[i * k], k);
//        printf("DIFFERENCE KEY %d\n", tools.difference_array(&key[i * k], &reconstructed_key[i * k], k));
    }
    printf("\nTotal Diff: %d", total_diff);

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