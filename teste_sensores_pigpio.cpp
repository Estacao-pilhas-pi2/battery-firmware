#include <iostream>
#include <pigpio.h>

// sensor magnético
#define HALL_SENSOR_PIN 17 // GPIO 17
// sensores de obstáculos 
#define IR_SENSOR_PIN_1 23 // GPIO 23
#define IR_SENSOR_PIN_2 24 // GPIO 24
#define IR_SENSOR_PIN_3 25 // GPIO 25
#define IR_SENSOR_PIN_4 8  // GPIO 8
#define IR_SENSOR_PIN_5 16 // GPIO 16

int main() {
    if (gpioInitialise() < 0) {
        std::cerr << "Falha ao inicializar o pigpio" << std::endl << std::flush;
        return 1;
    }

    gpioSetMode(HALL_SENSOR_PIN, PI_INPUT);

    while (true) {
        if (gpioRead(HALL_SENSOR_PIN) == PI_LOW) {
            std::cout << "Gaveta fechada" << std::endl;
        } else {
            std::cout << "Gaveta aberta" << std::endl;
        }

        if (gpioRead(IR_SENSOR_PIN_1) == PI_LOW) {
            std::cout << "Compartimento da pilha AAA não está vazio" << std::endl << std::flush;
        } else {
            std::cout << "Compartimento da pilha AAA está vazio" << std::endl << std::flush;
        }

        if (gpioRead(IR_SENSOR_PIN_2) == PI_LOW) {
            std::cout << "Compartimento da pilha AA não está vazio" << std::endl << std::flush;
        } else {
            std::cout << "Compartimento da pilha AA está vazio" << std::endl << std::flush;
        }

        if (gpioRead(IR_SENSOR_PIN_3) == PI_LOW) {
            std::cout << "Compartimento da pilha C não está vazio" << std::endl << std::flush;
        } else {
            std::cout << "Compartimento da pilha C está vazio" << std::endl << std::flush;
        }

        if (gpioRead(IR_SENSOR_PIN_4) == PI_LOW) {
            std::cout << "Compartimento da pilha D não está vazio" << std::endl << std::flush;
        } else {
            std::cout << "Compartimento da pilha D está vazio" << std::endl << std::flush;
        }

        if (gpioRead(IR_SENSOR_PIN_5) == PI_LOW) {
            std::cout << "Compartimento da pilha 9V não está vazio" << std::endl << std::flush;
        } else {
            std::cout << "Compartimento da pilha 9V está vazio" << std::endl << std::flush;
        }
    }

    gpioTerminate();
    return 0;
}
