#include <iostream>

#include <unistd.h>

#include "YahboomCommunication/yahboom.hpp"
//#include "SerialCommunication/serial.hpp"

int main() {

    YahboomC::YahboomConnection a = YahboomC::YahboomConnection("/dev/ttyACM0");

    int state = 0;

   for(int i = 0; i < 100000; i++){
        usleep(1 * 1000000);

        switch (state) 
        {
            case 0:
                a.forward();
                state = 1;
                break;
            case 1:
                a.backwards();
                state = 2;
                break;
            case 2:
                a.rotateLeft();
                state = 3;
                break;
            case 3:
                a.rotateLeft();
                state = 4;
                break;
            case 4:
                a.rotateRight();
                state = 0;
                break;
        }


        a.tick();
        auto retval = a.getSensorData();
        std::cout << "========== Data ==========" << std::endl;
        std::cout << "Left wheel: " << retval.leftWheelTick << std::endl;
        std::cout << "Right wheel: " << retval.rightWheelTick << std::endl;
        std::cout << "Acceleration: " << retval.acceleration << std::endl;
        std::cout << "Gyro: " << retval.gyro << std::endl;
        std::cout << "Distance: " << retval.soundSensorDistance << std::endl;
        std::cout << "Voltage: " << retval.voltage << std::endl;
        std::cout << "========== " << i << " ==========" << std::endl;
    }

    //https://blog.mbedded.ninja/programming/operating-systems/linux/linux-serial-ports-using-c-cpp/

    return 0;
}
