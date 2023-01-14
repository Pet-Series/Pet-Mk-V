#pragma once

#include <string>
#include "SerialCommunication/serial.hpp"


namespace YahboomC {

    //enum class Direction {STOP = 0, FORWARD = 1, BACKWARDS = 2, LEFTTURN = 3, RIGHTTURN = 4};
    //enum class Rotation {STOP = 0, RIGHTROTATION = 1, LEFTROTATION = 2};
    //enum class QueryPID {NA = 0, QUERY = 1, RESTOREDEFAULTS = 2};
    //enum class BoolPP {NA = 0, START = 1, STOP = 2};

    struct PIDSettings{
        double proportional;
        double integral;
        double derivative;
    };

    struct Measurments{
        double leftWheelTick = 0;
        double rightWheelTick = 0;
        double acceleration = 0; // ???
        double gyro = 0; // ???
        double soundSensorDistance = 0;
        double voltage = 0;
        uint messageNr = 0;
    };

    struct Command{
        int direction = 0;                      // Range: 0 - 4 | 0: Stop, 1: Forward, 2: Backwards, 3: Turn left, 4: Turn right
        int rotation = 0;                       // Range: 0 - 2 | 0: Stop, 1: Rotate left, 2: Rotate right
        int queryPID = 0;                       // Range: 0 - 2 | 0: N/A, 1: Query, 2: Restore default
        int reportMeasurments = 0;              // Range: 0 - 2 | 0: N/A, 1: Start, 2: Stop
        bool updatePIDAngle = false;            // Range: 0 - 1 | 0: False, 1: True
        bool updatePIDVelocity = false;         // Range: 0 - 1 | 0: False, 1: True
        double angleP = 0;                      // Range: -inf - inf | PID: Proportional
        double angleD = 0;                      // Range: -inf - inf | PID: Derivative
        double velocityP = 0;                   // Range: -inf - inf | PID: Proportional
        double velocityI = 0;                   // Range: -inf - inf | PID: Integral

        const std::string toString()
        {
            std::string AP, AD, VP, VI;
            if (angleP == 0){
                AP = "0";
            }
            else{
                AP = "AP" + std::to_string(angleP);
            }

            if (angleD == 0){
                AD = "0";
            }
            else{
                AD = "AD" + std::to_string(angleD);
            }

            if (velocityP == 0){
                VP = "0";
            }
            else{
                VP = "VP" + std::to_string(velocityP);
            }

            if (velocityI == 0){
                VI = "0";
            }
            else{
                VI = "VI" + std::to_string(velocityI);
            }

            return "$" + std::to_string(direction) + "," + 
                         std::to_string(rotation) + "," + 
                         std::to_string(queryPID) + "," +
                         std::to_string(reportMeasurments) + "," + 
                         std::to_string(updatePIDAngle) + "," +
                         std::to_string(updatePIDVelocity) + "," +
                         AP + "," +
                         AD + "," +
                         VP + "," +
                         VI + "#";
        } 
    };


    class YahboomConnection
    {
        public:
        YahboomConnection(const std::string &ttyName): YahboomConnection(ttyName, 9600){};
        YahboomConnection(const std::string &ttyName, const int &baudrate);
        ~YahboomConnection();

        void stop();
        void forward();
        void backwards();
        void turnRight();
        void turnLeft();
        void rotateLeft();
        void rotateRight();
        void updatePIDAngle(const PIDSettings &PID);
        void updatePIDVelocity(const PIDSettings &PID);

        void resetPIDSettings();
        const PIDSettings getPIDSettings();
        const Measurments getSensorData();

        void tick();

        private:
        SerialC::SerialConnection serialConnection;
        Measurments sensorData;
        std::string bufferString;

        void enableLogging();
        void disableLogging();

        void tickRead();
        void tickWrite(const std::string &message);

        // $ direction, rotation, Q-pid, measurments, U-pid1, U-pid2,           AP(1),           AD(1),           VP(2),           VI(2) #
        // $     (0-4),    (0-2), (0-2),       (0-2),  (0-1),  (0-1), AP(0.00-100.00), AD(0.00-100.00), VP(0.00-100.00), VI(0.00-100.00) #
        // $0,0,0,0,0,0,0,0,0,0# <- valid "do nothing" message

        void parseReadMessage();


    };
}