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

    int n = 1;
    int total = 40;
    while(n <= total) {
        while (serial_port.rdbuf()->in_avail() == 0) {
            usleep(100);
        }

        Tools tools;
        cout << "start " << n << "\n";
        milliseconds t = duration_cast<milliseconds>(
                system_clock::now().time_since_epoch()
        );
        milliseconds start = t;
        string result = "";
        long time_diff = 0;
        while (serial_port.rdbuf()->in_avail() > 0 || time_diff < 2000) {
            if (serial_port.rdbuf()->in_avail() == 0) {
                milliseconds t2 = duration_cast<milliseconds>(
                        system_clock::now().time_since_epoch()
                );
                time_diff = t2.count() - t.count() + time_diff;
                t = duration_cast<milliseconds>(
                        system_clock::now().time_since_epoch()
                );

                usleep(100);
                continue;
            }
            time_diff = 0;
            t = duration_cast<milliseconds>(
                    system_clock::now().time_since_epoch()
            );
            char next_byte;
            serial_port.get(next_byte);
//        cout << next_byte;
            result += next_byte;//tools.hex_char_to_bin(next_byte);


//        cout << next_byte;
//        std::cerr << next_byte;

        }
        cout << "finish\n";
//        cout << result << "\n";
        milliseconds finish = duration_cast<milliseconds>(
                system_clock::now().time_since_epoch()
        );
        cout << "total " << finish.count() - start.count() << "\n";

//        int* input_enrollment = tools.convertStringToIntArray(result, 33726);
        string name = to_string(n) + ".txt";
        tools.saveToFile(result, 33726, name);

        n++;
    }

    return EXIT_SUCCESS;
}