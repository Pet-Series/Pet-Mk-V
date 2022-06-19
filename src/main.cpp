#include "SerialCommunication/serial.hpp"

int main() {

    SerialC::SerialConnection a = SerialC::SerialConnection("/dev/ttyUSB0");
    int k = 100;
    for(int i = 0; i < k; i++){
        a.writeM("hello world!");
    }
    a.writeM("hello world!");

    //https://blog.mbedded.ninja/programming/operating-systems/linux/linux-serial-ports-using-c-cpp/

    return 0;
}
