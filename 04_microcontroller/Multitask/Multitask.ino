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


Button ledButton(4);
Button motorButton(5);
Light led1(6);

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("Button 1: ");
  Serial.print(ledButton.Update()); // call the update function of ledButton member of button class.
  Serial.print("Button 2: ");
  Serial.println(motorButton.Update());

  led1.Update(ledButton.Update());
}