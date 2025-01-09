//Oliver Olsen s205443
//Nils Wulff   s223968


#include <Arduino.h>
#include <LiquidCrystal.h>
#define TEMPPIN A0
#define INPUTVOLTAGE 5.0
#define ANALOGMAX 1024.0
#define OFFSET 0

#define REDPIN 11
#define YELLOWPIN 10
#define GREENPIN 9

#define HOTTEMP 27
#define COLDTEMP 24

int analogInput = 0;
float volt = 0;
float tempMeasured = 0;




float voltConvert(int analogInput);

void setup() {
  Serial.begin(9600);
  pinMode(TEMPPIN, INPUT);
  pinMode(REDPIN, OUTPUT);
  pinMode(YELLOWPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  
}

void loop() {
  analogInput = analogRead(TEMPPIN);

  // Store the new voltage
  volt = voltConvert(analogInput);
  Serial.print("Voltage measured/calculated: ");
  Serial.println(volt);
  // Temp calculated with formula: temperature_c = voltage * 100
  tempMeasured = (volt-OFFSET) * 100;
  Serial.print("Temperature measured: ");
  Serial.print(tempMeasured);
  Serial.write(u8"\u00B0");
  Serial.println("C");


  // Delay added to reduce number print-outs
  // The sensor can output data once per second
  delay(1000);

}


/**
 * @brief Converts the analog reading tol voltage by utilizing the formula: v = analog_reading * (V_in/analogMax)
 * 
 * @param analogInput 
 * @return int 
 */
  float voltConvert(int analogInput){
  float voltage = 0;
  voltage = analogInput * (INPUTVOLTAGE/ANALOGMAX);
  return voltage;
}



