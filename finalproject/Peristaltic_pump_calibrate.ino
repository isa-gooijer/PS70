int pumpPin = 7; // pin of pump

void setup() {
  // put your setup code here, to run once:
  pinMode(pumpPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(pumpPin, LOW);
  delay(5000);

  analogWrite(pumpPin, 255);
  Serial.println("Pump power: 255 (max)");
  delay(5000);
  digitalWrite(pumpPin, LOW);
  delay(3000);

  analogWrite(pumpPin, 225);
  Serial.println("Pump power: 225");
  delay(5000);
  digitalWrite(pumpPin, LOW);
  delay(3000);

  analogWrite(pumpPin, 200);
  Serial.println("Pump power: 200");
  delay(5000);
  digitalWrite(pumpPin, LOW);
  delay(3000);

  analogWrite(pumpPin, 175);
  Serial.println("Pump power: 175");
  delay(5000);
  digitalWrite(pumpPin, LOW);
  delay(3000);

  analogWrite(pumpPin, 150);
  Serial.println("Pump power: 150");
  delay(5000);
  digitalWrite(pumpPin, LOW);
  delay(3000);

}
