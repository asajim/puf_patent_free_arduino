#include <SerialStream.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include <ctime>
#include <iostream>
#include <chrono>
#include <cstring>
#include "Tools.h"
#include "BCH.h"

using namespace std::chrono;

int
main(int argc,
     char **argv) {
    //
    // Open the serial port.
    //
    using namespace std;
    using namespace LibSerial;
    SerialStream serial_port;
    char c;
    serial_port.Open("/dev/ttyACM0");
    if (!serial_port.good()) {
        std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] "
                  << "Error: Could not open serial port."
                  << std::endl;
        exit(1);
    }
    //
    // Set the baud rate of the serial port.
    //
    serial_port.SetBaudRate(SerialStreamBuf::BAUD_9600);
    if (!serial_port.good()) {
        std::cerr << "Error: Could not set the baud rate." <<
                  std::endl;
        exit(1);
    }
    //
    // Set the number of data bits.
    //
    serial_port.SetCharSize(SerialStreamBuf::CHAR_SIZE_8);
    if (!serial_port.good()) {
        std::cerr << "Error: Could not set the character size." <<
                  std::endl;
        exit(1);
    }
    //
    // Disable parity.
    //
    serial_port.SetParity(SerialStreamBuf::PARITY_NONE);
    if (!serial_port.good()) {
        std::cerr << "Error: Could not disable the parity." <<
                  std::endl;
        exit(1);
    }
    //
    // Set the number of stop bits.
    //
    serial_port.SetNumOfStopBits(1);
    if (!serial_port.good()) {
        std::cerr << "Error: Could not set the number of stop bits."
                  << std::endl;
        exit(1);
    }
    //
    // Turn off hardware flow control.
    //
    serial_port.SetFlowControl(SerialStreamBuf::FLOW_CONTROL_NONE);
    if (!serial_port.good()) {
        std::cerr << "Error: Could not use hardware flow control."
                  << std::endl;
        exit(1);
    }
    //
    // Do not skip whitespace characters while reading from the
    // serial port.
    //
    // serial_port.unsetf( std::ios_base::skipws ) ;
    //
    // Wait for some data to be available at the serial port.
    //
    //
    // Keep reading data from serial port and print it to the screen.
    //
    // Wait for some data to be available at the serial port.
    //
    while (serial_port.rdbuf()->in_avail() == 0) {
        usleep(100);
//        cout << "waiting" ;
    }


//    char out_buf[] = "check";
//    char to_send;
//    cout << "type a to start\n";
//    cin >> to_send;
//    serial_port.write(reinterpret_cast<const char *>(to_send), 1);

    //serial_port.write(out_buf, 5);  //<--FIRST COMMAND

    Tools tools;
    cout << "start\n";
    milliseconds t = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );
    milliseconds start = t;
    string result = "";
    long time_diff = 0;
    while ( serial_port.rdbuf()->in_avail() > 0 || time_diff < 2000) {
        if (serial_port.rdbuf()->in_avail() == 0){
            milliseconds t2 = duration_cast< milliseconds >(
                    system_clock::now().time_since_epoch()
            );
            time_diff = t2.count() - t.count() + time_diff;
            t = duration_cast< milliseconds >(
                    system_clock::now().time_since_epoch()
            );

            usleep(100);
            continue;
        }
        time_diff = 0;
        t = duration_cast< milliseconds >(
                system_clock::now().time_since_epoch()
        );
        char next_byte;
        serial_port.get(next_byte);
//        cout << next_byte;
        result += tools.hex_char_to_bin(next_byte);


//        cout << next_byte;
//        std::cerr << next_byte;

    }
    std::cerr << std::endl;
//    cout << result << "\n";
    cout << "finish\n";
    milliseconds finish = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
    );
    cout << "total " << finish.count() - start.count() << "\n";


    /********************************************************/
    /******************* TEST BCH CODE **********************/
    /********************************************************/

    cout << "\nSTART BCH\n";
    BCH bch;

    int* input_enrollment = tools.convertStringToIntArray(result, 33726);
//    int* input_reconstruction = tools.convertStringToIntArray(result, 33726);
//    int *input_reconstruction = tools.readFile(
//            "/home/ade>/CLionProjects/puf_patent_free_arduino/bit readout/23LC1024/W/21.c",
//            33726);
    int *input_reconstruction = tools.readFileSimple(
            "/home/ade/CLionProjects/SerialServer/input_reconstruction.c",
            33726);
//
//    cout << input_enrollment << "\n";
//    cout << input_reconstruction << "\n";

    tools.saveToFile(input_enrollment, 33726, "input_enrollment.txt");
    tools.saveToFile(input_reconstruction, 33726, "input_reconstruction.txt");

//    tools.print_array(input_enrollment, 100);
//    int row = bch.get_row();
//    int n = bch.get_n();
//    int k = bch.get_key_length();
//
//    /************************************
//     ****** GENERATION PROCEDURE ******
//     ************************************/
//    bch.initialize();               /* Read m */
//
////    int *encoded = (int *) malloc(sizeof(int) * n);
////    bch.encode_bch(key, encoded);           /* encode data */
////    tools.print_array(encoded, n);
//
//    int *key = (int *) malloc(sizeof(int) * k * row);
//    int *encoded = (int *) malloc(sizeof(int) * n * row);
//    for (int i = 0; i < row; i++) {
//        memcpy(&key[i * k], &input_enrollment[i * n], k * sizeof(int));
//        bch.encode_bch(&key[i * k], &encoded[i * n]);           /* encode data */
//    }
//    printf("KEY\n");
//    tools.print_array(key, k);
//    printf("ENCODED\n");
//    tools.print_array(encoded, n*row);
//
//    int *xor_enroll = tools.xor_array(encoded, input_enrollment, n * row);
//
//    int *helper_data = (int *) malloc(sizeof(int) * (n - k) * row);
//    for (int i = 0; i < row; i++) {
//        memcpy(&helper_data[i * (n - k)], &xor_enroll[i * n], (n - k) * sizeof(int));
//    }
//
//
//    /************************************
//     ****** REPRODUCTION PROCEDURE ******
//     ************************************/
//    int *helper_data_padded = (int *) malloc(sizeof(int) * n * row);
//    tools.initialize_array(helper_data_padded, n * row, 0);
//    for (int i = 0; i < row; i++) {
//        memcpy(&helper_data_padded[i * n], &helper_data[i * (n - k)], (n - k) * sizeof(int));
//    }
//
//    printf("HELPER DATA\n");
//    tools.print_array(helper_data_padded, n*row);
//
//    int *xor_reproduction = tools.xor_array(input_reconstruction, helper_data_padded, n * row);
//    printf("XOR REPRODUCTION\n");
//    tools.print_array(xor_reproduction, n*row);
//
//    int *reconstructed_key = (int *) malloc(sizeof(int) * k * row);
//    for (int i = 0; i < row; i++) {
//        bch.decode_bch(&xor_reproduction[i * n], &reconstructed_key[i * k]);
//    }
//    printf("XOR REPRODUCTION\n");
//    tools.print_array(xor_reproduction, n);
//    printf("XOR REPRODUCTION\n");
//    tools.print_array(&xor_reproduction[n-k], k);
//
//    for (int i = 0; i < row; i++) {
//        printf("DIFFERENCE INPUT %d\n",
//               tools.difference_array(&input_enrollment[i * n], &input_reconstruction[i * n], n));
//        printf("KEY\n");
//        tools.print_array(&key[i * k], k);
//        printf("RECONSTRUCTED KEY\n");
//        tools.print_array(&reconstructed_key[i * k], k);
//        printf("DIFFERENCE KEY %d\n", tools.difference_array(&key[i * k], &reconstructed_key[i * k], k));
//    }

    return EXIT_SUCCESS;
}