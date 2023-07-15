#define SENSOR_IR_ENTRADA 34
#define SENSOR_IR1 35
#define SENSOR_IR2 32
#define SENSOR_IR3 33
#define SENSOR_IR4 25
//#define SENSOR_IR5 00
#define SENSOR_HALL 26
#define SERVO0 27
#define SERVO1 14
#define STEP_DIR 12
#define STEP_STP 13

unsigned long tempo_inicial;
bool entrou = false;
bool fechou = false;

void isr_entrada(){
  tempo_inicial = millis();
  while(millis() < tempo_inicial + 250){
  }
  entrou = true;
}

void isr_gaveta(){
  tempo_inicial = millis();
  while(millis() < tempo_inicial + 250){
  }
  fechou = true;
}

void setup() {  
  Serial.begin(115200);
  
  pinMode(SENSOR_IR_ENTRADA, INPUT);
  pinMode(SENSOR_IR1, INPUT);
  pinMode(SENSOR_IR2, INPUT);
  pinMode(SENSOR_IR3, INPUT);
  pinMode(SENSOR_IR4, INPUT);
//  pinMode(SENSOR_IR5, INPUT);
  pinMode(SENSOR_HALL, INPUT);
  pinMode(STEP_DIR, OUTPUT);
  pinMode(STEP_STP, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(SENSOR_IR_ENTRADA), isr_entrada, RISING);
  attachInterrupt(digitalPinToInterrupt(SENSOR_HALL), isr_gaveta, RISING);

  // ledcSetup(uint8_t channel, uint32_t freq, uint8_t resolution_bits)
  ledcSetup(0, 50, 8);
  ledcSetup(1, 50, 8);
  // ledcAttachPin(uint8_t pin, uint8_t channel)
  ledcAttachPin(SERVO0, 0);
  ledcAttachPin(SERVO1, 1);
}

void loop() {  
  if(Serial.available()){
    Serial.println(Serial.readString());

    // Fazer aqui controle do passo e servo

    // ledcWrite(uint8_t channel, uint32_t duty);
//    ledcWrite(0, dutyCycle);
//    ledcWrite(1, dutyCycle);
  }
  
  if(entrou){
    Serial.println("AI");
    entrou = false;
  }
  if(fechou){
    Serial.println("SITUAÇÃO DA GAVETA");
    fechou = false;
  }
}
