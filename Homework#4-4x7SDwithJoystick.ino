#define FIRST_STATE 1
#define SECOND_STATE 2
#define DISPLAY_COUNT 4
#define MAX_DISPLAYED_VALUE_INDEX 15
#define DISPLAY_1_INDEX 0
#define DISPLAY_2_INDEX 1
#define DISPLAY_3_INDEX 2
#define DISPLAY_4_INDEX 3
#define REGISTER_SIZE 8
#define BAUD_RATE 9600

byte DEBUGGING_MODE = false;

const int latchPin = 11;
const int clockPin = 10;
const int dataPin = 12; 

const int segD1 = 7;
const int segD2 = 6;
const int segD3 = 5;
const int segD4 = 4;

unsigned const int pinSW = 2;
unsigned const int pinX = A0;
unsigned const int pinY = A1;

unsigned const long debounceDelay = 300;
unsigned const long resetTime = 3000;
volatile unsigned long buttonWasPressedTimestamp = 0;

byte buttonWasPressed = false;
byte buttonWasReleased = true;
byte state = FIRST_STATE;
byte DPstate = true;

unsigned int xValue = 0;
unsigned int yValue = 0;

unsigned const int xMinTreshold = 300;
unsigned const int xMaxTreshold = 700;
unsigned const int yMinTreshold = 300;
unsigned const int yMaxTreshold = 700;

const int encodingsNumber = 16;
int displayDigit = DISPLAY_1_INDEX;

int byteEncodings[encodingsNumber] = {
//A B C D E F G DP
  B11111100, // 0
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110, // 9
  B11101110, // A
  B00111110, // b
  B10011100, // C
  B01111010, // d
  B10011110, // E
  B10001110  // F
};
    
unsigned int toBeDisplayed[DISPLAY_COUNT] = {
  0, 0, 0, 0
};

int displayDigits[DISPLAY_COUNT] = {
  segD1, segD2, segD3, segD4
};
void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(pinSW, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pinSW), interruptHandler, CHANGE);

 for (auto display : displayDigits) {
    pinMode(display, OUTPUT);
    digitalWrite(display, HIGH);
  }  
  Serial.begin(BAUD_RATE);
}


void loop() {
  if(buttonWasPressed && buttonWasReleased) {
    buttonWasPressed = false;
    state = changeState(state);
  }
  else{
    if(buttonWasPressed && !buttonWasReleased && state == FIRST_STATE && millis() - buttonWasPressedTimestamp > resetTime) {
      buttonWasPressed = false;
      for(int i = 0; i < DISPLAY_COUNT; i++) {
        toBeDisplayed[i] = 0;
      }
      displayDigit = DISPLAY_1_INDEX;
    }
  }

  switch(state) {
    case FIRST_STATE:
      DPstate = getDPState(DPstate);
      displayDigit = switchDisplay(displayDigit);
      break;
    case SECOND_STATE:
      DPstate = true;
      setDisplayOutput(displayDigit);
      break;
    default:
      break;
  }
  activateDisplay(displayDigit, DPstate);
}


void interruptHandler() {
  static unsigned long lastPressTime = 0;
  static unsigned long lastReleaseTime = 0;
  unsigned long interruptTime = millis();
  byte buttonPressed = !digitalRead(pinSW);

  if(buttonPressed) {
    if (interruptTime - lastPressTime > debounceDelay)
    {
      buttonWasPressedTimestamp = interruptTime;
      buttonWasPressed = true;
      buttonWasReleased = false;
    }
    lastPressTime = interruptTime;
  }
  else {
    if(interruptTime - lastReleaseTime > debounceDelay) {
      buttonWasReleased = true;
     }
     lastReleaseTime = interruptTime;
  }
}


byte changeState(byte currState) {
  if(DEBUG_MODE) {
    Serial.print("Changed state: from ");
    Serial.print(currState);
    Serial.print(" to ");
  }
  if(currState == FIRST_STATE) {
    currState = SECOND_STATE;
  }
  else {
    currState = FIRST_STATE;
  }
  if(DEBUG_MODE) { 
    Serial.print(currState);
    Serial.prinln("");
  }
  return currState;
}


void writeReg(int digit) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, digit);
    digitalWrite(latchPin, HIGH);
}


void activateDisplay(int currentDisplay, byte dpState) {
  for (int i = 0; i < DISPLAY_COUNT; i++) {
    if(i == currentDisplay) {
      byteEncodings[toBeDisplayed[currentDisplay]] += dpState;
    }
    writeReg(byteEncodings[toBeDisplayed[i]]);
    byteEncodings[toBeDisplayed[currentDisplay]] = (byteEncodings[toBeDisplayed[currentDisplay]] / 2) * 2;
    digitalWrite(displayDigits[i], LOW);
    delay(5);
    digitalWrite(displayDigits[i], HIGH);
  }
}


unsigned int switchDisplay(unsigned int displayDigit) {
  static byte didNotMove = 0;
  static byte previouslySwitchedDisplay;
  xValue = analogRead(pinX);
  short int move = 0;
  Serial.println(xValue);
  if(xValue >= xMaxTreshold) {
    move = -1;
  } 
  if(xValue <= xMinTreshold){ 
    move = 1;    
  }
  if(move == didNotMove) {
    previouslySwitchedDisplay = false;
  }
  else{
    if(!previouslySwitchedDisplay) {
      previouslySwitchedDisplay = true;
      
      if(displayDigit + move <= DISPLAY_1_INDEX){
        displayDigit = DISPLAY_1_INDEX;
      } else
          if(displayDigit + move >= DISPLAY_4_INDEX){
            displayDigit = DISPLAY_4_INDEX;
          } else {
          displayDigit += move;
        }
    }
  }
  return displayDigit;
}


byte getDPState(byte dpState) {
  const unsigned long blinkDelay = 300;
  static unsigned long lastLedStateChange = 0;
  unsigned long currentTime = millis();
  if(currentTime - lastLedStateChange > blinkDelay) {
    dpState = !dpState;
    lastLedStateChange = currentTime;
  }
  return dpState; 
}

void setDisplayOutput(unsigned int displayDigit) {
  short int valueAdded = 0;
  yValue = analogRead(pinY);
  static byte didNotChangeValue = 0;
  static byte previouslySetOutput;
  

  if(yValue >= yMaxTreshold) {
    valueAdded = -1;
  } 
  if(yValue <= yMinTreshold){ 
    valueAdded = 1;    
  }

if(valueAdded == didNotChangeValue) {
    previouslySetOutput = false;
  }
  else {
    if(!previouslySetOutput) {
      previouslySetOutput = true;
      
      if(toBeDisplayed[displayDigit] + valueAdded < 0){
        toBeDisplayed[displayDigit] = 0;
      } else
          if(toBeDisplayed[displayDigit] + valueAdded > MAX_DISPLAYED_VALUE_INDEX){
            toBeDisplayed[displayDigit] = MAX_DISPLAYED_VALUE_INDEX;
          } else {
          toBeDisplayed[displayDigit] += valueAdded;
          }
    }
  }
}
