/*
 * PaccerInput
 * =========
 *
 * Library for the input code for the Paccer Pinball; gets input e.g. from sensor or simulates input.
 *
 * This lib sends the data to PaccerCommon.
 *
 * Created 2022-05-22
 *
 * https://github.com/PaccerPinball/PaccerInput
 */


#ifndef PaccerInput_H
#define PaccerInput_H

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <PaccerCommon.h>

#define SENSOR_COOLDOWN 2000

class PaccerInput {
    private:
        unsigned int currentInput{};
        unsigned long currentInputMillis{};
        PaccerCommon* common;
        char commandBuffer[20]{};
        unsigned int commandIdx = 0;
        static void serial(const String& msg);
        boolean checkInput(const int& type) const;
    public:
        explicit PaccerInput(PaccerCommon* common);
        /** Called from the main arduino sketch every loop() */
        void tick();
        void command(const String& command);
        void simulateInput(const unsigned int& input);
};

#endif
