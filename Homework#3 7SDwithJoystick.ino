#define BAUD_RATE 9600
#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define G 6
#define DP 7

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define DIRECTIONS 4
#define STAY 5

#define FIRST_STATE 1
#define SECOND_STATE 2

unsigned const int pinA = 4;
unsigned const int pinB = 5;
unsigned const int pinC = 6;
unsigned const int pinD = 7;
unsigned const int pinE = 8;
unsigned const int pinF = 9;
unsigned const int pinG = 10;
unsigned const int pinDP = 11;

unsigned const int pinSW = 2;
unsigned const int pinX = A0;
unsigned const int pinY = A1;

unsigned const long blinkDelay = 300;
unsigned const long debounceDelay = 300;
unsigned const long resetTime = 3000;
volatile unsigned long buttonWasPressedTimestamp = 0;

volatile byte buttonWasPressed = false;
volatile byte buttonWasReleased = false;
volatile byte state = FIRST_STATE;

unsigned int xValue = 0;
unsigned int yValue = 0;
unsigned const int xMinTreshold = 300;
unsigned const int xMaxTreshold = 700;
unsigned const int yMinTreshold = 300;
unsigned const int yMaxTreshold = 700;

unsigned int currentSegment = DP;
const unsigned int segmentSize = 8;
int segments[segmentSize] = { 
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};
byte segmentStates[segmentSize] = {
  LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW
};
int movementScheme[segmentSize][DIRECTIONS] = {
// UP, DOWN, LEFT, RIGHT
  {A,    G,    F,    B},   // A
  {A,    G,    F,    B},   // B
  {G,    D,    E,    DP},  // C
  {G,    D,    E,    C},   // D
  {G,    D,    E,    C},   // E
  {A,    G,    F,    B},   // F
  {A,    D,    G,    G},   // G
  {DP,   DP,   C,    DP},  // DP
};


void setup() {
  pinMode(pinSW, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pinSW), interruptHandler, CHANGE);
  for (int i = 0; i < segmentSize; i++) {
    pinMode(segments[i], OUTPUT);
  }
  Serial.begin(BAUD_RATE);
}


void loop() {
  
  if(buttonWasPressed && buttonWasReleased){
    buttonWasPressed = false;
    state = changeState(state);
  }
  else{
    if(buttonWasPressed && !buttonWasReleased && state == FIRST_STATE && millis() - buttonWasPressedTimestamp > resetTime) {
      buttonWasPressed = false;
      for(int i = 0; i < segmentSize; i++){
        segmentStates[i] = LOW;
        currentSegment = DP;
      }
    }
  }
  switch(state) {
    case FIRST_STATE:
      defaultState();
      currentSegment = switchSegment(currentSegment);
      break;
    case SECOND_STATE:
      toggleSegmentOutput(currentSegment);
      break;
    default:
      break;
  }
  displaySegments();
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


void displaySegments(){
  for(unsigned int segIndex = 0; segIndex < segmentSize; segIndex++){
    if(segIndex == currentSegment) {
      continue;
    }
    digitalWrite(segments[segIndex], segmentStates[segIndex]);
  }
}


byte changeState(byte currState) {
  if(currState == FIRST_STATE){
    currState = SECOND_STATE;
  }
  else {
    currState = FIRST_STATE;
  }
  return currState;
}


unsigned int switchSegment(unsigned int segment) {
  unsigned int move = STAY;
  static byte previouslyMoved;
  xValue = analogRead(pinX);
  yValue = analogRead(pinY);
  if(yValue >= yMaxTreshold){
    move = DOWN;
  }
  if(yValue <= yMinTreshold){
    move = UP;
  }
  if(xValue >= xMaxTreshold){
    move = RIGHT;
  } 
  if(xValue <= xMinTreshold){+
    move = LEFT;    
  }
  if(move == STAY){
    previouslyMoved = false;
  }
  else{
    if(!previouslyMoved) {
      previouslyMoved = true;
      return movementScheme[segment][move];
    }
  }
  return segment;
}


void defaultState() {
  static byte ledState = LOW;
  static unsigned long lastLedStateChange = 0;
  unsigned long currentTime = millis();

  if(currentTime - lastLedStateChange > blinkDelay){
    digitalWrite(segments[currentSegment], ledState);
    ledState = !ledState;
    lastLedStateChange = currentTime;
  }
}


void toggleSegmentOutput(unsigned int segment) {
  
  xValue = analogRead(pinX);
  if(xValue >= xMaxTreshold){
    segmentStates[segment] = HIGH;
  }
  if(xValue <= xMinTreshold){
    segmentStates[segment] = LOW;
  }
  digitalWrite(segments[segment], segmentStates[segment]);
}