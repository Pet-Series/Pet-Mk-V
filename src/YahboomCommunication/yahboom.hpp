#pragma once

#include "SerialCommunication/serial.hpp"

namespace YahboomC {

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

        void enableLogging();
        void disableLogging();

        // someStruct getLoggingInformation();

        private:
        SerialC::SerialConnection serialConnection;
        char ringBuffer[2048];



    };
}