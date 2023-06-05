#include <iostream>
#include <pigpiod_if2.h>

// sensor magnético
#define HALL_SENSOR_PIN 17 // GPIO 17



// sensores das gavetas 
#define IR_SENSOR_PIN_1 23 // GPIO 23
#define IR_SENSOR_PIN_2 24 // GPIO 24
#define IR_SENSOR_PIN_3 25 // GPIO 25
#define IR_SENSOR_PIN_4 8  // GPIO 8
#define IR_SENSOR_PIN_5 16 // GPIO 16

// sensor da entrada
#define IR_SENSOR_PIN_6 5 // GPIO 5

int main() {
    int pi = pigpio_start(NULL, NULL);
    if (pi < 0) {
        std::cerr << "Falha ao inicializar o pigpio" << std::endl;
        return 1;
    }

    set_mode(pi, HALL_SENSOR_PIN, PI_INPUT);
    set_mode(pi, HALL_SENSOR_PIN_1, PI_INPUT);
    set_mode(pi, HALL_SENSOR_PIN_2, PI_INPUT);
    set_mode(pi, HALL_SENSOR_PIN_3, PI_INPUT);
    set_mode(pi, HALL_SENSOR_PIN_4, PI_INPUT);
    set_mode(pi, HALL_SENSOR_PIN_5, PI_INPUT);

    while (true) {
        if (gpio_read(pi, HALL_SENSOR_PIN) == 0) {
            std::cout << "Gaveta fechada" << std::endl;
        } else {
            std::cout << "Gaveta aberta" << std::endl;
        }

        if (gpio_read(pi, IR_SENSOR_PIN_1) == 0) {
            std::cout << "Compartimento da pilha AAA não está vazio" << std::endl;
        } else {
            std::cout << "Compartimento da pilha AAA está vazio" << std::endl;
        }

        if (gpio_read(pi, IR_SENSOR_PIN_2) == 0) {
            std::cout << "Compartimento da pilha AA não está vazio" << std::endl;
        } else {
            std::cout << "Compartimento da pilha AA está vazio" << std::endl;
        }

        if (gpio_read(pi, IR_SENSOR_PIN_3) == 0) {
            std::cout << "Compartimento da pilha C não está vazio" << std::endl;
        } else {
            std::cout << "Compartimento da pilha C está vazio" << std::endl;
        }

        if (gpio_read(pi, IR_SENSOR_PIN_4) == 0) {
            std::cout << "Compartimento da pilha D não está vazio" << std::endl;
        } else {
            std::cout << "Compartimento da pilha D está vazio" << std::endl;
        }

        if (gpio_read(pi, IR_SENSOR_PIN_5) == 0) {
            std::cout << "Compartimento da pilha 9V não está vazio" << std::endl;
        } else {
            std::cout << "Compartimento da pilha 9V está vazio" << std::endl;
        }
    }

    pigpio_stop(pi);
    return 0;
}
