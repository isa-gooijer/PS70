// SOIL MOISTURE - CALIBRATION

class SoilMoist {
  // CLASS MEMBER VARIABLES
  // variables that are initialized at startup
  int SM_pin; //soil moisture sensor pin
  int interval; // interval at which soil moisture values is read
  
  // variables that maintain current state
  int currentMoistValue; // current soil moisture value.
  unsigned long lastUpdate; // last update (in milliseconds)

  public:
  SoilMoist(int SMpin, int Int){
    SM_pin = SMpin;
    interval = Int;
    lastUpdate = 0; // start clock at zero
  }

  void Update(){
    // check to see if it's time to read of the soil moisture value
    if(millis() - lastUpdate >= interval){
      lastUpdate = millis();
      currentMoistValue = analogRead(SM_pin);
      Serial.println("Sensor Value:" + String(currentMoistValue));
    }
  }
};

SoilMoist sm1(4, 1000); // pin = A0; interval = 1000 ms.

void setup() {
 Serial.begin(9600);
}

void loop() {
  sm1.Update();
}
