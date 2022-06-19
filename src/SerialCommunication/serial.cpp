// C library headers
#include <stdio.h>
#include <string.h>

// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()
#include <sys/ioctl.h>  // Read buffer size


// Normal headers

#include "serial.hpp"


namespace SerialC{

    SerialConnection::SerialConnection(const std::string &name, const int &baudrate){
        /* Open File Descriptor */
        this->serialPort = open(name.data(), O_RDWR| O_NOCTTY );
        this->restoreOriginaltty = false;

        /* Error Handling */
        if (this->serialPort < 0){
            std::cout << "Error " << errno << " opening " << name << ": " << strerror (errno) << std::endl;
        }
        else{
            setConfig(baudrate);
        }
        return;
    };

    SerialConnection::~SerialConnection(){
        if (this->serialPort < 0){
            std::cout << "Error, empty class";
            return;
        }
        if (this->restoreOriginaltty){
            tcsetattr(this->serialPort, TCSANOW, &this->originaltty);
        }
        
        close(this->serialPort);
        return;
    }

    void SerialConnection::setConfig(const int &baudrate){
        // Guide to config variables:
        // https://blog.mbedded.ninja/programming/operating-systems/linux/linux-serial-ports-using-c-cpp/

        // Populate tty with default settings
        termios tty;
        if(tcgetattr(this->serialPort, &tty) != 0) {
            std::cout << "Error: " << errno << " from tcgetattr " << strerror(errno) << std::endl;
            return;
        }

        // Create backup tty
        if (!this->restoreOriginaltty){
            this->originaltty = tty;
            this->restoreOriginaltty = true;
        }

        // Control Modes (Cflags)
        this->setFlag(tty.c_cflag, PARENB, false);  // Parity bit
        this->setFlag(tty.c_cflag, CSTOPB, false);  // 2 stop bits
        this->setFlag(tty.c_cflag, CSIZE, false);   // Clear number of bits per byte
        this->setFlag(tty.c_cflag, CS8, true);      // Set 8 bits per byte
        this->setFlag(tty.c_cflag, CRTSCTS, false); // Hardware flow controll
        this->setFlag(tty.c_cflag, CREAD , true);   // Read data
        this->setFlag(tty.c_cflag, CLOCAL, true);   // Disable modem specific signal lines (carrier detect)

        // Local Modes (Lflag)
        this->setFlag(tty.c_lflag, ICANON, false);  // Canonical Mode
        this->setFlag(tty.c_lflag, ECHO, false);    // DISABLE!!!
        this->setFlag(tty.c_lflag, ECHOE, false);   // DISABLE!!!
        this->setFlag(tty.c_lflag, ECHONL, false);  // DISABLE!!!
        this->setFlag(tty.c_lflag, ISIG, false);    // Treat intr, quit and susp as command instead of chars

        // Input Modes (Iflag)
        this->setFlag(tty.c_iflag, IXON | IXOFF | IXANY, false); // Software flow controll
        this->setFlag(tty.c_iflag, IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL, false); // Special handeling of bytes on receive

        // Output Modes (Oflag)
        this->setFlag(tty.c_oflag, OPOST, false);   // Special interpretation of output bytes
        this->setFlag(tty.c_oflag, ONLCR, false);   // Conversion of newline to carriage return/line feed

        // Vmin Vtime (c_cc)
        tty.c_cc[VTIME] = 0;   // Minimum wait time from first byte recieved 0.1s per value
        tty.c_cc[VMIN]  = 0;    // Minimum number of bytes

        // Baud rate

        cfsetispeed(&tty, baudrate);
        cfsetospeed(&tty, baudrate);

        // Save tty settings, also checking for error
        if (tcsetattr(this->serialPort, TCSANOW, &tty) != 0) {
            std::cout << "Error " << errno << "from tcsetattr: " << strerror(errno) << std::endl;
        }    

        return;
    }

    void SerialConnection::writeM(std::string message){
        write(this->serialPort, message.data(), message.length());
        return;
    }

    std::string SerialConnection::readM(){
        char readBuffer[1024];

        int n = read(this->serialPort, &readBuffer, sizeof(readBuffer)); 

        if (n < 0){
            std::cout << "Can't write message, unknown error!" << std::endl;
            return "";        
        }
        if (n == 0){
            return "";
        }
        return std::string(&readBuffer[0], &readBuffer[n]);
    }

    int SerialConnection::readMSize(){
        int bytes = 0;

        ioctl(this->serialPort, FIONREAD, &bytes);

        return bytes;
    }


    void SerialConnection::setFlag(tcflag_t &fieldToUpdate, const tcflag_t flag, const bool value){
        if (value){     
            fieldToUpdate |= flag;  // set bit to true
        }else{         
            fieldToUpdate &= ~flag; // set bit to false
        }
        return;
    }


}
