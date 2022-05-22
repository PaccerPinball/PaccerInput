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

class PaccerInput {
    private:
        PaccerCommon* common;
    public:
        explicit PaccerInput(PaccerCommon* common);
        /** Called from the main arduino sketch every loop() */
        void tick();
};

#endif
