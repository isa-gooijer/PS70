// Blink w/o using delay()
// http://www.arduino.cc/en/Tutorial/BlinkWithoutDelay


// constants won't change. Used here to set pin numbers.
const int ledPin = 13; // LED plugged into pin 13

// variables that will change:
int ledState = LOW; // used to set the LED
long previousMillis = 0; // stores the last time the LED was updated

// the following avriable is a long because the times, measuredd in ms,
// will quickly become a bigger number that can't be stored in an int.
long interval = 1000; //interval at which to blink (ms)

void setup() {
  // set digital pin as output.
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Check to see if it's time to blink the LED.
  /* If difference between current time and last time you blinked the LED
  is bigger than the interval at which you want to blink the LED. */

  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW){
      ledState = HIGH;
    }
    else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable
    digitalWrite(ledPin, ledState);
  }
}
