#define LED_VERMELHO 2
#define LED_VERDE 3
#define LED_AZUL 4
#define LED_AMARELO 5

#define BTN_A 6
#define BTN_B 7
#define UNDEFINED -1

#define QTD_LEDS 4

enum Estados {
  PRONTO_PROXIMA_RODADA,
  USUARIO_RESPONDENDO,
  JOGO_FINALIZADO_SUCESSO,
  JOGO_FINALIZADO_FALHA
};

int ledArray[QTD_LEDS];
int btnAState = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  randomSeed(analogRead(0));
  iniciaPortas();
  iniciaJogo();
  mostraJogo();
}

void iniciaPortas() {
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AZUL, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(BTN_A, INPUT_PULLUP);
  pinMode(BTN_B, INPUT_PULLUP);
}

void iniciaJogo(){
  for(int i=0; i < QTD_LEDS; i++){
    ledArray[i] = random(LED_VERMELHO, LED_AMARELO +1);
    digitalWrite(ledArray[i], LOW);
  }
}

void loop() {
  switch(estadoAtual()){
    case PRONTO_PROXIMA_RODADA: break;
    case USUARIO_RESPONDENDO: break;
    case JOGO_FINALIZADO_SUCESSO: break;
    case JOGO_FINALIZADO_FALHA: break;
  }
  int led_port =checaInputJogador();
  digitalWrite(led_port, HIGH);
  digitalWrite(led_port, LOW);
}

int estadoAtual(){
  return PRONTO_PROXIMA_RODADA;
}

int checaInputJogador(){
  if(digitalRead(BTN_A) == LOW){
    return LED_AMARELO;
  }
  else if(digitalRead(BTN_B) == LOW){
    return LED_AZUL;
  }
  return UNDEFINED;
}

void mostraJogo(){
  for(int i=0; i < QTD_LEDS; i++){
    piscaLed(ledArray[i]);
  }
}

void piscaLed(int led_port){
  digitalWrite(led_port, HIGH);
  delay(1000);
  digitalWrite(led_port, LOW);
  delay(500);
}

