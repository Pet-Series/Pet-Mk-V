#include <iostream>
#include <string>

#include <unistd.h>

#include <fcntl.h>
#include <stdio.h>

#include "YahboomCommunication/yahboom.hpp"
//#include "SerialCommunication/serial.hpp"

int main() {

    YahboomC::YahboomConnection a = YahboomC::YahboomConnection("/dev/ttyACM0");

    char state = '0';

    int numRead;
    char buf[20];
    fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);


   for(int i = 0; i < 100000; i++){
        usleep(1 * 100000); // wait 100ms = 0.1s

        numRead = read(0, buf, 1);
        if (numRead > 0) {
            state = buf[0];
        }
        else{
            state = '0';
        }


        switch (state) 
        {
            case 'w':
                a.forward();
                break;
            case 's':
                a.backwards();
                break;
            case 'a':
                a.turnLeft();
                break;
            case 'd':
                a.turnRight();
                break;
            case 'q':
                a.rotateLeft();
                break;
            case 'e':
                a.rotateRight();
                break;
            default:
                a.stop();
                break;
        }


        a.tick();
        //auto retval = a.getSensorData();
        //std::cout << "========== Data ==========" << std::endl;
        //std::cout << "Left wheel: " << retval.leftWheelTick << std::endl;
        //std::cout << "Right wheel: " << retval.rightWheelTick << std::endl;
        //std::cout << "Acceleration: " << retval.acceleration << std::endl;
        //std::cout << "Gyro: " << retval.gyro << std::endl;
        //std::cout << "Distance: " << retval.soundSensorDistance << std::endl;
        //std::cout << "Voltage: " << retval.voltage << std::endl;
        //std::cout << "Message Nr: " << retval.messageNr << std::endl;
        //std::cout << "========== " << i << " ==========" << std::endl;
    }

    //https://blog.mbedded.ninja/programming/operating-systems/linux/linux-serial-ports-using-c-cpp/

    return 0;
}
