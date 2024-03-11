#pragma once

#include "I2C/cppi2c.h" // Inclui a classe I2c para comunicação I2C
#include "font8x8_basic.hpp"
#include <string>
#include <cstdint> // Para uint8_t
#include <cstring> // Para memset e memcpy

class OLED
{
public:
    static const uint8_t WIDTH = 128;
    static const uint8_t HEIGHT = 64;
    static const uint8_t PAGES = HEIGHT / 8;
    uint8_t screenBuffer[PAGES][WIDTH];

    OLED(PROTOCOL::I2c *i2c, uint8_t address = 0x3C);
    void init();
    void displayClear();
    void displayText(const std::string &text, uint8_t x, uint8_t y);
    void displayPattern();
    void setContrast(uint8_t contrast);
    void scroll(bool enable);
    void displaySleep();
    void displayWakeUp();
    void drawBatteryIndicator(uint8_t level);
    void initScreenBuffer();
    void writePixel(uint8_t x, uint8_t y, bool on);
    void updateDisplay();
    void displayTextBuffered(const std::string &text, uint8_t x, uint8_t y);

private:
    PROTOCOL::I2c &_i2c;
    uint8_t _address;
    void sendCommand(uint8_t cmd);
    void sendData(const uint8_t *data, size_t size);
    void setPosition(uint8_t column, uint8_t page);
    static const uint8_t _initCommands[];
};
