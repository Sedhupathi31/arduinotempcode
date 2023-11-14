#include <TimerOne.h>

const int ledPin = 13; // Pin connected to the LED
int tempPin = 0;       // Analog pin connected to the temperature sensor
float temp;            // Variable to store temperature

const long intervalLowTemp = 250;  // Blink interval for temperatures below 30°C (in milliseconds)
const long intervalHighTemp = 500; // Blink interval for temperatures 30°C and above (in milliseconds)

boolean ledState = LOW;

void setup() {
  pinMode(ledPin, OUTPUT); // Set the LED pin as an output
  Serial.begin(9600);      // Initialize serial communication at 9600 bps

  Timer1.initialize(intervalLowTemp * 1000); // Initialize Timer1 with interval for temperatures below 30°C
  Timer1.attachInterrupt(blinkLowTemp);      // Attach the interrupt function
  Timer1.start();                            // Start the timer
}

void loop() {
  temp = analogRead(tempPin);  // Read analog voltage from the temperature sensor
  temp = temp * 0.48828125;    // Convert analog voltage to temperature (in degrees Celsius)

  // Check temperature and update LED blinking accordingly
  if (temp >= 30.0) {
    // Change the interval for temperatures 30°C and above
    Timer1.initialize(intervalHighTemp * 1000);
  }
}

void blinkLowTemp() {
  ledState = !ledState;
  digitalWrite(ledPin, ledState);
}

void blinkHighTemp() {
  ledState = !ledState;
  digitalWrite(ledPin, ledState);
}