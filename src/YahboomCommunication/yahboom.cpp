#include <string>
#include <unistd.h>
#include "SerialCommunication/serial.hpp"
#include "yahboom.hpp"




namespace YahboomC {

    YahboomConnection::YahboomConnection(const std::string &ttyName, const int &baudrate) : 
        serialConnection(ttyName, baudrate)
    {
        //this->serialConnection;
        //this->bufferString = "";
        //this->sensorData = YahboomC::Measurments();  
        usleep(2 * 1000000); // TODO: replace with "connection established" check
        this->enableLogging();
    }

    YahboomConnection::~YahboomConnection(){
        this->disableLogging();
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
        // YahboomC::Command command = YahboomC::Command();
        // command.queryPID = 1;
        // this->tickWrite(command.toString());
        // TODO: implement this part... somehow

        return YahboomC::PIDSettings();
    }

    const Measurments YahboomConnection::getSensorData(){
        return this->sensorData;
    }

    void YahboomConnection::tick(){
        this->tickRead();
        this->parseReadMessage();
    }

    void YahboomConnection::enableLogging(){
        YahboomC::Command command = YahboomC::Command();
        command.reportMeasurments = 1;
        this->tickWrite(command.toString());
    }

    void YahboomConnection::disableLogging(){
        YahboomC::Command command = YahboomC::Command();
        command.reportMeasurments = 2;
        this->tickWrite(command.toString());
    }

    void YahboomConnection::tickRead(){
        this->bufferString += this->serialConnection.readM();
    }

    void YahboomConnection::tickWrite(const std::string &message){
        this->serialConnection.writeM(message);
    }

    void YahboomConnection::parseReadMessage(){

        std::size_t firstIndex = this->bufferString.find("$");
        if (firstIndex == std::string::npos){
            return; // Nothing found
        }
        std::size_t lastIndex = this->bufferString.find("#", firstIndex);
        if (lastIndex == std::string::npos){
            return; // Nothing found
        }

        
        const std::string measurmentsString = this->bufferString.substr(firstIndex, lastIndex - firstIndex + 1); // $LV{},RV{},AC{},GY{},CSB{},VT{}#
        const std::string formatString = "$LV0,RV1,AC2,GY3,CSB4,VT5#";
        this->bufferString.erase(0, lastIndex + 1); // clear the string

        //std::cout << measurmentsString << std::endl;

        // Parse command responses
        if (measurmentsString == "$OK#")
        {
            return; // Do nothing
        }


        // Parse mesurements
        YahboomC::Measurments measurments = YahboomC::Measurments();

        int index = 0;
        int numberIndexStart = -1;
        for (unsigned int i = 0 ; i < measurmentsString.size(); i++){
            const char indexChar = formatString.at(index);
            if (isdigit(indexChar)){
                if (numberIndexStart == -1){
                    numberIndexStart = i;
                }
                if (isdigit(measurmentsString.at(i+1)) ||
                    measurmentsString.at(i+1) == '.'){
                        // do nothing
                    }
                    else{
                        double number = std::stod(measurmentsString.substr(numberIndexStart, i - numberIndexStart + 1));
                        switch (indexChar){
                            case '0':
                                measurments.leftWheelTick = number;
                                break;
                            case '1':
                                measurments.rightWheelTick = number;
                                break;
                            case '2':
                                measurments.acceleration = number;
                                break;
                            case '3':
                                measurments.gyro = number;
                                break;
                            case '4':
                                measurments.soundSensorDistance = number;
                                break;
                            case '5':
                                measurments.voltage = number;
                                break;
                            default:
                                throw "test";
                        }

                        numberIndexStart = -1;
                        index++;
                    }
            }
            else{
                if (indexChar == measurmentsString.at(i)){
                    index++;
                }
                else{
                    throw std::runtime_error("Error can't parse the following line: " + measurmentsString);
                }
            }
        }

        measurments.messageNr = this->sensorData.messageNr + 1;
        this->sensorData = measurments;
    }

}