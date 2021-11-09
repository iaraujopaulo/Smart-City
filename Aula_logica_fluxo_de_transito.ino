//vermelho [0], amarelo [1], verde [2]
byte pinSemaforo[]={2, 3, 4};
//byte pinSemaforo[0] = 2;
//byte pinSemaforo[1] = 3;
//byte pinSemaforo[2] = 4;
byte estado = 0;
int tempoSemaforo, tempoVermelho = 8000;
unsigned long tempoInicial;

void setup() {
  Serial.begin(9600);
  //Serial.println(pinSemaforo[2]);
  for(byte x=0; x<3; x++){
    pinMode(pinSemaforo[x], OUTPUT);
  } 
  tempoInicial = millis();
}

void loop() {
  bool sensorIR = digitalRead(5);
  if (sensorIR){
    if(estado == 1){
      tempoVermelho = 1000;
    }
  }
  Serial.println(sensorIR);
  semaforo();
}

void semaforo(){
  tempoSemaforo = millis() - tempoInicial;
  if ((tempoSemaforo>5000)&&(estado == 0)){
    vermelho();
    estado = 1;
    tempoInicial = millis();
  }
  else if ((tempoSemaforo>tempoVermelho)&&(estado == 1)){
    amarelo();
    estado = 2;
    tempoInicial = millis();
    tempoVermelho = 8000;
  }
  else if ((tempoSemaforo>3000)&&(estado == 2)){
    verde();
    estado = 0;
    tempoInicial = millis();
  }
}

void vermelho(){
  digitalWrite(pinSemaforo[0], HIGH);
  digitalWrite(pinSemaforo[1], LOW);
  digitalWrite(pinSemaforo[2], LOW);
  Serial.println("Vermelho");
}

void amarelo(){
  digitalWrite(pinSemaforo[0], LOW);
  digitalWrite(pinSemaforo[1], HIGH);
  digitalWrite(pinSemaforo[2], LOW);
  Serial.println("Amarelo");
}

void verde(){
  digitalWrite(pinSemaforo[0], LOW);
  digitalWrite(pinSemaforo[1], LOW);
  digitalWrite(pinSemaforo[2], HIGH);
  Serial.println("Verde");
}
