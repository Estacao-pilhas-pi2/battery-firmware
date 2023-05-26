#include <iostream>
#include <wiringPi.h>

//sensor magnetico
#define HALL_SENSOR_PIN 0 // GPIO 17
// sensores de obstaculos 
#define IR_SENSOR_PIN_1 4 // GPIO 23
#define IR_SENSOR_PIN_2 5 // GPIO 24
#define IR_SENSOR_PIN_3 6 // GPIO 25
#define IR_SENSOR_PIN_4 10 // GPIO 8
#define IR_SENSOR_PIN_5 27 // GPIO 16

int main() {
    wiringPiSetup();
    pinMode(HALL_SENSOR_PIN, INPUT);

    pinMode(HALL_SENSOR_PIN, INPUT);

    while (true) {
        if (digitalRead(HALL_SENSOR_PIN) == LOW) {
            std::cout << "Gaveta fechada" << std::endl;
        } else {
            std::cout << "Gaveta aberta" << std::endl;
        }

        if (digitalRead(IR_SENSOR_PIN_1) == LOW){
            std::cout << "Compartimento da pilha AAA nao esta vazio" << std::endl;
        } else{
            std::cout << "Compartimento da pilha AAA esta vazio" << std::endl;
        }

        if (digitalRead(IR_SENSOR_PIN_2) == LOW){
            std::cout << "Compartimento da pilha AA nao esta vazio" << std::endl;
        } else{
            std::cout << "Compartimento da pilha AA esta vazio" << std::endl;
        }

        if (digitalRead(IR_SENSOR_PIN_3) == LOW){
            std::cout << "Compartimento da pilha C nao esta vazio" << std::endl;
        } else{
            std::cout << "Compartimento da pilha C esta vazio" << std::endl;
        }

        if (digitalRead(IR_SENSOR_PIN_4) == LOW){
            std::cout << "Compartimento da pilha D nao esta vazio" << std::endl;
        } else{
            std::cout << "Compartimento da pilha D esta vazio" << std::endl;
        }

        if (digitalRead(IR_SENSOR_PIN_5) == LOW){
            std::cout << "Compartimento da pilha 9V nao esta vazio" << std::endl;
        } else{
            std::cout << "Compartimento da pilha 9V esta vazio" << std::endl;
        }
    }

    return 0;
}
