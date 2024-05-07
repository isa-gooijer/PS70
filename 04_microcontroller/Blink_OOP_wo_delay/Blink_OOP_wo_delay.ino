// These variables store the flash pattern
// and the current state of the LED

class Flasher {
  // Class member variables
  // These are initialized at the startup
  int ledPin; // number of LED pin
  long OnTime; // ms on-time
  long OffTime; // ms off-time

  // These maitain the current stat
  int ledState; // ledState used to set the LED
  unsigned long previousMillis; // stores the last time LED was updated


  // CONSTRUCTOR - creates a Flasher
  // and initializes the member variables and state
  public:
  Flasher(int pin, long on, long off) {
    ledPin = pin;
    pinMode(ledPin, OUTPUT);
    
    OnTime = on;
    OffTime = off;

    ledState = LOW;
    previousMillis = 0;
  }

  void Update() {
  // check to see if it's time to change the state of the LED
  unsigned long currentMillis = millis();

  // if LED is on and difference between current time and previous update
  // is bigger than the time LED is supposed to be turned on.
  if((ledState == HIGH) && (currentMillis - previousMillis >= OnTime)){
    ledState = LOW; // change LED state to being turned off.
    previousMillis = currentMillis; // remember the time (of updating)
    digitalWrite(ledPin, ledState); // update the actual LED
    }
  // if LED is off, and difference between current time and last update is 
  // is bigger than the time the LED is supposed to be turned off.
  else if((ledState == LOW) && (currentMillis - previousMillis >= OffTime)){
    ledState = HIGH; // change led state to being turned on
    previousMillis = currentMillis; // remember the time
    digitalWrite(ledPin, ledState); // update actual LED
    }
  }
};


Flasher led1(12, 100, 400);
Flasher led2(13, 350, 350);
Flasher led3(11, 1000, 200);

void setup(){

}

void loop(){
  led1.Update();
  led2.Update();
  led3.Update();
}