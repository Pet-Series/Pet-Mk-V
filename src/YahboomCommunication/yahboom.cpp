#include <string>
#include "SerialCommunication/serial.hpp"
#include "yahboom.hpp"




namespace YahboomC {

    YahboomConnection::YahboomConnection(const std::string &ttyName, const int &baudrate) : 
        serialConnection(ttyName, baudrate)
    {
        //this->serialConnection;
        //this->bufferString = "";
        //this->sensorData = YahboomC::Measurments();  
        this->enableLogging();
        ;
    }

    YahboomConnection::~YahboomConnection(){
        // Do nothing I guess
        // this->serialConnection.~SerialConnection();
    }

    void YahboomConnection::forward(){
        YahboomC::Command command = YahboomC::Command();
        command.direction = 1;
        this->tickWrite(command.toString());
    }

    void YahboomConnection::backwards(){
        YahboomC::Command command = YahboomC::Command();
        command.direction = 2;
        this->tickWrite(command.toString());
    }

    void YahboomConnection::turnRight(){
        YahboomC::Command command = YahboomC::Command();
        command.direction = 3;
        this->tickWrite(command.toString());
    }

    void YahboomConnection::turnLeft(){
        YahboomC::Command command = YahboomC::Command();
        command.direction = 4;
        this->tickWrite(command.toString());
    }

    void YahboomConnection::rotateLeft(){
        YahboomC::Command command = YahboomC::Command();
        command.rotation = 1;
        this->tickWrite(command.toString());
    }

    void YahboomConnection::rotateRight(){
        YahboomC::Command command = YahboomC::Command();
        command.rotation = 2;
        this->tickWrite(command.toString());
    }

    void YahboomConnection::updatePIDAngle(const PIDSettings &PID){
        YahboomC::Command command = YahboomC::Command();
        command.updatePIDAngle = true;
        command.angleD = PID.derivative;
        command.angleP = PID.proportional;
        this->tickWrite(command.toString());
    }

    void YahboomConnection::updatePIDVelocity(const PIDSettings &PID){
        YahboomC::Command command = YahboomC::Command();
        command.updatePIDVelocity = true;
        command.velocityI = PID.integral;
        command.velocityP = PID.proportional;
        this->tickWrite(command.toString());
    }

    void YahboomConnection::resetPIDSettings(){
        YahboomC::Command command = YahboomC::Command();
        command.queryPID = 2;
        this->tickWrite(command.toString());
    }

    const PIDSettings YahboomConnection::getPIDSettings(){
        YahboomC::Command command = YahboomC::Command();
        command.queryPID = 1;
        this->tickWrite(command.toString());
        // TODO: implement this part... somehow

        return YahboomC::PIDSettings();
    }

    const Measurments YahboomConnection::getSensorData(){
        return this->sensorData;
    }

    void YahboomConnection::tick(){
        ;
    }

    void YahboomConnection::enableLogging(){
        ;
    }

    void YahboomConnection::disableLogging(){
        ;
    }

    void YahboomConnection::tickRead(){
        ;
    }

    void YahboomConnection::tickWrite(const std::string &message){
        ;
    }

    void YahboomConnection::parseReadMessage(){
        ;
    }

}