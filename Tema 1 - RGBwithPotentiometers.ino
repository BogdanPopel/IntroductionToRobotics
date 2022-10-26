const unsigned short int redLedPin = 11;
const unsigned short int greenLedPin = 10;
const unsigned short int blueLedPin = 9;

const unsigned short int redAnalogInPin = A0;
const unsigned short int greenAnalogInPin = A1;
const unsigned short int blueAnalogInPin = A2;

unsigned short int redAnalogInValue = 0;
unsigned short int greenAnalogInValue = 0;
unsigned short int blueAnalogInValue = 0;

unsigned short int redBrightness = 0;
unsigned short int greenBrightness = 0;
unsigned short int blueBrightness = 0;

byte DEBUG_MODE = 0;

const unsigned short int MAX_ANALOG_INPUT = 1023;
const unsigned short int MIN_ANALOG_INPUT, MIN_ANALOG_OUTPUT = 0;
const unsigned short int MAX_ANALOG_OUTPUT = 255;
const unsigned short int BAUD_RATE = 9600;

void setup() {

  Serial.begin(BAUD_RATE);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);

}

void loop() {

  redAnalogInValue = analogRead(redAnalogInPin);
  greenAnalogInValue = analogRead(greenAnalogInPin);
  blueAnalogInValue = analogRead(blueAnalogInPin);
  
  redBrightness = map(redAnalogInValue, MIN_ANALOG_INPUT, MAX_ANALOG_INPUT, MIN_ANALOG_OUTPUT, MAX_ANALOG_OUTPUT); 
  greenBrightness = map(greenAnalogInValue, MIN_ANALOG_INPUT, MAX_ANALOG_INPUT, MIN_ANALOG_OUTPUT, MAX_ANALOG_OUTPUT);
  blueBrightness = map(blueAnalogInValue, MIN_ANALOG_INPUT, MAX_ANALOG_INPUT, MIN_ANALOG_OUTPUT, MAX_ANALOG_OUTPUT);
 
  if( DEBUG_MODE ){
    Serial.write("Red Analog Input: ");
    Serial.println(redAnalogInValue);
    Serial.write("Green Analog Input: ");
    Serial.println(greenAnalogInValue);
    Serial.write("Blue Analog Input: ");
    Serial.println(blueAnalogInValue);
  }
  
    analogWrite(redLedPin, redBrightness);
    analogWrite(greenLedPin, greenBrightness);
    analogWrite(blueLedPin, blueBrightness);
 

}
