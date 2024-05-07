/* WITH DELAY
int button1Pin = 4;
int button2Pin = 5;
int ledPin = 6;

void setup() {
  // put your setup code here, to run once:
    // pull up Arduino's internal resistor.
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Button 1: ");
  Serial.print(digitalRead(button1Pin));
  Serial.print("Button 2: ");
  Serial.println(digitalRead(button2Pin));

  if(digitalRead(button1Pin) == 0 ){
    digitalWrite(ledPin, HIGH);
    delay(5000);
    digitalWrite(ledPin, LOW);
  }

} */

#include <Servo.h> 

class Button{
  // Member variables
  int buttonPin; //what pin the button is connected to.
  int buttonState; //what the button is currently reading.

  // constructor
  public:
  // outside value 'pin' that I'm putting into the class
  Button(int pin){
    buttonPin = pin;
    pinMode(buttonPin, INPUT_PULLUP);
    buttonState = digitalRead(buttonPin); //or 1, it's going to read HIGH
  }

  // int to get a return value
  int Update() {
    buttonState = digitalRead(buttonPin); //what the button is reading.
    return buttonState; // whenever you call the function it'll return the buttonState.
  }
};


class Light{
  // Member variables
  int ledPin;
  int ledState;

  public:
  // constructor
  Light(int pin){
    ledPin = pin;
    pinMode(ledPin, OUTPUT);
  }

  // joined
  void Update(int buttonState){
    ledState = 1 - buttonState;
    digitalWrite(ledPin, ledState);
  }
};

class Sweeper{
  Servo servo;  // the servo
  int pos; // current servo position
  int increment; //increment to move for each interval
  int updateInterval; //interval between updates (in milliseconds)
  unsigned long lastUpdate; //last update of position (in milliseconds)

  //CONSTRUCTOR
  public:
  Sweeper(int interval){
    updateInterval = interval;
    increment = 1;
  }

  void Attach(int pin){
    servo.attach(pin);
  }

  void Detach(){
    servo.detach();
  }

  void Update(int buttonState){
    if (buttonState == LOW) {
      // check if time to update
      if(millis() - lastUpdate > updateInterval){
        lastUpdate = millis(); // remember time
        pos += increment; // increase/change position
        servo.write(pos); // change position of Servo motor
        Serial.println(pos); // print the position in serial monitor
        
        //end of sweep when degree is 180 or 0.
        if((pos >= 180) || (pos <=0)){
          // reverse direction
          increment = -increment;
        }
      }
    }    
  }
}; 



Button ledButton(4);
Button motorButton(5);
Light led1(6);
Sweeper motor1(15);

void setup() {
  Serial.begin(9600);
  motor1.Attach(10);
}

void loop() {
  Serial.print("Button 1: ");
  Serial.print(ledButton.Update()); // call the update function of ledButton member of button class.
  Serial.print("Button 2: ");
  Serial.println(motorButton.Update());

  led1.Update(ledButton.Update());
  motor1.Update(motorButton.Update());
}