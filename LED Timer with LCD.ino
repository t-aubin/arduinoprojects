#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define button, LED, and LCD pins
const int buttonPin = 2;
const int ledPin = 12;

// Initialize the I2C LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Set the LCD I2C address, columns, and rows

// Variables to store button state
int buttonState = 0;
int lastButtonState = 0;

// Variables to store timer state
unsigned long previousMillis = 0;
const long interval = 3600000;  // 1 hour in milliseconds
bool timerRunning = false;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  
  lcd.begin(16, 2);  // Initialize the LCD with 16 columns and 2 rows
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Time left:");
  lcd.setCursor(0, 1);
  lcd.print("1:00:00");
}

void loop() {
  // Read the state of the button
  buttonState = digitalRead(buttonPin);

  // Check if the button is pressed
  if (buttonState == HIGH && lastButtonState == LOW) {
    if (!timerRunning) {
      // Start the timer
      previousMillis = millis();
      timerRunning = true;
      digitalWrite(ledPin, LOW);  // Turn off the LED
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Time left:");
      lcd.setCursor(0, 1);
      lcd.print("1:00:00");
    } else {
      // Stop the timer
      timerRunning = false;
      digitalWrite(ledPin, LOW);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Stopped");
      lcd.setCursor(0, 1);
      lcd.print("         ");
    }
  }

  // Update the last button state
  lastButtonState = buttonState;

  // Check if the timer is running
  if (timerRunning) {
    // Check if it's time to update the LCD
    unsigned long currentMillis = millis();
    long elapsedTime = currentMillis - previousMillis;
    long remainingTime = interval - elapsedTime;
    int hours = (remainingTime / 1000) / 3600;
    int minutes = (remainingTime / 1000 / 60) % 60;
    int seconds = (remainingTime / 1000) % 60;

    if (remainingTime <= 0) {
      // Timer has finished
      flashLED();
      timerRunning = false;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Push up time!");
      lcd.setCursor(0, 1);
      lcd.print("         ");
    } else {
      // Update the LCD with the remaining time
      lcd.setCursor(0, 1);
      if (hours < 10) lcd.print("0");
      lcd.print(hours);
      lcd.print(":");
      if (minutes < 10) lcd.print("0");
      lcd.print(minutes);
      lcd.print(":");
      if (seconds < 10) lcd.print("0");
      lcd.print(seconds);
    }
  }

  // Delay to debounce the button
  delay(50);
}

void flashLED() {
  for (int i = 0; i < 20; i++) {
    digitalWrite(ledPin, HIGH);
    delay(250);
    digitalWrite(ledPin, LOW);
    delay(250);
  }
}
