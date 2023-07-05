#include <iostream>
#include <pigpio.h>
#include <string.h>

#define SERVO0 12

int main() {
    if (gpioInitialise() < 0) {
        std::cerr << "Falha ao inicializar o pigpio" << std::endl;
        return 1;
    }

    // Configura a porta GPIO como saida
    gpioSetMode(SERVO0, PI_OUTPUT);
    //gpioSetMode(SERVO1, PI_OUTPUT);
	
	
	//Configura manualmente o pino pwm
	//gpioSetPWMfrequency(SERVO0, 400); // Ver frequencia
	//gpioSetPWMrange(SERVO0, 2500);
	
	std::string mensagem;
	bool condicao;

    while (true) {
	// The range supported by servos varies and should probably be determined by experiment. 
	// A value of 1500 should always be safe and represents the mid-point of rotation. 
	// You can DAMAGE a servo if you command it to move beyond its limits.
	//gpioServo(SERVO0, 700); // Move servo to safe position anti-clockwise.
	//time_sleep(1);
	//gpioServo(SERVO0, (2500+700)/2); // Move servo to safe position anti-clockwise.
	//time_sleep(1);		
	//gpioServo(SERVO0, 2500); // Move servo to centre position.
	//time_sleep(1);
	
	gpioServo(SERVO0, 1600);
	std::getline(std::cin, mensagem);

	condicao = (mensagem.compare("AI0")==0) ||
		   (mensagem.compare("AI1")==0) ||
		   (mensagem.compare("AI2")==0) ||
		   (mensagem.compare("AI3")==0) ||
		   (mensagem.compare("AI4")==0);

	if(mensagem.compare("AI5")==0){
		std::cerr << "Não é pilha" << std::endl;
		gpioServo(SERVO0, 2500);
		time_sleep(1);
	} else if(condicao){
		std::cerr << "É pilha" << std::endl;
		gpioServo(SERVO0, 700);
		time_sleep(1);
	}
    }

    gpioTerminate();  // Encerra a biblioteca pigpio

    return 0;

}
