//Oliver Olsen s205443
//Nils Wulff   s223968

// 11a  The I2C is a way to communicate with one or more components at once.
// The I2C works by sending the data over the serial data and serial clock.
// The master (microcontoller) sends the adress that the data is for. The component
// With the corrosponding adress then recieves the data. Id the adress wasn't a match,
// the component ignores it. This way we can communicate with multiple components (but not at once!).
// 11b  We can save power, by only printing when necessary.


#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define TEMPPIN A0
#define INPUTVOLTAGE 5.0
#define ANALOGMAX 1024.0
#define OFFSET 0
#define SAMPLESIZE 10
#define SAMPLETIME 1500
#define TOOHOT 28

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

float temperature();

void setup() {
  Serial.begin(9600);
  pinMode(TEMPPIN, INPUT);
  
  lcd.init();                      // initialize the lcd 
  lcd.backlight(); 
}

void loop() {
  float SUM = 0; 
  for (int i = 0; i < SAMPLESIZE; i++) {
    SUM += temperature(); 
    delay(SAMPLETIME / SAMPLESIZE);
  }
  float temp = SUM / SAMPLESIZE; 
  Serial.println(temp); 
  lcd.setCursor(0, 0); 
  lcd.print(temp); 
  lcd.print(char(223)); 
  lcd.print("C");

  lcd.setCursor(0, 1); 
  if (temp >= TOOHOT) {
    lcd.print("TOO HOT!!!");
  } else {
    lcd.print("          "); 
  }

  delay(SAMPLETIME);
}


/**
 * @brief Converts the analog reading tol voltage by utilizing the formula: v = analog_reading * (V_in/analogMax)
 * 
 * @param analogInput 
 * @return int 
 */
float temperature(){
  int analogInput = analogRead(TEMPPIN);
  float voltage = analogInput * (INPUTVOLTAGE/ANALOGMAX); 
  float tempMeasured = (voltage - OFFSET) * 100;
  return tempMeasured;
}



