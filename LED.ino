// LED Pit logo display
// 3/31/18
// Liam Bewley, Maya Yaakov, Roy Hill, Art McLaughlin


#include <SoftwareSerial.h>
 
#define REDPIN 5
#define GREENPIN 6
#define BLUEPIN 4
#define BUTTONPIN 2
#define A_CHANNEL 3
#define B_CHANNEL 9

int buttonState = 0;
int buttonPressed = 0;

#define FADESPEED 5    // make this higher to slow down

enum Mode { Fade, Red, Orange, Yellow};
Mode mode = Fade;
int buttonDebounceLast = 0;
int buttonDebounce;
int encoderDebounceLast = 0;
int encoderDebounce;

double dimPercent = 1;
 
void setup() {
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  pinMode(BUTTONPIN, INPUT);
  pinMode(A_CHANNEL, INPUT);
  pinMode(B_CHANNEL, INPUT);

  //Turn on internal pullups
  digitalWrite(BUTTONPIN, HIGH);
  digitalWrite(A_CHANNEL, HIGH);
  digitalWrite(B_CHANNEL, HIGH);

  //attach listener methods to the button and encoder
  attachInterrupt(digitalPinToInterrupt(BUTTONPIN), updateMode, CHANGE);
  attachInterrupt(digitalPinToInterrupt(A_CHANNEL), updateEncoder, CHANGE);

  Serial.begin(9600);
}


void updateMode() {
  buttonDebounce = millis();

  //debouncing delay
  if(buttonDebounce - buttonDebounceLast > 750) {
    switch (mode) {
      case Fade:
        mode = Red;
        break;
      case Red:
        mode = Orange;
        break;
      case Orange:
        mode = Yellow;
        break;
      case Yellow:
        mode = Fade;
        break;
    }

    buttonDebounceLast = buttonDebounce;
  }
}


void updateEncoder() {
  encoderDebounce = millis();
  Serial.println("Interrupt Called");
  //debouncing delay
  if(encoderDebounce - encoderDebounceLast > 200) {
  Serial.println("Debounce called");
    //check direction of movement using B channel, modify dimPercent
    if(digitalRead(B_CHANNEL) == LOW) {
      Serial.println("B channel read as low");
      if(dimPercent > 0) {
        Serial.println("dimPercent modified");
        dimPercent -= 0.25;
      }
    } else {
      Serial.println("B channel read as high");
      if(dimPercent < 1) {
        Serial.println("dimPercent modified");
        dimPercent += 0.25;
      }
    }
    encoderDebounceLast = encoderDebounce;
  }
}

void loop() {
  int r, g, b;


  if(mode == Fade) {
   analogWrite(REDPIN, (int) (255 * dimPercent)); 
   analogWrite(BLUEPIN, 0);
    // fade from red to yellow
    for (g = 0; g < 200; g++) { 
      analogWrite(GREENPIN, (int) (g * dimPercent));
      delay(FADESPEED);
    } 
    analogWrite(BLUEPIN, 0);
    // fade from yellow to red
    for (g = 200; g > 0; g--) { 
      analogWrite(GREENPIN, (int) (g * dimPercent));
      delay(FADESPEED);
    } 
  } else if(mode == Red) {
      analogWrite(REDPIN, (int) (100 * dimPercent));
      analogWrite(BLUEPIN, 0);
      analogWrite(GREENPIN, 0);
  } else if(mode == Orange) {
      analogWrite(REDPIN, (int) (255 * dimPercent));
      analogWrite(BLUEPIN, 0);
      analogWrite(GREENPIN, (int) (50 * dimPercent));
  } else if(mode == Yellow) {
      analogWrite(REDPIN, (int) (255 * dimPercent));
      analogWrite(BLUEPIN, 0);
      analogWrite(GREENPIN, (int) (150 * dimPercent));
  }
}
