#include <iostream>
#include <pigpio.h>
#include <string.h>

// sensores com interupções
#define SENSOR_IR_ENTRADA 18 	// GPIO 18
#define SENSOR_HALL 17 			// GPIO 17

// sensores dos compartimentos
#define SENSOR_IR_1 23 	// GPIO 23
#define SENSOR_IR_2 24 	// GPIO 24
#define SENSOR_IR_3 25 	// GPIO 25
#define SENSOR_IR_4 8  	// GPIO 8
#define SENSOR_IR_5 7 	// GPIO 7

// motor de passo
#define DIRMotor 27 // GPIO 27
#define STPMotor 22 // GPIO 22
#define ENAMotor 26 // GPIO 26

// posições do motor de passo
#define POS0 0	// 
#define POS1 1	// 
#define POS2 2	// 
#define POS3 3	// 
#define POS4 4	// 

char respostaIA[4];
const int speed = 1000;		// Velocidade do motor de passo (em microssegundos)
int posicaoAtual = 0;

// Função para mover o motor de passo em uma direção específica
void moveStepper(int numSteps, int direction) {
    // Define a direção do motor de passo (0 para sentido horário, 1 para sentido anti-horário)
    gpioWrite(DIRMotor, direction);

    // Move o motor de passo
    for (int i = 0; i < numSteps; i++) {
        gpioWrite(STPMotor, 1);
        time_sleep(speed / 1000000.0);
        gpioWrite(STPMotor, 0);
        time_sleep(speed / 1000000.0);
    }
}

// ISR para tratar inserção de nova pilha (sensor IR)
void ISREntrada(int gpio, int level, uint32_t tick) {
	// Debouncing do sensor
	double tempoInicial = time_time();			// Tempo em segundos
	while(time_time() < tempoInicial + 0.01){	// Aguarda 10 ms
	}
	
	// Girar servo pra posição neutra
	// DESCOBRIR FUNÇÕES DE GIRAR SERVO
	
    std::cout << "Interrupção detectada no Sensor IR!" << std::endl;
	// Avisa IA para começar análise
    std::cout << "AI" << std::endl;
	// Espera a resposta da IA
	scanf("%s", &respostaIA);
	
	int delta = 0;
	int direcao = 0;
	
	// DESCOBRIR A DIREÇÃO DO MOTOR
	// DESCOBRIR OS PASSOS DO MOTOR
	// Calcula o quanto o motor deve girar e direção
	if(strcmp(respostaIA, "AI0\0") == 0){
		delta = POS0 - posicaoAtual;
	}
	else if(strcmp(respostaIA, "AI1\0") == 0){
		delta = POS1 - posicaoAtual;
	}
	else if(strcmp(respostaIA, "AI2\0") == 0){
		delta = POS2 - posicaoAtual;
	}
	else if(strcmp(respostaIA, "AI3\0") == 0){
		delta = POS3 - posicaoAtual;
	}
	else if(strcmp(respostaIA, "AI4\0") == 0){
		delta = POS4 - posicaoAtual;
	}
	else{
		delta = 0;
	}
	direcao = delta>=0 ? 0 : 1;
	// Gira o motor
	moveStepper(abs(delta)*20, direcao);
	
	// Gira os servos para derrubar pilha
	if(strcmp(respostaIA, "AI5\0") == 0){
		// Girar pra fora
	} else {
		// Girar pra dentro
	}
}

// ISR para tratar fechamento da gaveta (sensor hall)
void ISRGaveta(int gpio, int level, uint32_t tick) {
	// Debouncing do sensor
	double tempoInicial = time_time();			// Tempo em segundos
	while(time_time() < tempoInicial + 0.01){	// Aguarda 10 ms
	}
	
    // Lógica a ser executada quando ocorrer a interrupção
    std::cout << "Interrupção detectada no Sensor Hall!" << std::endl;
	// Indica o estado de cada compartimento (vazio ou não-vazio)
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
    gpioSetMode(SENSOR_IR_ENTRADA, PI_INPUT);
    gpioSetMode(SENSOR_IR_1, PI_INPUT);
    gpioSetMode(SENSOR_IR_2, PI_INPUT);
    gpioSetMode(SENSOR_IR_3, PI_INPUT);
    gpioSetMode(SENSOR_IR_4, PI_INPUT);
    gpioSetMode(SENSOR_IR_5, PI_INPUT);

	// Configura interupção do sensor hall na gaveta
    // - borda de descida (FALLING) do sinal
     if (gpioSetISRFunc(SENSOR_HALL, FALLING_EDGE, 0, ISRGaveta) < 0) {
        std::cerr << "Falha ao inicializar a interrupção do Sensor Hall" << std::endl;
        return 1;
    }
	// Configura interrupção do sensor IR na entrada da caixa
    // - borda de descida (FALLING) do sinal
     if (gpioSetISRFunc(SENSOR_IR_ENTRADA, FALLING_EDGE, 0, ISREntrada) < 0) {
        std::cerr << "Falha ao inicializar a interrupção do Sensor IR" << std::endl;
        return 1;
    }
	

    // Lógica principal do programa
    while (true) {
        // Realize outras tarefas ou espere aqui
    }

    gpioTerminate();  // Encerra a biblioteca pigpio

    return 0;
}
