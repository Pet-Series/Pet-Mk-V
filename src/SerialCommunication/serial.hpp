#pragma once

#include <iostream>
#include <string>

#include <termios.h>    // POSIX terminal control definitions

namespace SerialC {

    class SerialConnection
    {
        public:
        SerialConnection(const std::string &name): SerialConnection(name, 9600){};
        SerialConnection(const std::string &name, const int &baudrate);
        ~SerialConnection();

        void writeM(std::string message);
        std::string readM();
        int readMSize();

        void setConfig(const int &baudrate);

        private:
        termios originaltty;
        bool restoreOriginaltty;
        int serialPort;

        void setFlag(tcflag_t &fieldToUpdate, const tcflag_t flag, const bool value);

    };
}