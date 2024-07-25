#include <IRremote.h>

const int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;

const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;

bool isOn = false;
int currentColor = 0;  // 0: off, 1: red, 2: green, 3: blue, 

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  turnOff();
}

void loop() {
  if (irrecv.decode(&results)) {
    handleIRInput(results.value);
    irrecv.resume();
  }
}

void handleIRInput(unsigned long value) {
  switch (value) {
    case 0xFFA25D:  // Power button
      isOn = !isOn;
      if (isOn) {
        changeColor(currentColor);
      } else {
        turnOff();
      }
      break;
    case 0xFF629D:  // Up button
      currentColor = (currentColor + 1) % 8;
      if (isOn) {
        changeColor(currentColor);
      }
      break;
    case 0xFFA857:  // Down button
      currentColor = (currentColor - 1 + 8) % 8;
      if (isOn) {
        changeColor(currentColor);
      }
      break;
  }
}

void turnOff() {
  analogWrite(RED_PIN, 0);
  analogWrite(GREEN_PIN, 0);
  analogWrite(BLUE_PIN, 0);
}

void changeColor(int color) {
  switch (color) {
    case 0:  // Off
      turnOff();
      break;
    case 1:  // Red
      setColor(255, 0, 0);
      break;
    case 2:  // Green
      setColor(0, 255, 0);
      break;
    case 3:  // Blue
      setColor(0, 0, 255);
      break;
  
}

void setColor(int red, int green, int blue)
{
  analogWrite(RED_PIN, red);
  analogWrite(GREEN_PIN, green);
  analogWrite(BLUE_PIN, blue);
}
