#include <iostream>

#include<unistd.h>

#include "SerialCommunication/serial.hpp"

int main() {

    SerialC::SerialConnection a = SerialC::SerialConnection("/dev/ttyACM0");

    usleep(2 * 1000000);

    a.writeM("$0,0,0,1,0,0,0,0,0,0#");

    for(int i = 0; i < 100000; i++){
        usleep(1 * 1000000);
        auto retval = a.readM();
        std::cout << retval << std::endl;
    }


    //https://blog.mbedded.ninja/programming/operating-systems/linux/linux-serial-ports-using-c-cpp/

    return 0;
}
