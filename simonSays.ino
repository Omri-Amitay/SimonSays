#define buttonNum  4
#define ledNum  4
#define buzzer 11
#define MAX_SEQUENCE 100
int button[buttonNum] = {3, 2, 4, 5};
int led[ledNum] = {7, 8, 9, 6};
int sequence[MAX_SEQUENCE];
int sequenceEnd = 0;


void setup() {
  // put your setup code here, to run once:
  for ( int i = 0; i < buttonNum; i++) {
    pinMode(led[i], OUTPUT);
    pinMode(button[i], INPUT_PULLUP);

  }
  pinMode(buzzer, OUTPUT);


  for ( int i = 0 ; i < MAX_SEQUENCE ; i++) {
    sequence[i] = -1;
  }

  Serial.begin(9600);
  randomSeed(analogRead(A0));

}

int checkButton() {
  while (true) {
    for ( int i = 0; i < buttonNum; i++) {
      if (digitalRead(button[i]) == LOW) {
        Serial.print("Led Turned on: ");
        tone(buzzer, 300 + i * 100, 500);
        Serial.println(led[i]);
        digitalWrite(led[i], HIGH);
        delay(500);
        digitalWrite(led[i], LOW);
        return i;

      }
    }
  }

}
bool sequenceCheck() {
  for (int i = 0; i < MAX_SEQUENCE; i++) {
    if (sequence[i] == -1) {
      delay(1000);
      return true; // checks if sequence is over
    }
    int buttonPressed = checkButton();
    Serial.print("buttonPressed: ");
    Serial.print(buttonPressed);
    Serial.print(" I: ");
    Serial.println(i);
    if (buttonPressed == sequence[i]) {
      Serial.println("Button Correct!");

    }
    else {
      Serial.println("Button Wrong!");
      return false ;
    }
  }

  // for loop check first sequence and check.

}
void allLedsBlink(int blinkDelay) {
  for (int i = 0; i < ledNum; i++) {
    digitalWrite(led[i], HIGH);
  }
  delay(blinkDelay);
  for (int i = 0; i < ledNum; i++) {

    digitalWrite(led[i], LOW);

  }
  delay(500);
}
void turnLED(int pin) {
  digitalWrite(led[pin], HIGH);
  delay(500);
  digitalWrite(led[pin], LOW);
  delay(200);
  Serial.println("Led Turned on!");
  Serial.println(pin);
}
void addSequence() {

  int ledToAdd = random(0, 4);
  if (sequenceEnd == 99) {
    Serial.println("SequenceEnd is already at 99!!!");
    return ;
  }
  sequence[sequenceEnd] = ledToAdd;
  //  Serial.print("ledToAdd: ");
  //  Serial.print(ledToAdd);
  //  Serial.print(" Sequence End: ");
  //  Serial.println(sequenceEnd);

  for ( int i = 0; i < sequenceEnd + 1; i++) {
    turnLED(sequence[i]);
    Serial.print("COUNTER: ");

    Serial.print(i);
    Serial.print(" LED PIN: ");
    Serial.println(sequence[i]);
  }
  sequenceEnd++;
}
void resetGame() {
  allLedsBlink(100);
  allLedsBlink(100);
  allLedsBlink(100);
  for (int i = 0; i < MAX_SEQUENCE; i++) {
    sequence[ i] = -1;
    sequenceEnd = 0;
  }
  tone(buzzer, 500, 500);
  tone(buzzer, 330, 500);
}
void loop() {
  addSequence();
  bool passedTest = sequenceCheck();
  Serial.print("PassedTest: ");
  Serial.println(passedTest);
  if (passedTest == false) {
    resetGame();
  }
  //for(int i = 0; i <


}
