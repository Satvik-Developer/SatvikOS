#include "port.h"

Port::Port(uint16_t portnumber) {
    this->portnumber = portnumber;
    }

    Port8Bit::Port8Bit(uint16_t portnumber)
        : Port(portnumber) {
        }

        Port8Bit::~Port8Bit() {
        }

        void Port8Bit::Write(uint8_t data) {
            __asm__ volatile("outb %0, %1" : : "a"(data), "Nd"(portnumber));
            }

            uint8_t Port8Bit::Read() {
                uint8_t result;
                    __asm__ volatile("inb %1, %0" : "=a"(result) : "Nd"(portnumber));
                        return result;
                        }