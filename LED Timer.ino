// Define button and LED pins
const int buttonPin = 2;
const int ledPin = 13;

// Variables to store button state
int buttonState = 0;
int lastButtonState = 0;

// Variables to store LED state
bool ledState = false;

// Variables to store timer state
unsigned long previousMillis = 0;
const long interval = 1000 * 60 * 60;  // 1 hour in milliseconds
bool timerRunning = false;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
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
      digitalWrite(ledPin, HIGH);
    } else {
      // Stop the timer
      timerRunning = false;
      digitalWrite(ledPin, LOW);
    }
  }

  // Update the last button state
  lastButtonState = buttonState;

  // Check if the timer is running
  if (timerRunning) {
    // Check if it's time to flash the LED
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      // Timer has finished, flash the LED
      flashLED();
      timerRunning = false;
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
