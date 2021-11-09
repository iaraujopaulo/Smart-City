byte pinSemaforo[] = {2, 3, 4};

byte estado = 0;
int tempoSemaforo, tempoVermelho = 8000;
unsigned long tempoInicial;
bool flagSensor = true, sinalVermelho;

void setup() {
  Serial.begin(9600);
  //Serial.println(pinSemaforo[2]);
  for (byte x = 0; x < 3; x++) {
    pinMode(pinSemaforo[x], OUTPUT);
  }
  tempoInicial = millis();
}

void loop() {
  unsigned long tempoParado, tempoAtualSensor;
  bool sensorIR = digitalRead(5), engarrafamento;
  //se sensorIR for igual a 1
  if ((!sensorIR) and (sinalVermelho)){
    if (flagSensor) {
      tempoAtualSensor = millis();
      engarrafamento = true;
    }
    flagSensor = false;
    tempoParado = millis() - tempoAtualSensor;
    Serial.println(tempoParado);
    if ((tempoParado > 2000) and (engarrafamento)){
      if (estado == 0) {
        tempoVermelho = 1000;
        Serial.println("Sinal vermelho vuado");
        engarrafamento = false;
        sinalVermelho = false;
      }
    }
  }
  else{
    flagSensor = true;    
  }
  semaforo();
}

void semaforo() {
  tempoSemaforo = millis() - tempoInicial;
  if ((tempoSemaforo > tempoVermelho) && (estado == 0)) {
    statusSemaforo("Verde", 0, 0, 1);
    estado = 1;  
    tempoInicial = millis();
    sinalVermelho = false;
  }
  else if ((tempoSemaforo > 6000) && (estado == 1)) {
    statusSemaforo("Amarelo", 0, 1, 0);
    estado = 2;
    tempoInicial = millis();
  }
  else if ((tempoSemaforo > 2000) && (estado == 2)) {
    statusSemaforo("Vermelho", 1, 0, 0);
    estado = 0;
    tempoInicial = millis();
    tempoVermelho = 8000;
    flagSensor = true;
    sinalVermelho = true;
  }
}

void statusSemaforo(String estadoSemaforo, bool statusVermelho, bool statusAmarelo, bool statusVerde) {
  digitalWrite(pinSemaforo[0], statusVermelho);
  digitalWrite(pinSemaforo[1], statusAmarelo);
  digitalWrite(pinSemaforo[2], statusVerde);
  Serial.println(estadoSemaforo);
}
