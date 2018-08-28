
/*
 * Automatic Watering System 1.0
 * 
 * An arduino program for time controlled plant watering.
 * 
 * The main concept is to controll a 12V pump with a mosfet,
 * and water the plants according to the time parameters 
 * defined in the param section.
 * 
 * For more information check the github repo:
 * https://github.com/legokor/Automatic-Watering-System
 * or the article:
 * http://legokor.hu/2018-08-28-aws/
 * 
 */

// ------------------------------------------------------------ PARAM ------------------------------------------------------------
// ---------- time parameters ----------
unsigned long minutes_between_watering = 4320;      // the time between two watering    in minutes    currently 3 days
unsigned long watering_time_seconds = 180;          // how long the pump will be running in seconds    currently 3 minutes 

// ---------- pump I/O parameters ----------
int pump = 4;

unsigned long last_watering_time = 0;               // in milliseconds


// ------------------------------------------------------------ SETUP ------------------------------------------------------------
void setup() {
  
  pinMode(pump, OUTPUT);
  digitalWrite(pump, LOW);

  water_plants(10);
  last_watering_time = millis();
}


// ------------------------------------------------------------ LOOP ------------------------------------------------------------
void loop() {
  // check if its time to water
  if ( ((millis() - last_watering_time)/60000) >= minutes_between_watering ) {
    water_plants(watering_time_seconds);
  }
  
  // sleep the program for 0.1 second
  delay(100);
}



// ------------------------------------------------------------ FUNCTIONS ------------------------------------------------------------

/*
 * tuns the pump on, and turns it off after it was running for the watering_time interval seconds
 *   note: the function stops the pump for 10 seconds at the half of the watering time, to let the pump engine cool down
 */
void water_plants(unsigned long watering_time) {
  digitalWrite(pump, HIGH); 
  
  unsigned long start = millis();
  while ( ((millis() - start)/1000) < watering_time/2 ) {
    delay(100);
  }

  digitalWrite(pump, LOW);
  delay(10000);
  digitalWrite(pump, HIGH);

  start = millis();
  while ( ((millis() - start)/1000) < watering_time/2 ) {
    delay(100);
  }

  digitalWrite(pump, LOW);
  last_watering_time = millis();
}








