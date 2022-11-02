unsigned const int BAUD_RATE = 9600;
unsigned const int interruptPin = 2;
unsigned const int carRedLedPin = 5;
unsigned const int carYellowLedPin = 6;
unsigned const int carGreenLedPin = 7;
unsigned const int pedestrianRedLedPin = 10;
unsigned const int pedestrianGreenLedPin = 11;
unsigned const int audioOutputPin = 4; 

unsigned const int debounceDelay = 50;
unsigned int lastDebounceTime = 0;

byte outputOn = HIGH;
volatile byte interruptPinState = LOW;
 
unsigned const int defaultState = 1;
unsigned const int inputDetected = 2;
unsigned const int effectOfInput = 3;
unsigned const int lastState = 4;
unsigned int state = defaultState;

unsigned long stageStartTime = 0; 
unsigned long audioOutputStartTime = 0;
unsigned long digitalOutputStartTime = 0;

unsigned const long inputEffectDelay = 8000;
unsigned const long inputDetectedEffectDuration = 3000;
unsigned const long lastStageDuration = 4000;

const float lessThanWhole = 0.3; 
unsigned const int frequency = 1000;
unsigned const long outputInterval = 1000;
unsigned const int audioOutputDuration = 200;


int startStatesCycle = 0;
void setup() {

  pinMode(interruptPin, INPUT_PULLUP);
  pinMode(carRedLedPin, OUTPUT);
  pinMode(carYellowLedPin, OUTPUT);
  pinMode(carGreenLedPin, OUTPUT);
  pinMode(pedestrianRedLedPin, OUTPUT);
  pinMode(pedestrianGreenLedPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), Interrupt, CHANGE);
  Serial.begin(BAUD_RATE);

}

void loop() {

  if (millis() - lastDebounceTime > debounceDelay && interruptPinState) {
    lastDebounceTime = millis();
    startStatesCycle = 1;
  }
  else {
    startStatesCycle = 0;
  }
    switch (state) {

      case defaultState:
        outputOn = HIGH;
        noTone(audioOutputPin); 
        digitalWrite(carRedLedPin, !outputOn);
        digitalWrite(carYellowLedPin, !outputOn);
        digitalWrite(carGreenLedPin, outputOn);
        digitalWrite(pedestrianRedLedPin, outputOn);
        digitalWrite(pedestrianGreenLedPin, !outputOn);
        if (startStatesCycle) {
        stageStartTime = millis();
        state = inputDetected;
        }
        break;

      case inputDetected:
        if (millis() - stageStartTime >= inputEffectDelay) {
          digitalWrite(carRedLedPin, !outputOn);
          digitalWrite(carYellowLedPin, outputOn);
          digitalWrite(carGreenLedPin, !outputOn);
          digitalWrite(pedestrianRedLedPin, outputOn);
          digitalWrite(pedestrianGreenLedPin, !outputOn);
          
          if (millis() - stageStartTime - inputEffectDelay >= inputDetectedEffectDuration) {
            stageStartTime = millis();
            audioOutputStartTime = millis();
            state = effectOfInput;
          }
        }
        break;

      case effectOfInput:
        digitalWrite(carRedLedPin, outputOn);
        digitalWrite(carYellowLedPin, !outputOn);
        digitalWrite(carGreenLedPin, !outputOn);
        digitalWrite(pedestrianRedLedPin, !outputOn);
        digitalWrite(pedestrianGreenLedPin, outputOn); 
        if (millis() - audioOutputStartTime >= outputInterval) {
          tone(audioOutputPin, frequency, audioOutputDuration);
          audioOutputStartTime = millis();
        }
        if (millis() - stageStartTime >= inputEffectDelay) {
          stageStartTime = millis();
          digitalOutputStartTime = millis();
          state = lastState;
        }
        break;

      case lastState:
          if (millis() - digitalOutputStartTime >= outputInterval * lessThanWhole) {
            outputOn = !outputOn;
            digitalWrite(pedestrianGreenLedPin, outputOn);
            tone(audioOutputPin, frequency, audioOutputDuration);
            digitalOutputStartTime = millis();    
          }
          if (millis() - stageStartTime >= lastStageDuration) {
            state = defaultState;
            interruptPinState = LOW;
          }
        break;

      default: 
        break;
    }
}


void Interrupt(){
       interruptPinState = HIGH;
}