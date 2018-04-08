
#define LED_RED 2
#define LED_GREEN 3
#define LED_BLUE 4
#define LED_YELLOW 5

#define BTN_A 6
#define BTN_B 7
#define BTN_C 8
#define BTN_D 9

#define QTD_LEDS 4

#define UNDEFINED -1

enum States {
  NEXT_ROUND,
  USER_TURN,
  GAME_WIN,
  GAME_OVER
};

enum GAME_DIFFICULTY {
  EASY = 4,
  NORMAL = 8,
  HARD = 15 
};

int *leds;
int DIFFICUTY = NORMAL;
int currentState = NEXT_ROUND;
int turn = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  randomSeed(analogRead(0));
  
  setPorts();
  
  DIFFICUTY = setGameDifficult();
  leds = malloc(DIFFICUTY * sizeof(int));
  Serial.print("Difficulty: ");
  Serial.println(DIFFICUTY);  

  loadColors();
}

void setPorts() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  
  pinMode(BTN_A, INPUT_PULLUP);
  pinMode(BTN_B, INPUT_PULLUP);
  pinMode(BTN_C, INPUT_PULLUP);
  pinMode(BTN_D, INPUT_PULLUP);
}

int setGameDifficult(){
  if(((digitalRead(BTN_A) == LOW) || (digitalRead(BTN_D) == LOW))){
      return EASY;
  }
  else if (((digitalRead(BTN_B) == LOW) || (digitalRead(BTN_C) == LOW))){
    return HARD;
  }
  return NORMAL;  
}

void loadColors(){
  for(int i=0; i<DIFFICUTY; i++){
    leds[i] = random(LED_RED, LED_YELLOW +1);
  }
}

void flashLight(int led){
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);
  delay(250);
}

void executeMachineTurn(){
  Serial.println("---Starting Machine Turn---");
  Serial.print("Turn: ");
  Serial.println(turn+1);
  
  if(turn == DIFFICUTY){
    currentState = GAME_WIN;
    Serial.println("Setting State to GAME_WIN");
    Serial.println("---Ending Machine Turn---");
    return;
  }
  
  turn++;
  for(int i=0; i < turn; i++){
    Serial.print("Flashing LED:");
    Serial.println(leds[i]);
    flashLight(leds[i]);
  }
  
  currentState =  USER_TURN;
  Serial.println("Setting State to USER_TURN");
  Serial.println("---Ending Machine Turn---");
}

void executeUserTurn(){
  Serial.println("---Starting User Turn---");
  int i=0;
  while(i < turn){
    if(digitalRead(BTN_A) == LOW){
      flashLight(LED_YELLOW);
      if(leds[i] != LED_YELLOW){
        currentState = GAME_OVER;
        return;
      }
      i++;
    }
    else if(digitalRead(BTN_B) == LOW){
      flashLight(LED_BLUE);
      if(leds[i] != LED_BLUE){
        currentState = GAME_OVER;
        return;
      }
      i++;
    }
    else if(digitalRead(BTN_C) == LOW){
      flashLight(LED_GREEN);
      if(leds[i] != LED_GREEN){
        currentState = GAME_OVER;
        return;
      }
      i++;
    }
    else if(digitalRead(BTN_D) == LOW){
      flashLight(LED_RED);
      if(leds[i] != LED_RED){
        currentState = GAME_OVER;
        return;
      }
      i++;
    }
  }
  currentState = NEXT_ROUND;
  Serial.println("---Ending User Turn---");
}

void executeGameCleared(){
  for(int j=0; j <20; j++){
    for(int i=0; i < QTD_LEDS; i++){
      digitalWrite(i+2, HIGH);
      delay(200*((j%3)*0.25));
      digitalWrite(i+2, LOW);
      delay(200*((j%3)*0.25));
    }
    for(int i=(QTD_LEDS-1); i >= 0; i--){
      digitalWrite(i+2, HIGH);
      delay(200*((j%3)*0.25));
      digitalWrite(i+2, LOW);
      delay(200*((j%3)*0.25));
    }
  }
  currentState = UNDEFINED;
}

void executeGameOver(){
  Serial.println("GAME OVER!!!");
  for(int j=0; j < 3; j++ ){
    for(int i=0; i < QTD_LEDS; i++){
      digitalWrite(i+2, HIGH);
    }
    delay(500);
    for(int i=0; i < QTD_LEDS; i++){
      digitalWrite(i+2, LOW);
    }
    delay(500);
  }
  currentState = UNDEFINED;
}

void loop() {
  switch(currentState){
    case NEXT_ROUND: executeMachineTurn(); break;
    case USER_TURN: executeUserTurn(); break;
    case GAME_WIN: executeGameCleared(); break;
    case GAME_OVER: executeGameOver(); break;
  }
}
