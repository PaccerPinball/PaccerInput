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

#include <Arduino.h>
#include "PaccerInput.h"
#include <LiquidCrystal.h>
#include <PaccerCommon.h>

PaccerInput::PaccerInput(PaccerCommon *common) {
    this->common = common;
    pinMode(INPUT_SPRING_START, INPUT_PULLUP);
    pinMode(INPUT_PACMAN_INSIDE, INPUT_PULLUP);
    pinMode(INPUT_HOLE_ONE, INPUT_PULLUP);
    pinMode(INPUT_HOLE_TWO, INPUT_PULLUP);
    pinMode(INPUT_SLOW_PROPELLOR, INPUT_PULLUP);
}

void PaccerInput::tick() {
    // Receive serial "commands"
    if (Serial.available() > 0) {
        byte b = Serial.read();
        if(b == '\n') {
            // ensure \0 termination
            commandBuffer[commandIdx] = '\0';
            // interpret command
            command(commandBuffer);
            commandIdx = 0;
        }
        else if(commandIdx < sizeof(commandBuffer) - 1) {
            // Add byte to string
            commandBuffer[commandIdx++] = b; // NOLINT(cppcoreguidelines-narrowing-conversions)
        }
    }
    if (checkInput(INPUT_SPRING_START)) {
        currentInputMillis = millis();
        currentInput = INPUT_SPRING_START;
        simulateInput(INPUT_SPRING_START);
    }
    else if (checkInput(INPUT_PACMAN_INSIDE)) {
        currentInputMillis = millis();
        currentInput = INPUT_PACMAN_INSIDE;
        simulateInput(INPUT_PACMAN_INSIDE);
    }
    else if (checkInput(INPUT_HOLE_ONE)) {
        currentInputMillis = millis();
        currentInput = INPUT_HOLE_ONE;
        simulateInput(INPUT_HOLE_ONE);
    }
}

void PaccerInput::command(const String& command) {
    serial("Received command: " + command);

    if (command.startsWith("input ")) {
        unsigned char c = command.charAt(6);
        unsigned int input = c - '0';
        simulateInput(input);
    }
    else if (command.startsWith("broadcast")) {
        for (int i = 0; i < 20; i++) {
            serial("BROADCAST TEST " + String(i));
        }
    }
}

void PaccerInput::simulateInput(const unsigned int& input) {
    serial("Simulating input: " + String(input));
    common->input(input);
}

void PaccerInput::serial(const String &msg) {
    Serial.println( "INPUT | " + msg);
}

boolean PaccerInput::checkInput(const int &type) const {
    return digitalRead(type) == LOW && (currentInput != type || millis() - currentInputMillis > SENSOR_COOLDOWN);
}
