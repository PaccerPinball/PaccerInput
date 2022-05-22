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


#include "PaccerInput.h"
#include <LiquidCrystal.h>
#include <PaccerCommon.h>

PaccerInput::PaccerInput(PaccerCommon *common) {
    this->common = common;
}

void PaccerInput::tick() {
    Serial.println("INPUT TICK");
}
