#include <iostream>
#include <pigpio.h>

#define SENSOR_HALL 17 // GPIO 17

// sensores das gavetas 
#define SENSOR_IR_1 23 // GPIO 23
#define SENSOR_IR_2 24 // GPIO 24
#define SENSOR_IR_3 25 // GPIO 25
#define SENSOR_IR_4 8  // GPIO 8
#define SENSOR_IR_5 7 // GPIO 7


void ISRGaveta(int gpio, int level, uint32_t tick) {
	
	double tempoinicial = time_time();
	while(time_time() < tempoinicial + 0.01){
		
	}
	
    // Lógica a ser executada quando ocorrer a interrupção
    std::cout << "Interrupção detectada!" << std::endl;
	if (gpioRead(SENSOR_HALL) == 0) {
		std::cout << "G1" << std::endl;
	} else {
		std::cout << "G0" << std::endl;
	}

	if (gpioRead(SENSOR_IR_1) == 0) {
		std::cout << "AAA1" << std::endl;
	} else {
		std::cout << "AAA0" << std::endl;
	}

	if (gpioRead(SENSOR_IR_2) == 0) {
		std::cout << "AA1" << std::endl;
	} else {
		std::cout << "AA0" << std::endl;
	}

	if (gpioRead(SENSOR_IR_3) == 0) {
		std::cout << "9V1" << std::endl;
	} else {
		std::cout << "9V0" << std::endl;
	}

	if (gpioRead(SENSOR_IR_4) == 0) {
		std::cout << "C1" << std::endl;
	} else {
		std::cout << "C0" << std::endl;
	}

	if (gpioRead(SENSOR_IR_5) == 0) {
		std::cout << "D1" << std::endl;
	} else {
		std::cout << "D0" << std::endl;
	}
}

int main() {
    if (gpioInitialise() < 0) {
        std::cerr << "Falha ao inicializar o pigpio" << std::endl;
        return 1;
    }

    // Configura a porta GPIO como entrada
    gpioSetMode(SENSOR_HALL, PI_INPUT);
    gpioSetMode(SENSOR_IR_1, PI_INPUT);
    gpioSetMode(SENSOR_IR_2, PI_INPUT);
    gpioSetMode(SENSOR_IR_3, PI_INPUT);
    gpioSetMode(SENSOR_IR_4, PI_INPUT);
    gpioSetMode(SENSOR_IR_5, PI_INPUT);

    // Configura a interrupção para a borda de subida (RISING) do sinal
     if (gpioSetISRFunc(SENSOR_HALL, FALLING_EDGE, 0, ISRGaveta) < 0) {
        std::cerr << "Falha ao inicializar a interrupção" << std::endl;
        return 1;
    }
	

    // Lógica principal do programa
    while (true) {
        // Realize outras tarefas ou espere aqui
    }

    gpioTerminate();  // Encerra a biblioteca pigpio

    return 0;
}
