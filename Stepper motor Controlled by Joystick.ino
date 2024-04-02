#include <Stepper.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Define number of steps per revolution for your stepper motor
const int stepsPerRevolution = 200;  

// Initialize the stepper motor
Stepper myStepper(stepsPerRevolution, 8, 9);  // STEP connected to pin 8, DIR connected to pin 9

// Joystick pins
const int joyPinY = A1;  // Analog input pin for Y-axis

// Joystick threshold
const int joyThreshold = 512;  // Center position of joystick

// LCD module settings
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Set the LCD I2C address and dimensions

void setup() {
  // Initialize the LCD with 16 columns and 2 rows
  lcd.begin(16, 2);
  lcd.backlight();

  // Set the speed of the stepper motor (RPM)
  myStepper.setSpeed(30);  // Reduced speed to 30 RPM  
}

void loop() {
  // Read the analog value from the joystick
  int joyValY = analogRead(joyPinY);

  // Direction display
  if (joyValY < joyThreshold - 100) {
    lcd.setCursor(0, 0);
    lcd.print("Direction: ");
    lcd.setCursor(0, 1);
    lcd.print("Clockwise ");
    
    // Set the direction of the stepper motor
    digitalWrite(9, HIGH);  // DIR pin
    
    // Move the stepper motor
    myStepper.step(1);
    delay(10);  // Delay to slow down the motor
  } 
  else if (joyValY > joyThreshold + 100) {
    lcd.setCursor(0, 0);
    lcd.print("Direction: ");
    lcd.setCursor(0, 1);
    lcd.print("CounterCW ");
    
    // Set the direction of the stepper motor
    digitalWrite(9, LOW);  // DIR pin
    
    // Move the stepper motor
    myStepper.step(1);
    delay(10);  // Delay to slow down the motor
  } 
  else {
    // Stop the motor
    myStepper.step(0);
    lcd.setCursor(0, 0);
    lcd.print("Direction: ");
    lcd.setCursor(0, 1);
    lcd.print("Stopped   ");
  }
}
