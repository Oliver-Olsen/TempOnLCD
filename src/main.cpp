//Oliver Olsen s205443
//Nils Wulff   s223968

//To use the LCD we need two libraries: One to control I2C, and one for controlling the display itself
#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define TEMPPIN A0 //The pin used for ADC
#define INPUTVOLTAGE 5.0 //The voltage used in the temp sensor
#define ANALOGMAX 1024.0 //The resolution of the ADC
#define OFFSET 0 //A temperature offset determined by the sensor datasheet
#define SAMPLESIZE 10 //How many samples are taken per update
#define SAMPLETIME 1500 //How often does the display update
#define TOOHOT 28 //The temperature at which the system gets too hot

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

float temperature(); //Initialize temperature function

bool hot = false; //Boolean to determine if the system was just too hot

void setup() {
  pinMode(TEMPPIN, INPUT);
  
  lcd.init(); // Initialize the LCD 
  lcd.backlight(); //Turns on the backlight
}

void loop() {
  float SUM = 0; //Creates a sum for averaging samples
  for (int i = 0; i < SAMPLESIZE; i++) {//Adds samples together with a uniform delay
    SUM += temperature(); 
    delay(SAMPLETIME / SAMPLESIZE);
  }
  float temp = SUM / SAMPLESIZE; //After samples have been added, averages them out

  lcd.setCursor(0, 0); //Sets the LCD cursor at origin
  lcd.print(temp); //Prints the temperature on the LCD
  lcd.print(char(223)); //Follows up the temperature with a "°"...
  lcd.print("C"); //... and a "C"

  /*  Checks if a change has occured in 'too hot' status since last check
  *   If a change has occured, updates the lower line of the display
  */

  if ((temp >= TOOHOT) != hot) { 
    lcd.setCursor(0, 1); //Sets cursor to lower line of LCD

    if (temp >= TOOHOT) { //If the system is now too hot, writes it on the display and changes 'hot' boolean to true
      lcd.print("TOO HOT!!!"); 
      hot = true; 
    } else { //If the system is no longer too hot, clears the display and changes 'hot' boolean to false
      lcd.print("          "); 
      hot = false; 
    }
  }

  delay(SAMPLETIME); //A delay to control how often the display is updated
}


/**
 * @brief Calculates the current temperature based on the current ADC reading, by dividing the ADC value with the resolution of the ADC 
 * and multiplying the result with the voltage of the sensor. The temperature of the sensor equals the voltage multiplied by 100
 * 
 * @return float 
 */
float temperature(){
  int analogInput = analogRead(TEMPPIN);
  float voltage = analogInput * (INPUTVOLTAGE/ANALOGMAX); 
  float tempMeasured = (voltage - OFFSET) * 100;
  return tempMeasured;
}



