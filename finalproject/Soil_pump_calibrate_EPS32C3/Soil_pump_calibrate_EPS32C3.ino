// SOIL MOISTURE - PERISTALTIC PUMP - CALIBRATED

// EPS32C3 (conversion)

class SoilMoist {
  // CLASS MEMBER VARIABLES
  // variables that are INITIRALIZED AT STARTUP
  int SM_pin; //soil moisture sensor pin
  int ledPin; // pin of LED
  int pumpPin; // pin of pump
  
  //GET THESE VALUES
  // higher value is in air, lower value in water
  int interval; // interval at which soil moisture values is read (milliseconds)
  float desired_wc; // the desired water content by weight (wc_d)
  
  // GET THESE VALUES FROM CALIBRATION (fill out in FIREBASE)
  // int water_min; // minimum value sensor (pure water)
  // int air_max; // maximum value sensor (air)
  float b_dry_soil; // soil moisture sensor value from dry soil.
  float soil_max_wc; // the water content of saturated soil, refer to calibration curve. 
  float a_slope; // the slope from the linear fitted line from calibration.
  float speed_pump; // how many mL/s are moved by the pump. (seconds)
  // weight the dry soil (doesn't need to be from calibration)
  float dry_weight; // the dry weight of the soil (W_dry) when it was put into the pot/cup without addition of water. (GRAMS)


  // variables that maintain CURRENT STATE
  // GET FROM SENSOR: 
  int y_soil_sensor; // value from the soil moisture sensor
  
  // CALCULATE:
  // water content by weight (so % water of the total weight)
  float x_current_wc; // current water content by weight (wc_c). This is x from y = a*x + b (y_soil_sensor = a_slope * x + b_dry_soil).
  float delta_water_vol; // change in water volume, aka how much mL needs to be added/pumped.
  int time_pump; // time pump is on to get desired water content. (in milliseconds)

  // to keep check of time
  unsigned long lastUpdate; // last update (in milliseconds)


  public:
  SoilMoist(int SENSOR, int LED, int PUMP, int INT,  float a, float b, float W_d, float soilMAX_wc, float desiredWC, float PUMPspeed){
    SM_pin = SENSOR;
    ledPin = LED;
    pumpPin = PUMP;
    interval = INT;
    a_slope = a;
    b_dry_soil = b;
    dry_weight = W_d;
    soil_max_wc = soilMAX_wc;
    desired_wc = desiredWC;
    speed_pump = PUMPspeed;
    
    pinMode(ledPin, OUTPUT); // set LED pin to an OUTPUT
    pinMode(pumpPin, OUTPUT); // set pump pin to an OUTPUT
    lastUpdate = 0; // start clock at zero
  }

  void Update(){
    // check to see if it's time to read of the soil moisture value
    if(millis() - lastUpdate >= interval){
      lastUpdate = millis();
      y_soil_sensor = analogRead(SM_pin);
      x_current_wc = (analogRead(SM_pin) - b_dry_soil) / a_slope; // x = (y-b)/a where y is value from sensor, a and b are derived from the calibration of the sensor.
      delta_water_vol = (dry_weight/(1 - desired_wc)) - (dry_weight/(1 - x_current_wc));
      time_pump = delta_water_vol / speed_pump * 1000; // *1000 to get milliseconds.

      Serial.println("NEW MEASUREMENT");
      Serial.println("Interval: " + String(interval));
      Serial.println("a_slope: " + String(a_slope));
      Serial.println("b_dry_soil: " + String(b_dry_soil));
      Serial.println("dry weight: " + String(dry_weight));
      Serial.println("soil_max_wc: " + String(soil_max_wc));
      Serial.println("desired_wc: " + String(desired_wc));
      Serial.println("Sensor Value:" + String(y_soil_sensor));
      Serial.println("current_cw: " + String(x_current_wc));
      Serial.println("delta_water_vol: " + String(delta_water_vol));
      Serial.println("time_pump: " + String(time_pump/1000));

      x_current_wc = (y_soil_sensor - b_dry_soil) / a_slope; // x = (y-b)/a where y is value from sensor, a and b are derived from the calibration of the sensor.
      
      if (x_current_wc >= soil_max_wc) {
        digitalWrite(ledPin, HIGH); // turn on LED to show that something is wrong. The water content is equal to or higher than the saturated soil --> too much water!
      }

      else if (x_current_wc < desired_wc){
        delta_water_vol = (dry_weight/(1 - desired_wc)) - (dry_weight/(1 - x_current_wc));
        time_pump = delta_water_vol / speed_pump * 1000; // *1000 to get milliseconds.
        
        //Serial.println("delta water volume:" + String(delta_water_volume));
        //Serial.println("time pump is on (ms):" + String(time_pump));
        
        // led pump run for the calculated time to add the estimated amount of water to reach desired water content in the soil.
        analogWrite(pumpPin, 255);
        delay(time_pump);
        analogWrite(pumpPin, 0);

        digitalWrite(ledPin, LOW); // turn off red LED
      }

      else {
        digitalWrite(ledPin, LOW); // turn off red LED
      }
    }
  }
};

// sensor pin = 4, led pin = 3, pump pin = 7.
// interval is 30 sec. --> 30000 ms
// FROM CALIBRATION (EPS32C3):
// a = -2363.4
// b = 32675.2
// W_d = 100 (g)
// soil_max_wc = 0.436
// desired_wc = 0.35
// pump_speed (255) = 2.3 mL/s

SoilMoist sm1(4, 3, 7, 30000, -2363.4, 2675.2, 100, 0.436, 0.35, 2.3);

void setup() {
 Serial.begin(9600);
}

void loop() {
  sm1.Update();
}
