// color swirl! connect an RGB LED to the PWM pins as indicated
// in the #defines
// public domain, enjoy!
 
#define REDPIN 5
#define GREENPIN 6
#define BLUEPIN 3
 
#define FADESPEED 5     // make this higher to slow down
 
void setup() {
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
}
 

void loop() {
  int r, g, b;
 
analogWrite(REDPIN, 255); 
analogWrite(BLUEPIN, 0);
  // fade from red to yellow
  for (g = 0; g < 200; g++) { 
    analogWrite(GREENPIN, g);
    delay(FADESPEED);
  } 
  analogWrite(BLUEPIN, 0);
  // fade from red to yellow
  for (g = 200; g > 0; g--) { 
    analogWrite(GREENPIN, g);
    delay(FADESPEED);
  } 
}
