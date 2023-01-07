#pragma once

#include "SerialCommunication/serial.hpp"


namespace YahboomC {

    struct Measurments{
        double leftWheelTick;
        double rightWheelTick;
        double acceleration; // ???
        double gyro; // ???
        double soundSensorDistance;
        double voltage;
    };

    class YahboomConnection
    {
        public:
        YahboomConnection(const std::string &ttyName): YahboomConnection(ttyName, 9600){};
        YahboomConnection(const std::string &ttyName, const int &baudrate);
        ~YahboomConnection();

        // move forward
        // move back
        // signle function for movement?
        // read documentation for this!

        void tick();

        Measurments getSensorData();
        // someStruct getLoggingInformation();

        private:
        SerialC::SerialConnection serialConnection;
        Measurments sensorData;
        char ringBuffer[2048];

        void enableLogging();
        void disableLogging();

        void tickRead();
        void tickWrite();

        void parseReadMessage();


    };
}